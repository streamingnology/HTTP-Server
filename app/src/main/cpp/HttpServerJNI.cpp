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

#include "HttpServerJNI.h"
#include "IHttpServer.h"

JNIEXPORT jlong JNICALL Java_com_streamingnology_httpserver_HTTPServer_nativeCreate
  (JNIEnv *, jobject) {
	IHttpServer* httpServer = IHttpServer::CreateInstance();
	return (long)httpServer;
}

JNIEXPORT void JNICALL Java_com_streamingnology_httpserver_HTTPServer_nativeOpen
  (JNIEnv *env, jobject, jlong httpServer, jstring webroot, jint port) {
	const char *root = env->GetStringUTFChars(webroot, NULL);
	IHttpServer* pHttpServer = (IHttpServer*) httpServer;
	if (pHttpServer != NULL) {
		pHttpServer->SetWebRoot(root);
		pHttpServer->SetListenPort(port);
	}
}

JNIEXPORT jint JNICALL Java_com_streamingnology_httpserver_HTTPServer_nativeStart
  (JNIEnv *, jobject, jlong httpServer) {
	IHttpServer* pHttpServer = (IHttpServer*) httpServer;
	if (pHttpServer != NULL) {
		return pHttpServer->Start();
	}
	return 0;
}

JNIEXPORT void JNICALL Java_com_streamingnology_httpserver_HTTPServer_nativeStop
  (JNIEnv *, jobject, jlong httpServer) {
	IHttpServer* pHttpServer = (IHttpServer*) httpServer;
	if (pHttpServer != NULL) {
		pHttpServer->Stop();
	}
}

JNIEXPORT jstring JNICALL Java_com_streamingnology_httpserver_HTTPServer_nativeGetErrorMessage
  (JNIEnv *env, jobject, jlong httpServer) {
	IHttpServer* pHttpServer = (IHttpServer*) httpServer;
	if (pHttpServer != NULL) {
		string message = pHttpServer->GetErrorMessage();
		return env->NewStringUTF(message.c_str());
	}
	return env->NewStringUTF("");
}

