/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BHO_PREDEF_COMPILER_PGI_H
#define BHO_PREDEF_COMPILER_PGI_H

#include <asio2/bho/predef/version_number.h>
#include <asio2/bho/predef/make.h>

/* tag::reference[]
= `BHO_COMP_PGI`

http://en.wikipedia.org/wiki/The_Portland_Group[Portland Group C/{CPP}] compiler.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__PGI+` | {predef_detection}

| `+__PGIC__+`, `+__PGIC_MINOR__+`, `+__PGIC_PATCHLEVEL__+` | V.R.P
|===
*/ // end::reference[]

#define BHO_COMP_PGI BHO_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__PGI)
#   if !defined(BHO_COMP_PGI_DETECTION) && (defined(__PGIC__) && defined(__PGIC_MINOR__) && defined(__PGIC_PATCHLEVEL__))
#       define BHO_COMP_PGI_DETECTION BHO_VERSION_NUMBER(__PGIC__,__PGIC_MINOR__,__PGIC_PATCHLEVEL__)
#   endif
#   if !defined(BHO_COMP_PGI_DETECTION)
#       define BHO_COMP_PGI_DETECTION BHO_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef BHO_COMP_PGI_DETECTION
#   if defined(BHO_PREDEF_DETAIL_COMP_DETECTED)
#       define BHO_COMP_PGI_EMULATED BHO_COMP_PGI_DETECTION
#   else
#       undef BHO_COMP_PGI
#       define BHO_COMP_PGI BHO_COMP_PGI_DETECTION
#   endif
#   define BHO_COMP_PGI_AVAILABLE
#   include <asio2/bho/predef/detail/comp_detected.h>
#endif

#define BHO_COMP_PGI_NAME "Portland Group C/C++"

#endif

#include <asio2/bho/predef/detail/test.h>
BHO_PREDEF_DECLARE_TEST(BHO_COMP_PGI,BHO_COMP_PGI_NAME)

#ifdef BHO_COMP_PGI_EMULATED
#include <asio2/bho/predef/detail/test.h>
BHO_PREDEF_DECLARE_TEST(BHO_COMP_PGI_EMULATED,BHO_COMP_PGI_NAME)
#endif
