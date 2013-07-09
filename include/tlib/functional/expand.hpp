/**
 * tlib::functional library
 *
 * Copyright 2012 (c) Tomasz Kamiński
 *
 * Use, modification, and distribution is subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 *    Authors: Tomasz Kamiński (tomaszkam@gmail.com)
 */
#ifndef TLIB_TYPE_FUNCTIONAL_EXPAND_HPP
#define TLIB_TYPE_FUNCTIONAL_EXPAND_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <type_traits>
#include <tlib/type_traits/is_tuple.hpp>
#include <tlib/mpl/arithmetic/integral_vector.hpp>
#include <tlib/functional/detail/expanded.hpp>

namespace tlib
{
  namespace functional
  {
    template<std::size_t First = 0, typename Tuple>
    typename std::enable_if<
      tlib::type_traits::is_tuple<typename std::decay<Tuple>::type>::value,
      detail::expanded_range<Tuple&&, First>
    >::type expand(Tuple&& tuple)
    {
      return detail::expanded_range<Tuple&&, First>(std::forward<Tuple&&>(tuple));
    }
    
    template<std::size_t First, std::size_t Last, typename Tuple>
    typename std::enable_if<
      tlib::type_traits::is_tuple<typename std::decay<Tuple>::type>::value,
      detail::expanded_range<Tuple&&, First, Last>
    >::type expand(Tuple&& tuple)
    {
      return detail::expanded_range<Tuple&&, First, Last>(std::forward<Tuple&&>(tuple));
    }
    
    template<std::size_t... Indicies, typename Tuple>
    typename std::enable_if<
      tlib::type_traits::is_tuple<typename std::decay<Tuple>::type>::value,
      detail::expanded<Tuple&&, tlib::mpl::vector<std::integral_constant<std::size_t, Indicies>...>>
    >::type expand_selected(Tuple&& tuple)
    {
      typedef tlib::mpl::vector<std::integral_constant<std::size_t, Indicies>...> indicies_type;
      return detail::expanded<Tuple&&, indicies_type>(std::forward<Tuple&&>(tuple));
    }
   
    inline namespace expand_operator
    {
      template<typename Tuple>
      typename std::enable_if<
        tlib::type_traits::is_tuple<typename std::decay<Tuple>::type>::value,
        detail::expanded_range<Tuple&&>
      >::type operator*(Tuple&& tuple)
      {
        return expand(std::forward<Tuple&&>(tuple));
      }
    }
  }
}

#endif /* TLIB_TYPE_FUNCTIONAL_EXPAND_HPP */
