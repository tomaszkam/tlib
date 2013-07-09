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
#ifndef TLIB_TYPE_FUNCTIONAL_DETAIL_RESULT_OF_INVOKE_HPP
#define TLIB_TYPE_FUNCTIONAL_DETAIL_RESULT_OF_INVOKE_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <type_traits>
#include <tlib/mpl/vector.hpp>
#include <tlib/mpl/push.hpp>
#include <tlib/mpl/concatenate.hpp>
#include <tlib/functional/detail/expanded.hpp>

namespace tlib
{
  namespace functional
  {
    namespace detail
    {
      template<typename Function, typename Previous, typename... Nexts>
      struct result_of_invoke;
      
      template<typename Function, typename Previous, typename Current, typename... Nexts>
      struct result_of_invoke<Function, Previous, Current, Nexts...>
      {
        typedef typename result_of_invoke<
                  Function, 
                  mpl::Push_back<Previous, Current>, 
                  Nexts...
                >::type type; 
      };
      
      template<typename Function, typename Previous, typename Tuple, typename Indicies, typename... Nexts>
      struct result_of_invoke<Function, Previous, expanded<Tuple, Indicies>, Nexts...>
      {
        typedef typename result_of_invoke<
                  Function,
                  mpl::Concatenate<Previous, typename expanded<Tuple, Indicies>::elements_type>, 
                  Nexts...
                >::type type; 
      };
      
      template<typename Function, typename Previous, typename Tuple, typename Indicies, typename... Nexts>
      struct result_of_invoke<Function, Previous, expanded<Tuple, Indicies>&&, Nexts...>
      {
        typedef typename result_of_invoke<Function, Previous, expanded<Tuple, Indicies>, Nexts...>::type type; 
      };
      
      template<typename Function, typename... Arguments>
      struct result_of_invoke<Function, mpl::vector<Arguments...>>
      {
        typedef typename std::result_of<Function(Arguments...)>::type type; 
      };
      

    }
  }
}

#endif /* TLIB_TYPE_FUNCTIONAL_DETAIL_RESULT_OF_INVOKE_HPP */
