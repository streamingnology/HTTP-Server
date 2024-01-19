#ifndef BHO_DESCRIBE_BASES_HPP_INCLUDED
#define BHO_DESCRIBE_BASES_HPP_INCLUDED

// Copyright 2020, 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <asio2/bho/describe/modifiers.hpp>
#include <asio2/bho/describe/detail/void_t.hpp>
#include <asio2/bho/describe/detail/config.hpp>

#if defined(BHO_DESCRIBE_CXX11)

#include <asio2/bho/mp11/algorithm.hpp>
#include <type_traits>

namespace bho
{
namespace describe
{
namespace detail
{

template<class T> using _describe_bases = decltype( bho_base_descriptor_fn( static_cast<T**>(0) ) );

template<unsigned M> struct base_filter
{
    template<class T> using fn = mp11::mp_bool< ( M & mod_any_access & T::modifiers ) != 0 >;
};

template<class T, class En = void> struct has_describe_bases: std::false_type
{
};

template<class T> struct has_describe_bases<T, void_t<_describe_bases<T>>>: std::true_type
{
};

} // namespace detail

template<class T, unsigned M> using describe_bases = mp11::mp_copy_if_q<detail::_describe_bases<T>, detail::base_filter<M>>;

template<class T> using has_describe_bases = detail::has_describe_bases<T>;

} // namespace describe
} // namespace bho

#endif // !defined(BHO_DESCRIBE_CXX11)

#endif // #ifndef BHO_DESCRIBE_BASES_HPP_INCLUDED
