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
#ifndef TLIB_ITERATOR_DETAIL_COMMON_VALUE_TYPE_HPP
#define	TLIB_ITERATOR_DETAIL_COMMON_VALUE_TYPE_HPP

#include <boost/type_traits/remove_reference.hpp>
#include <tlib/iterator/detail/common_reference.hpp>

namespace tlib
{
  namespace iterator
  {
    namespace detail
    {
      template<typename Iterator1, typename Iterator2>
      struct common_value_type
      {
        typedef typename boost::remove_reference<
          typename tlib::iterator::detail::common_reference<Iterator1, Iterator2>::type
        >::type type;
      };
    }
  }
}

#endif	/* TLIB_ITERATOR_DETAIL_COMMON_VALUE_TYPE_HPP */

