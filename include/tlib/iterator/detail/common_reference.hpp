/**
 * tlib::iterator library
 *
 * Copyright 2012 (c) Tomasz Kamiński
 *
 * Use, modification, and distribution is subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 *    Authors: Tomasz Kamiński (tomaszkam@gmail.com)
 */
#ifndef TLIB_ITERATOR_DETAIL_COMMON_REFERENCE_HPP
#define	TLIB_ITERATOR_DETAIL_COMMON_REFERENCE_HPP

#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/common_type.hpp>

namespace tlib
{
  namespace iterator
  {
    namespace detail
    {
      template<typename Iterator1, typename Iterator2>
      struct common_reference
      {
        typedef typename boost::common_type<
          typename boost::iterator_reference<Iterator1>::type,
          typename boost::iterator_reference<Iterator2>::type
        >::type type;
      };
    }
  }
}

#endif	/* TLIB_ITERATOR_DETAIL_COMMON_REFERENCE_HPP */

