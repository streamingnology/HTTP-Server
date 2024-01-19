#ifndef BHO_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED
#define BHO_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <asio2/bho/mp11/detail/mp_fold.hpp>
#include <asio2/bho/mp11/list.hpp>
#include <asio2/bho/mp11/utility.hpp>

namespace bho
{
namespace mp11
{

// mp_min_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_min
{
    template<class T1, class T2> using fn = mp_if<P<T1, T2>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_min_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_min<P>>;
template<class L, class Q> using mp_min_element_q = mp_min_element<L, Q::template fn>;

// mp_max_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_max
{
    template<class T1, class T2> using fn = mp_if<P<T2, T1>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_max_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_max<P>>;
template<class L, class Q> using mp_max_element_q = mp_max_element<L, Q::template fn>;

} // namespace mp11
} // namespace bho

#endif // #ifndef BHO_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED
