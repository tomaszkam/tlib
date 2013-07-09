/**
 * tlib::type_traits library
 *
 * Copyright 2012 (c) Umasz Kamiński
 *
 * Use, modification, and distribution is subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 *    Authors: Umasz Kamiński (tomaszkam@gmail.com)
 */
#ifndef TLIB_TYPE_TRAITS_APPLY_SAME_HPP
#define TLIB_TYPE_TRAITS_APPLY_SAME_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

namespace tlib
{
  namespace type_traits
  {
    namespace detail
    {
      template<typename T>
      struct apply_same_as
      {
        template<typename U>
        struct to
        {
          typedef U type;
        };
      };
      
      template<typename T>
      struct apply_same_as<T const>
      {
        template<typename U>
        struct to
        {
          typedef typename apply_same_as<T>::template to<U>::type const type;
        };
      };
      
      template<typename T>
      struct apply_same_as<T volatile>
      {
        template<typename U>
        struct to
        {
          typedef typename apply_same_as<T>::template to<U>::type volatile type;
        };
      };
      
      template<typename T>
      struct apply_same_as<T const volatile>
      {
        template<typename U>
        struct to
        {
          typedef typename apply_same_as<T>::template to<U>::type const volatile type;
        };
      };
      
      template<typename T>
      struct apply_same_as<T&>
      {
        template<typename U>
        struct to
        {
          typedef typename apply_same_as<T>::template to<U>::type& type;
        };
      };
      
      template<typename T>
      struct apply_same_as<T&&>
      {
        template<typename U>
        struct to
        {
          typedef typename apply_same_as<T>::template to<U>::type&& type;
        };
      };
    }
    
    template<typename T>
    struct apply_same_as
    {
        template<typename U>
        struct to
        {
          typedef typename detail::apply_same_as<T>::template to<U>::type type;
        };
        

    };
    
    template<typename T>
    struct Apply_same_as
    {
      template<typename U>
      using To = typename apply_same_as<T>::template to<U>::type;
    };
  }
}

#endif /* TLIB_TYPE_TRAITS_APPLY_SAME_HPP */
