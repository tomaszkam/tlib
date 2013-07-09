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
#ifndef TLIB_TYPE_FUNCTIONAL_DETAIL_INVOKER_HPP
#define TLIB_TYPE_FUNCTIONAL_DETAIL_INVOKER_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <type_traits>
#include <tlib/mpl/vector.hpp>
#include <tlib/functional/detail/expanded.hpp>

namespace tlib
{
  namespace functional
  {
    namespace detail
    {
      template<typename Function, typename Result, typename... Previous>
      struct invoker
      {
        Result operator()(Function function, Previous... previous) const
        {
          return function(std::forward<Previous>(previous)...);
        }
        
        template<typename Current, typename... Next>
        Result operator()(Function function, Previous... previous, Current&& current, Next&&... next) const
        {
          invoker<Function, Result, Previous..., Current&&> next_invoker;
          return next_invoker(std::forward<Function>(function),
                              std::forward<Previous>(previous)..., 
                              std::forward<Current>(current),
                              std::forward<Next>(next)...);
        }
        
        template<typename Tuple, typename Indicies, typename... Next>
        Result operator()(Function function, Previous... previous, expanded<Tuple, Indicies>&& expanded_element, Next&&... next) const
        {
          unwind_invoker<expanded<Tuple, Indicies>> next_invoker;
          return next_invoker(std::forward<Function>(function),
                              std::forward<Previous>(previous)..., 
                              expanded_element.get(),
                              std::forward<Next>(next)...);
        }
        
      private:
        template<typename Expanded, 
                 typename Indicies = typename Expanded::indicies_type,
                 typename Elements = typename Expanded::elements_type>
        struct unwind_invoker;
        
        template<typename Expanded, std::size_t... Indicies, typename... Elements>
        struct unwind_invoker<
                Expanded,
                mpl::vector<std::integral_constant<std::size_t, Indicies>...>,
                mpl::vector<Elements...>
               >
        {
          template<typename... Next>
          Result operator()(Function function, Previous... previous, typename Expanded::stored_type tuple, Next&&... next) const
          {
            invoker<Function, Result, Previous..., Elements...> next_invoker;
            return next_invoker(std::forward<Function>(function),
                                std::forward<Previous>(previous)..., 
                                std::forward<Elements>(std::get<Indicies>(tuple))...,
                                std::forward<Next>(next)...);
          }
        };
      };
    }
  }
}

#endif /* TLIB_TYPE_FUNCTIONAL_DETAIL_INVOKER_HPP */
