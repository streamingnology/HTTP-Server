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

#include "MageResults.h"

const char* Mage_ResultText(int result) {
	switch (result) {
		case Mage_SUCCESS:                               return "Mage_SUCCESS";
		case Mage_FAILURE:                               return "Mage_FAILURE";
		case Mage_ERROR_OUT_OF_MEMORY:                   return "Mage_ERROR_OUT_OF_MEMORY";
		case Mage_ERROR_INVALID_PARAMETERS:              return "Mage_ERROR_INVALID_PARAMETERS";
		case Mage_ERROR_NO_SUCH_FILE:                    return "Mage_ERROR_NO_SUCH_FILE";
		case Mage_ERROR_PERMISSION_DENIED:               return "Mage_ERROR_PERMISSION_DENIED";
		case Mage_ERROR_CANNOT_OPEN_FILE:                return "Mage_ERROR_CANNOT_OPEN_FILE";
		case Mage_ERROR_EOS:                             return "Mage_ERROR_EOS";
		case Mage_ERROR_WRITE_FAILED:                    return "Mage_ERROR_WRITE_FAILED";
		case Mage_ERROR_READ_FAILED:                     return "Mage_ERROR_READ_FAILED";
		case Mage_ERROR_INVALID_FORMAT:                  return "Mage_ERROR_INVALID_FORMAT";
		case Mage_ERROR_NO_SUCH_ITEM:                    return "Mage_ERROR_NO_SUCH_ITEM";
		case Mage_ERROR_OUT_OF_RANGE:                    return "Mage_ERROR_OUT_OF_RANGE";
		case Mage_ERROR_INTERNAL:                        return "Mage_ERROR_INTERNAL";
		case Mage_ERROR_INVALID_STATE:                   return "Mage_ERROR_INVALID_STATE";
		case Mage_ERROR_LIST_EMPTY:                      return "Mage_ERROR_LIST_EMPTY";
		case Mage_ERROR_LIST_OPERATION_ABORTED:          return "Mage_ERROR_LIST_OPERATION_ABORTED";
		case Mage_ERROR_INVALID_RTP_CONSTRUCTOR_TYPE:    return "Mage_ERROR_INVALID_RTP_CONSTRUCTOR_TYPE";
		case Mage_ERROR_NOT_SUPPORTED:                   return "Mage_ERROR_NOT_SUPPORTED";
		case Mage_ERROR_INVALID_TRACK_TYPE:              return "Mage_ERROR_INVALID_TRACK_TYPE";
		case Mage_ERROR_INVALID_RTP_PACKET_EXTRA_DATA:   return "Mage_ERROR_INVALID_RTP_PACKET_EXTRA_DATA";
		case Mage_ERROR_BUFFER_TOO_SMALL:                return "Mage_ERROR_BUFFER_TOO_SMALL";
		case Mage_ERROR_NOT_ENOUGH_DATA:                 return "Mage_ERROR_NOT_ENOUGH_DATA";
		default:                                        return "UNKNOWN";
	}
}

