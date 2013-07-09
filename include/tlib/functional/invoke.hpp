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
#ifndef TLIB_TYPE_FUNCTIONAL_INVOKE_HPP
#define TLIB_TYPE_FUNCTIONAL_INVOKE_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <tlib/functional/detail/result_of_invoke.hpp>
#include <tlib/functional/detail/invoker.hpp>

namespace tlib
{
  namespace functional
  {
      template<typename T>
      struct result_of_invoke;
      
      template<typename FunctionType, typename... ArgumentTypes>
      struct result_of_invoke<FunctionType(ArgumentTypes...)>
      {
        typedef typename detail::result_of_invoke<FunctionType, mpl::vector<>, ArgumentTypes...>::type type;
      };
      
      template<typename T>
      using Result_of_invoke = typename result_of_invoke<T>::type;
      
      template<typename Function, typename... Arguments>
      Result_of_invoke<Function&&(Arguments&&...)> invoke(Function&& function, Arguments&&... arguments)
      {
        detail::invoker<Function&&, Result_of_invoke<Function&&(Arguments&&...)>> invoker;
        return invoker(std::forward<Function&&>(function), std::forward<Arguments&&>(arguments)...);
      }
  }
}

#endif /* TLIB_TYPE_FUNCTIONAL_INVOKE_HPP */
