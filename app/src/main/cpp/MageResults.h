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

#ifndef MAGE_COMMON_RESULTS_H_
#define MAGE_COMMON_RESULTS_H_

const int Mage_SUCCESS                               =  0;
const int Mage_FAILURE                               = -1;
const int Mage_ERROR_OUT_OF_MEMORY                   = -2;
const int Mage_ERROR_INVALID_PARAMETERS              = -3;
const int Mage_ERROR_NO_SUCH_FILE                    = -4;
const int Mage_ERROR_PERMISSION_DENIED               = -5;
const int Mage_ERROR_CANNOT_OPEN_FILE                = -6;
const int Mage_ERROR_EOS                             = -7;
const int Mage_ERROR_WRITE_FAILED                    = -8;
const int Mage_ERROR_READ_FAILED                     = -9;
const int Mage_ERROR_INVALID_FORMAT                  = -10;
const int Mage_ERROR_NO_SUCH_ITEM                    = -11;
const int Mage_ERROR_OUT_OF_RANGE                    = -12;
const int Mage_ERROR_INTERNAL                        = -13;
const int Mage_ERROR_INVALID_STATE                   = -14;
const int Mage_ERROR_LIST_EMPTY                      = -15;
const int Mage_ERROR_LIST_OPERATION_ABORTED          = -16;
const int Mage_ERROR_INVALID_RTP_CONSTRUCTOR_TYPE    = -17;
const int Mage_ERROR_NOT_SUPPORTED                   = -18;
const int Mage_ERROR_INVALID_TRACK_TYPE              = -19;
const int Mage_ERROR_INVALID_RTP_PACKET_EXTRA_DATA   = -20;
const int Mage_ERROR_BUFFER_TOO_SMALL                = -21;
const int Mage_ERROR_NOT_ENOUGH_DATA                 = -22;
const int Mage_ERROR_NOT_ENOUGH_SPACE                = -23;

const char* Mage_ResultText(int result);

#define Mage_FAILED(result) ((result) != Mage_SUCCESS)
#define Mage_SUCCEEDED(result) ((result) == Mage_SUCCESS)

#define Mage_CHECK(_x) do {                      \
    Mage_Result _result = (_x);                  \
    if (Mage_FAILED(_result)) return _result;    \
} while(0)

#endif //!MAGE_COMMON_RESULTS_H_
