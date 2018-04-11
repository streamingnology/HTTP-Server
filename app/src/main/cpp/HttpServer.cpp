/******************************************************************************
|
| Copyright (c) 2018 streamingnology Inc (https://github.com/streamingnology)
|
| This file is part of HTTP Server
|
| Permission is hereby granted, free of charge, to any person obtaining a copy
| of this software and associated documentation files (the "Software"), to deal
| in the Software without restriction, including without limitation the rights
| to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
| copies of the Software, and to permit persons to whom the Software is
| furnished to do so, subject to the following conditions:
|
| The above copyright notice and this permission notice shall be included in all
| opies or substantial portions of the Software.
|
| THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
| MPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
| FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
| AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
| LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
| OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
| OFTWARE.
 ******************************************************************************/

#include "HttpServer.h"

extern "C" {
  #include "Log.h"
}

extern "C" {

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/types.h>
  #include <sys/stat.h>

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #include <windows.h>
  #include <io.h>
  #include <fcntl.h>
  #ifndef S_ISDIR
  #define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#endif
#else
  #include <sys/stat.h>
  #include <sys/socket.h>
  #include <signal.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <dirent.h>
#endif

  #include <event2/event.h>
  #include <event2/http.h>
  #include <event2/buffer.h>
  #include <event2/util.h>
  #include <event2/keyvalq_struct.h>

#ifdef EVENT__HAVE_NETINET_IN_H
  #include <netinet/in.h>
  #ifdef _XOPEN_SOURCE_EXTENDED
    #include <arpa/inet.h>
    #endif
#endif

}


#ifdef _WIN32
#ifndef stat
#define stat _stat
#endif
#ifndef fstat
#define fstat _fstat
#endif
#ifndef open
#define open _open
#endif
#ifndef close
#define close _close
#endif
#ifndef O_RDONLY
#define O_RDONLY _O_RDONLY
#endif
#endif

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "C.h"

using namespace rapidjson;

const char *(HttpServer::TAG) = "HttpServer";

static void HttpServiceThread(void* arg) {
	HttpServer *httpServer = (HttpServer*)arg;
	struct event_base *base = (struct event_base *)httpServer->GetEventBase();
	event_base_dispatch(base);
}

HttpServer::HttpServer() {
	this->listenPort = 8989;
	this->webroot = "";
	this->base = NULL;
	this->httpServerThread = NULL;
}

static const struct table_entry {
		const char *extension;
		const char *content_type;
} content_type_table[] = {
				{ "txt",   "text/plain" },
				{ "html",  "text/html" },
				{ "htm",   "text/htm" },
				{ "css",   "text/css" },
				{ "gif",   "iAP4/gif" },
				{ "jpg",   "iAP4/jpeg" },
				{ "jpeg",  "iAP4/jpeg" },
				{ "png",   "iAP4/png" },
				{ "m3u8",  "application/vnd.apple.mpegurl"},
				{ "ts",    "video/MP2T"},
				{ NULL,    NULL },
};

/* Try to guess a good content-type for 'path' */
static const char *guess_content_type(const char *path)
{
	const char *last_period, *extension;
	const struct table_entry *ent;
	last_period = strrchr(path, '.');
	if (!last_period || strchr(last_period, '/'))
		goto not_found; /* no exension */
	extension = last_period + 1;
	for (ent = &content_type_table[0]; ent->extension; ++ent) {
		if (!evutil_ascii_strcasecmp(ent->extension, extension))
			return ent->content_type;
	}

not_found:
	return "application/misc";
}

HttpServer::~HttpServer() {

}

void HttpServer::SetListenPort(Mage_UI16 port) {
	this->listenPort = port;
}

Mage_UI16 HttpServer::GetListenPort() {
	return this->listenPort;
}

void HttpServer::SetWebRoot(string webroot) {
	this->webroot = webroot;
}

string HttpServer::GetWebRoot() {
	return this->webroot;
}

Mage_Result HttpServer::Start() {
#ifdef _WIN32
	WSADATA WSAData;
	WSAStartup(0x101, &WSAData);
#else
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return Mage_FAILURE;
#endif

	base = event_base_new();
	if (!base) {
		int errorid = 1;
		string how = "Couldn't create an event_base";
		string howto = "Maybe memory use out, try to reboot device. If there is no help, ONLY GOD KNOW HOW TO...";
		makeErrorMessage(errorid, how, howto);
		LOGE(TAG,"Couldn't create an event_base: exiting");
		return Mage_FAILURE;
	}

	/* Create a new evhttp object to handle requests. */
	http = evhttp_new(base);
	if (!http) {
		int errorid = 2;
		string how = "couldn't create evhttp";
		string howto = "Maybe memory use out, try to reboot device. If there is no help, ONLY GOD KNOW HOW TO...";
		makeErrorMessage(errorid, how, howto);
		LOGE(TAG,"couldn't create evhttp. exiting.");
		return Mage_FAILURE;
	}

	/* The /dump URI will dump all requests to stdout and say 200 ok. */
	//evhttp_set_cb(http, "/dump", dump_request_cb, NULL);

	/* We want to accept arbitrary requests, so we need to set a "generic"
	 * cb.  We can also add callbacks for specific paths. */
	evhttp_set_gencb(http, onHttpRequest, (void*)this);

	/* Now we tell the evhttp what port to listen on */
	handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", listenPort);
	if (!handle) {
		char str[32];
		snprintf(str, sizeof(str), "Couldn't bind to port %d.", listenPort);

		int errorid = 3;
		string how = string(str);
		string howto = "Try another port";
		makeErrorMessage(errorid, how, howto);
		LOGE(TAG, "Couldn't bind to port %d. Exiting.\n", (int)listenPort);
		return Mage_FAILURE;
	}

	{
		/* Extract and display the address we're listening on. */
		struct sockaddr_storage ss;
		evutil_socket_t fd;
		ev_socklen_t socklen = sizeof(ss);
		char addrbuf[128];
		void *inaddr;
		const char *addr;
		int got_port = -1;
		fd = evhttp_bound_socket_get_fd(handle);
		memset(&ss, 0, sizeof(ss));
		if (getsockname(fd, (struct sockaddr *)&ss, &socklen)) {

			int errorid = 4;
			string how = "getsockname() failed";
			string howto = "honestly speaking, I don't know how to do, try to reboot device?";
			makeErrorMessage(errorid, how, howto);

			LOGE(TAG, "getsockname() failed");
			return Mage_FAILURE;
		}
		if (ss.ss_family == AF_INET) {
			got_port = ntohs(((struct sockaddr_in*)&ss)->sin_port);
			inaddr = &((struct sockaddr_in*)&ss)->sin_addr;
		} else if (ss.ss_family == AF_INET6) {
			got_port = ntohs(((struct sockaddr_in6*)&ss)->sin6_port);
			inaddr = &((struct sockaddr_in6*)&ss)->sin6_addr;
		} else {
			char str[32];
			snprintf(str, sizeof(str), "Weird address family %d.", ss.ss_family);

			int errorid = 5;
			string how = string(str);
			string howto = "you are using another protocol neither INET nor INET6";
			makeErrorMessage(errorid, how, howto);

			LOGE(TAG, "Weird address family %d\n", ss.ss_family);
			return Mage_FAILURE;
		}
		addr = evutil_inet_ntop(ss.ss_family, inaddr, addrbuf,
		                        sizeof(addrbuf));
		if (addr) {
			char uri_root[512];
			snprintf(uri_root, sizeof(uri_root), "http://%s:%d",addr,got_port);
			LOGD(TAG, "Listening on %s:%d", addr, got_port);
		} else {
			int errorid = 6;
			string how = "evutil_inet_ntop failed";
			string howto = "I don't know how to fix this trouble";
			makeErrorMessage(errorid, how, howto);

			LOGE(TAG, "evutil_inet_ntop failed");
			return Mage_FAILURE;
		}
	}

	this->httpServerThread = new std::thread(HttpServiceThread, this);

	return Mage_SUCCESS;
}

void HttpServer::Stop() {
	if (base != NULL) {
		event_base_loopbreak(base);
		base = NULL;
	}
	if (http != NULL) {
		evhttp_free(http);
		http = NULL;
	}
}

void HttpServer::onHttpRequest(struct evhttp_request *req, void *arg) {
	struct evbuffer *evb = NULL;
	HttpServer *httpServer = (HttpServer *)arg;
	const char *docroot = (const char *)(httpServer->GetWebRoot().c_str());
	const char *uri = evhttp_request_get_uri(req);
	struct evhttp_uri *decoded = NULL;
	const char *path;
	char *decoded_path;
	char *whole_path = NULL;
	size_t len;
	int fd = -1;
	struct stat st;

	if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
		//dump_request_cb(req, arg);
		evhttp_send_error(req, HTTP_BADREQUEST, 0);
		return;
	}

	LOGD(TAG, "Got a GET request for <%s>\n",  uri);

	/* Decode the URI */
	decoded = evhttp_uri_parse(uri);
	if (!decoded) {
		LOGE(TAG,"It's not a good URI. Sending BADREQUEST\n");
		evhttp_send_error(req, HTTP_BADREQUEST, 0);
		return;
	}

	/* Let's see what path the user asked for. */
	path = evhttp_uri_get_path(decoded);
	if (!path) path = "/";

	/* We need to decode it, to see what path the user really wanted. */
	decoded_path = evhttp_uridecode(path, 0, NULL);
	if (decoded_path == NULL)
		goto err;
	/* Don't allow any ".."s in the path, to avoid exposing stuff outside
	 * of the docroot.  This test is both overzealous and underzealous:
	 * it forbids aceptable paths like "/this/one..here", but it doesn't
	 * do anything to prevent symlink following." */
	if (strstr(decoded_path, ".."))
		goto err;

	len = strlen(decoded_path)+strlen(docroot)+2;
	if (!(whole_path = (char *)malloc(len))) {
		LOGE(TAG, "onHttpRequest, malloc failed");
		goto err;
	}
	evutil_snprintf(whole_path, len, "%s/%s", docroot, decoded_path);

	if (stat(whole_path, &st)<0) {
		goto err;
	}

	/* This holds the content we're sending. */
	evb = evbuffer_new();

	if (S_ISDIR(st.st_mode)) {
		/* If it's a directory, read the comments and make a little
		 * index page */
#ifdef _WIN32
		HANDLE d;
		WIN32_FIND_DATAA ent;
		char *pattern;
		size_t dirlen;
#else
		DIR *d;
		struct dirent *ent;
#endif
		const char *trailing_slash = "";

		if (!strlen(path) || path[strlen(path)-1] != '/')
			trailing_slash = "/";

#ifdef _WIN32
		dirlen = strlen(whole_path);
		pattern = malloc(dirlen+3);
		memcpy(pattern, whole_path, dirlen);
		pattern[dirlen] = '\\';
		pattern[dirlen+1] = '*';
		pattern[dirlen+2] = '\0';
		d = FindFirstFileA(pattern, &ent);
		free(pattern);
		if (d == INVALID_HANDLE_VALUE)
			goto err;
#else
		if (!(d = opendir(whole_path)))
			goto err;
#endif

		evbuffer_add_printf(evb,
		                    "<!DOCTYPE html>\n"
						                    "<html>\n <head>\n"
						                    "  <meta charset='utf-8'>\n"
						                    "  <title>%s</title>\n"
						                    "  <base href='%s%s'>\n"
						                    " </head>\n"
						                    " <body>\n"
						                    "  <h1>%s</h1>\n"
						                    "  <ul>\n",
		                    decoded_path, /* XXX html-escape this. */
		                    path, /* XXX html-escape this? */
		                    trailing_slash,
		                    decoded_path /* XXX html-escape this */);
#ifdef _WIN32
		do {
			const char *name = ent.cFileName;
#else
		while ((ent = readdir(d))) {
			const char *name = ent->d_name;
#endif
			evbuffer_add_printf(evb,
			                    "    <li><a href=\"%s\">%s</a>\n",
			                    name, name);/* XXX escape this */
#ifdef _WIN32
			} while (FindNextFileA(d, &ent));
#else
		}
#endif
		evbuffer_add_printf(evb, "</ul></body></html>\n");
#ifdef _WIN32
		FindClose(d);
#else
		closedir(d);
#endif
		evhttp_add_header(evhttp_request_get_output_headers(req),
		                  "Content-Type", "text/html");
	} else {
		/* Otherwise it's a file; add it to the buffer to get
		 * sent via sendfile */
		const char *type = guess_content_type(decoded_path);
		if ((fd = open(whole_path, O_RDONLY)) < 0) {
			LOGE(TAG, "onHttpRequest, open %s failed", whole_path);
			goto err;
		}

		if (fstat(fd, &st)<0) {
			/* Make sure the length still matches, now that we
			 * opened the file :/ */
			perror("fstat");
			goto err;
		}
		evhttp_add_header(evhttp_request_get_output_headers(req),
		                  "Content-Type", type);
		evbuffer_add_file(evb, fd, 0, st.st_size);
	}

	evhttp_send_reply(req, 200, "OK", evb);
	goto done;
err:
	evhttp_send_error(req, 404, "Document was not found");
	if (fd>=0)
		close(fd);
done:
	if (decoded)
		evhttp_uri_free(decoded);
	if (decoded_path)
		free(decoded_path);
	if (whole_path)
		free(whole_path);
	if (evb)
		evbuffer_free(evb);
}

string HttpServer::ToString() {
	return std::string();
}

void *HttpServer::GetEventBase() {
	return base;
}

string HttpServer::GetErrorMessage() {
	return err;
}

void HttpServer::makeErrorMessage(int errid, string how, string howto) {
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	writer.StartObject();
	writer.Key(ERRORID.c_str()); writer.Int(errid);
	writer.Key(ERRORHOW.c_str()); writer.String(how.c_str());
	writer.Key(ERRORHOWTO.c_str()); writer.String(howto.c_str());
	writer.EndObject();
	err = s.GetString();
}

