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

#ifndef MAGE_COMMON_HTTPSERVER_H
#define MAGE_COMMON_HTTPSERVER_H

#include <string>
#include <thread>
#include "MageTypes.h"
#include "MageResults.h"
#include "IHttpServer.h"

extern "C" {
  #include <event2/event.h>
  #include <event2/http.h>
  #include <event2/buffer.h>
  #include <event2/util.h>
}

//static struct event_base *base = NULL;

using namespace std;
class HttpServer: public IHttpServer
{
public:
    HttpServer();
    ~HttpServer();

public:
		void               SetListenPort(Mage_UI16 port);
		Mage_UI16          GetListenPort();
		void               SetWebRoot(string webroot);
		string             GetWebRoot();
		Mage_Result        Start();
		void               Stop();
		void*              GetEventBase();
		string             ToString();
		string             GetErrorMessage();
public:
		static void        onHttpRequest(struct evhttp_request *req, void *arg);

private:
		void               makeErrorMessage(int errid, string how, string howto);
private:
		Mage_UI16                  listenPort;
		string                     webroot;
		struct event_base          *base;
		struct evhttp              *http;
		struct evhttp_bound_socket *handle;
		thread                     *httpServerThread;
		static const char          *TAG;
		string                     err;
};

#endif //!MAGE_COMMON_HTTPSERVER_H
