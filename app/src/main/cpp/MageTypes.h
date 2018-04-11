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

#ifndef MAGE_COMMON_MAGE_TYPES_H_
#define MAGE_COMMON_MAGE_TYPES_H_

#include <stdint.h>
#include <sys/types.h>

typedef int            Mage_Result;
typedef unsigned int   Mage_Flags;
typedef unsigned int   Mage_Mask;
typedef unsigned int   Mage_Cardinal;
typedef unsigned int   Mage_Ordinal;
typedef unsigned int   Mage_UI32;
typedef signed   int   Mage_SI32;
typedef unsigned short Mage_UI16;
typedef signed   short Mage_SI16;
typedef unsigned char  Mage_UI08;
typedef Mage_UI08      Mage_Byte;
typedef Mage_UI32      Mage_Size;
typedef __int64_t      Mage_SI64;
typedef __uint64_t     Mage_UI64;

#endif //!MAGE_COMMON_MAGE_TYPES_H_