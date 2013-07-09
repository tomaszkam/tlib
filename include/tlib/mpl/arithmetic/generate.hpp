/**
 * tlib::mpl::arithmetic library
 *
 * Copyright 2012 (c) Tomasz Kamiński
 *
 * Use, modification, and distribution is subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 *    Authors: Tomasz Kamiński (tomaszkam@gmail.com)
 */
#ifndef TLIB_TYPE_MPL_ARITHMETIC_GENERATE_HPP
#define TLIB_TYPE_MPL_ARITHMETIC_GENERATE_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <type_traits>
#include <tlib/mpl/vector.hpp>
#include <tlib/mpl/push.hpp>

namespace tlib
{
  namespace mpl
  {
    namespace arithmetic
    {
      template<typename T, T First, T Last>
      struct generate;
      
      template<typename T, T First, T Last>
      struct generate
      {
        typedef Push_front<
            typename generate<
              T,
              std::conditional<
                First < Last,
                std::integral_constant<T, First+1>,
                std::integral_constant<T, First-1>
              >::type::value,
              Last
            >::type,
            std::integral_constant<T, First>
        > type;
      };

      template<typename T, T Last>
      struct generate<T, Last, Last>
      {
        typedef vector<> type;
      };
      
      template<typename T, T First, T Last>
      using Generate = typename generate<T, First, Last>::type;
    }
  }
}

#endif /* TLIB_TYPE_MPL_ARITHMETIC_GENERATE_HPP */
