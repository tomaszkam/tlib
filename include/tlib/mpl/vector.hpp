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
#ifndef TLIB_TYPE_MPL_VECTOR_HPP
#define TLIB_TYPE_MPL_VECTOR_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

namespace tlib
{
  namespace mpl
  {
    template<typename... Ts> 
    struct vector {};
    
    template<std::size_t N, typename T>
    struct at;
   
    template<std::size_t N, typename T, typename... Ts>
    struct at<N, vector<T, Ts...>>
    {
      typedef typename at<N-1, vector<Ts...>>::type type;
    };
    
    template<typename T, typename... Ts>
    struct at<0, vector<T, Ts...>>
    {
      typedef T type;
    };
    
    template<std::size_t N, typename T>
    using At = typename at<N, T>::type;
  }
}

#endif /* TLIB_TYPE_MPL_VECTOR_HPP */
