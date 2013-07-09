/**
 * tlib::type_traits library
 *
 * Copyright 2012 (c) Tomasz Kamiński
 *
 * Use, modification, and distribution is subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 *    Authors: Tomasz Kamiński (tomaszkam@gmail.com)
 */
#ifndef TLIB_TYPE_TRAITS_IS_TUPLE_HPP
#define TLIB_TYPE_TRAITS_IS_TUPLE_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <type_traits>
#include <utility>
#include <cstddef>

namespace tlib
{
  namespace type_traits
  {
    namespace detail
    {
      using std::get;
      
      template<typename T> std::false_type check_tuple_size(...);
      template<typename T> std::true_type  check_tuple_size(decltype(std::tuple_size<T>::value)*);
      
      template<std::size_t N, typename T> std::false_type check_tuple_element(...);
      template<std::size_t N, typename T> std::true_type  check_tuple_element(typename std::tuple_element<N,T>::type*);
      
      template<std::size_t N, typename T> std::false_type check_tuple_get(...);
      template<std::size_t N, typename T> 
      typename std::conditional<
        std::is_same<
          typename std::tuple_element<N,T>::type&,
          decltype(get<N>(std::declval<T&>()))
        >::value,
        std::true_type, 
        std::false_type
      >::type check_tuple_get(void*);
    }
    
    template<typename T>
    struct has_tuple_size : decltype(detail::check_tuple_size<T>(nullptr))
    {
    };
    
    template<std::size_t N, typename T>
    struct has_tuple_element : decltype(detail::check_tuple_element<N,T>(nullptr))
    {
    };
    
    template<std::size_t N, typename T>
    struct has_tuple_get 
      : std::integral_constant<bool, has_tuple_element<N,T>::value && decltype(detail::check_tuple_get<N,T>(nullptr))::value> 
    {
    };
    
    namespace detail
    {
      template<std::size_t N, typename T>
      struct has_tuple_get_up_to
        : std::integral_constant<bool, has_tuple_get<N-1, T>::value && has_tuple_get_up_to<N-1, T>::value>
      {
      };
      
      template<typename T>
      struct has_tuple_get_up_to<0, T> : std::true_type
      {
      };
      
      template<typename T>
      struct has_tuple_get_up_to_lazy 
      {
        typedef detail::has_tuple_get_up_to<std::tuple_size<T>::value, T> type;
      };
      
      struct false_type_lazy
      {
        typedef std::false_type type;
      };
    }
   
    template<typename T>
    struct is_tuple
      : std::conditional<
          has_tuple_size<T>::value,
          detail::has_tuple_get_up_to_lazy<T>,
          std::false_type
        >::type::type
    {
    };
  }
}

#endif /* TLIB_TYPE_TRAITS_IS_TUPLE_HPP */
