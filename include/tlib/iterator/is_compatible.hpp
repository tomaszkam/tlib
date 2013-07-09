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
#ifndef TLIB_ITERATOR_IS_COMPATIBLE_HPP
#define	TLIB_ITERATOR_IS_COMPATIBLE_HPP

#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/interoperable.hpp>

namespace tlib
{
  namespace iterator
  {
    template<typename Iterator1, typename Iterator2>
    struct is_compatible 
      : public boost::is_interoperable<
          typename boost::iterator_reference<Iterator1>::type,
          typename boost::iterator_reference<Iterator2>::type
        >
    {
    };
  }
}

#endif	/* TLIB_ITERATOR_IS_COMPATIBLE_HPP */

