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
#ifndef TLIB_TYPE_FUNCTIONAL_DETAIL_EXPANDED_HPP
#define TLIB_TYPE_FUNCTIONAL_DETAIL_EXPANDED_HPP

#if __cplusplus < 201103L //C++11
  #error "This library needs at least a C++11 compliant compiler."
#endif

#include <type_traits>
#include <tuple>
#include <tlib/type_traits/is_tuple.hpp>
#include <tlib/type_traits/apply_same.hpp>
#include <tlib/mpl/vector.hpp>
#include <tlib/mpl/arithmetic/generate.hpp>

namespace tlib
{
  namespace functional
  {
    namespace detail
    {
      template<typename Tuple, typename DecoratedTuple, typename Indicies>
      struct expand_types;
      
      template<typename Tuple, typename DecoratedTuple, std::size_t... Indicies>
      struct expand_types<Tuple, DecoratedTuple, mpl::vector<std::integral_constant<std::size_t, Indicies>...>>
      {
        typedef mpl::vector<
                 typename type_traits::apply_same_as<DecoratedTuple>::
                    template to<
                      typename std::tuple_element<Indicies, Tuple>::type
                    >::type...
                > type;
      };
      
      template<typename T, typename Indicies>
      struct expanded
      {
        typedef typename std::decay<T>::type base_type;
        typedef T                            stored_type;
        typedef Indicies                     indicies_type;
        typedef typename expand_types<
                  base_type, stored_type,
                  indicies_type
                >::type                      elements_type;
        
        expanded(stored_type t) : storage(std::forward<stored_type>(t)) {}
        
        stored_type get() const { return std::forward<stored_type>(storage); }
        operator stored_type() const { return get(); }
        
      private:
        stored_type storage;
      };
         
      template<typename T, 
               std::size_t First = 0, 
               std::size_t Last = std::tuple_size<typename std::decay<T>::type>::value
              >
      using expanded_range = expanded<T, mpl::arithmetic::Generate<std::size_t, First, Last>>;
    }
  }
}

#endif /* TLIB_TYPE_FUNCTIONAL_DETAIL_EXPANDED_HPP */
