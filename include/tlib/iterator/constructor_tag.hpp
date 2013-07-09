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
#ifndef TLIB_ITERATOR_CONSTRUCTOR_TAG_HPP
#define TLIB_ITERATOR_CONSTRUCTOR_TAG_HPP

#include <boost/utility/enable_if.hpp>

namespace tlib
{
  namespace iterator
  {
   
    struct begin_t {};
    extern begin_t const begin;
    
    struct end_t {};
    extern end_t const end;
    
    template<typename Iterator>
    struct from_t
    {
      explicit from_t(Iterator const& iterator) : _iterator(iterator) {}
      
      operator Iterator const&() const { return _iterator; }
      
    private:
      Iterator const& _iterator;
    };
    
    template<typename Iterator>
    inline from_t<Iterator> from(Iterator const& iterator)
    {
      return from_t<Iterator>(iterator);
    }
    
    template<typename Iterator>
    struct from1_t : public from_t<Iterator>
    {
      explicit from1_t(Iterator const& iterator) : from_t<Iterator>(iterator) {}
    };
    
    template<typename Iterator>
    inline from1_t<Iterator> from1(Iterator const& iterator)
    {
      return from1_t<Iterator>(iterator);
    }
    
    template<typename T>
    inline from1_t<T*> from1(T* const& iterator)
    {
      return from1_t<T*>(iterator);
    }
    
    template<typename Iterator>
    struct from2_t : public from_t<Iterator>
    {
      explicit from2_t(Iterator const& iterator) : from_t<Iterator>(iterator) {}
    };
    
    template<typename Iterator>
    inline from2_t<Iterator> from2(Iterator const& iterator)
    {
      return from2_t<Iterator>(iterator);
    }
  }
}

#endif /* TLIB_ITERATOR_CONSTRUCTOR_TAG_HPP */
