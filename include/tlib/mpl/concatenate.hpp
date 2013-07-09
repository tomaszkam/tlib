/**
 * tlib::mpl library
 *
 * Copyright 2012 (c) Tomasz Kamiński
 *
 * Use, modification, and distribution is subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 *    Authors: Tomasz Kamiński (tomaszkam@gmail.com)
 */
#ifndef TLIB_TYPE_MPL_CONCATENATE_HPP
#define TLIB_TYPE_MPL_CONCATENATE_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <tlib/mpl/vector.hpp>

namespace tlib
{
  namespace mpl
  {
    template<typename T1, typename T2, typename... Ts>
    struct concatenate
    {
      typedef typename concatenate<typename concatenate<T1, T2>::type, Ts...>::type type;
    };
    
    template<typename... T1s, typename... T2s>
    struct concatenate<vector<T1s...>, vector<T2s...>>
    {
      typedef vector<T1s..., T2s...> type;
    };
    
    template<typename T1, typename T2, typename... Ts>
    using Concatenate = typename concatenate<T1, T2, Ts...>::type;
  }
}

#endif /* TLIB_TYPE_MPL_CONCATENATE_HPP */
