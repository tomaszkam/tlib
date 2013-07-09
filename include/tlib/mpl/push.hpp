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
#ifndef TLIB_TYPE_MPL_PUSH_HPP
#define TLIB_TYPE_MPL_PUSH_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <tlib/mpl/vector.hpp>

namespace tlib
{
  namespace mpl
  {
    template<typename V, typename T, typename... Ts>
    struct push_back;
    
    template<typename... TVs, typename T, typename... Ts>
    struct push_back<vector<TVs...>, T, Ts...>
    {
      typedef vector<TVs..., T, Ts...> type;
    };
    
    template<typename V, typename T, typename... Ts>
    using Push_back = typename push_back<V, T, Ts...>::type;
    
    template<typename V, typename T, typename... Ts>
    struct push_front;
    
    template<typename... TVs, typename T, typename... Ts>
    struct push_front<vector<TVs...>, T, Ts...>
    {
      typedef vector<T, Ts..., TVs...> type;
    };
    
    template<typename V, typename T, typename... Ts>
    using Push_front = typename push_front<V, T, Ts...>::type;
  }
}

#endif /* TLIB_TYPE_MPL_PUSH_BACK_HPP */
