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

#ifndef MAGE_COMMON_IHTTPSERVER_H
#define MAGE_COMMON_IHTTPSERVER_H

#include <string>
#include <thread>
#include "MageTypes.h"
#include "MageResults.h"

using namespace std;

class IHttpServer {
public:
		static IHttpServer *     CreateInstance();
public:
  virtual void               SetListenPort(Mage_UI16 port) = 0;
  virtual Mage_UI16          GetListenPort() = 0;
  virtual void               SetWebRoot(string webroot) = 0;
  virtual string             GetWebRoot() = 0;
  virtual Mage_Result        Start() = 0;
  virtual void               Stop() = 0;
  virtual void*              GetEventBase() = 0;
  virtual string             ToString() = 0;
	virtual string             GetErrorMessage() = 0;
};

#endif //!MAGE_COMMON_IHTTPSERVER_H
