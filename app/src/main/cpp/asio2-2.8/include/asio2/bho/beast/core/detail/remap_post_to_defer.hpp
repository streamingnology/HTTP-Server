//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BHO_BEAST_DETAIL_REMAP_POST_TO_DEFER_HPP
#define BHO_BEAST_DETAIL_REMAP_POST_TO_DEFER_HPP

#include <asio/is_executor.hpp>
#include <asio2/bho/core/empty_value.hpp>
#include <type_traits>
#include <utility>

namespace bho {
namespace beast {
namespace detail {

template<class Executor>
class remap_post_to_defer
    : private bho::empty_value<Executor>
{
    BHO_STATIC_ASSERT(
        net::is_executor<Executor>::value);

    Executor const&
    ex() const noexcept
    {
        return this->get();
    }

public:
    remap_post_to_defer(
        remap_post_to_defer&&) = default;

    remap_post_to_defer(
        remap_post_to_defer const&) = default;

    explicit
    remap_post_to_defer(
        Executor const& ex)
        : bho::empty_value<Executor>(
            bho::empty_init_t{}, ex)
    {
    }

    bool
    operator==(
        remap_post_to_defer const& other) const noexcept
    {
        return ex() == other.ex();
    }

    bool
    operator!=(
        remap_post_to_defer const& other) const noexcept
    {
        return ex() != other.ex();
    }

    decltype(std::declval<Executor const&>().context())
    context() const noexcept
    {
        return ex().context();
    }

    void
    on_work_started() const noexcept
    {
        ex().on_work_started();
    }

    void
    on_work_finished() const noexcept
    {
        ex().on_work_finished();
    }

    template<class F, class A>
    void
    dispatch(F&& f, A const& a) const
    {
        ex().dispatch(std::forward<F>(f), a);
    }

    template<class F, class A>
    void
    post(F&& f, A const& a) const
    {
        ex().defer(std::forward<F>(f), a);
    }

    template<class F, class A>
    void
    defer(F&& f, A const& a) const
    {
        ex().defer(std::forward<F>(f), a);
    }
};

} // detail
} // beast
} // bho

#endif
