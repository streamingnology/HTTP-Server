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

package com.streamingnology.httpserver;

public class HTTPServer {
  private String TAG = "HTTPServer";
  private String webroot = "";
  private int    port = 8080;
  private long   nativeHTTPServer = 0;

  static {
    System.loadLibrary("httpserver-jni");
  }

  public void setParameter(String webroot, int port) {
    this.webroot = webroot;
    this.port    = port;
  }

  public void open () {
    nativeHTTPServer = nativeCreate();
    nativeOpen(nativeHTTPServer, webroot, port);
  }

  public int start() {
    if (nativeHTTPServer != 0) {
      return nativeStart(nativeHTTPServer);
    }
    return 0;
  }

  public void stop() {
    if (nativeHTTPServer != 0) {
      nativeStop(nativeHTTPServer);
    }
  }

  public String getErrorMessage() {
    if (nativeHTTPServer != 0) {
      return nativeGetErrorMessage(nativeHTTPServer);
    }
    return "";
  }

  private native long nativeCreate();
  private native void nativeOpen(long HTTPServer, String webroot, int port);
  private native int  nativeStart(long HTTPServer);
  private native void nativeStop(long HTTPServer);
  private native String nativeGetErrorMessage(long HTTPServer);
}
