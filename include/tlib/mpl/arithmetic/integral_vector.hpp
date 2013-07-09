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
#ifndef TLIB_TYPE_MPL_ARITHMETIC_INTEGRAL_VECTOR_HPP
#define TLIB_TYPE_MPL_ARITHMETIC_INTEGRAL_VECTOR_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <type_traits>
#include <tlib/mpl/vector.hpp>

namespace tlib
{
  namespace mpl
  {
    namespace arithmetic
    {
      template<typename T, T... Args>
      using integral_vector = vector<std::integral_constant<T, Args>...>;
    }
  }
}

#endif /* TLIB_TYPE_MPL_ARITHMETIC_INTEGRAL_VECTOR_HPP */
