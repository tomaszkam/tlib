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
#ifndef TLIB_ITERATOR_MERGING_ITERATOR_HPP
#define TLIB_ITERATOR_MERGING_ITERATOR_HPP

#include <algorithm>
#include <functional>
#include <cassert>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/and.hpp>
#include <tlib/iterator/detail/merging_iterator_impl.hpp>
#include <tlib/iterator/detail/common_value_type.hpp>
#include <tlib/iterator/constructor_tag.hpp>

namespace tlib
{
  namespace iterator
  {
    template<typename Iterator1, typename Iterator2 = Iterator1,
             typename Compare = 
               std::less<
                 typename boost::remove_const<
                   typename tlib::iterator::detail::common_value_type<Iterator1, Iterator2>::type
                 >::type
               >
            >
    class merging_iterator : private detail::merging_iterator_impl<Iterator1, Iterator2, Compare>,
                             public boost::iterator_facade<
                                      merging_iterator<Iterator1, Iterator2, Compare>,
                                      typename tlib::iterator::detail::common_value_type<Iterator1, Iterator2>::type,
                                      typename detail::merging_iterator_impl<Iterator1, Iterator2, Compare>::traversal,
                                      typename tlib::iterator::detail::common_reference<Iterator1, Iterator2>::type
                                    >
    {
    private:
      typedef detail::merging_iterator_impl<Iterator1, Iterator2, Compare> impl;
      
    public:
      typedef typename impl::iterator1 iterator1;
      typedef typename impl::iterator2 iterator2;
      typedef typename impl::compare   compare;
      
      merging_iterator(compare const &comp_ = compare()) :
        impl(iterator1(), iterator1(), iterator2(), iterator2(),
             true, iterator1(), iterator2(), comp_)
      {}
      
      template<typename I1, typename I2>
      merging_iterator(merging_iterator<I1, I2, compare> const& other,
                       typename boost::enable_if<
                         boost::mpl::and_<
                           boost::is_convertible<I1, iterator1>,
                           boost::is_convertible<I2, iterator2>
                         >
                       >::type* = 0) :
         impl(other.range1_begin, other.range1_end, other.range2_begin, other.range2_end,
              other.use_range1, other.range1_it, other.range2_it, other._comp)
      {}
      
      merging_iterator(begin_t const&,
                       iterator1 const& _range1_begin, iterator1 const& _range1_end,
                       iterator2 const& _range2_begin, iterator2 const& _range2_end,
                       compare const& comp_ = compare())
        : impl(_range1_begin, _range1_end, _range2_begin, _range2_end,
               true, _range1_begin, _range2_begin, comp_)
      {
        this->set_use_range1();
      }

      merging_iterator(end_t const&,
                       iterator1 const& _range1_begin, iterator1 const& _range1_end,
                       iterator2 const& _range2_begin, iterator2 const& _range2_end,
                       compare const& comp_ = compare())
        : impl(_range1_begin, _range1_end, _range2_begin, _range2_end,
               true, _range1_end, _range2_end, comp_)
      {
      }
      
      template<typename I1>
      merging_iterator(from1_t<I1> const& _range1_it,
                       iterator1 const& _range1_begin, iterator1 const& _range1_end,
                       iterator2 const& _range2_begin, iterator2 const& _range2_end,
                       typename boost::enable_if<
                         boost::is_convertible<I1, iterator1>,  
                         compare
                       >::type const& comp_ = compare())
        : impl(_range1_begin, _range1_end, _range2_begin, _range2_end,
               true, _range1_it, _range2_begin, comp_)
      {
        if (this->range2_begin == this->range2_end)
          return;
        
        if (this->range1_begin == this->range1_end)
          this->use_range1 = false;
        else
          this->range2_it = std::lower_bound(this->range2_begin, this->range2_end, *this->range1_it, this->_comp);
      }
      
      template<typename I2>
      merging_iterator(from2_t<I2> const& _range2_it,
                       iterator1 const& _range1_begin, iterator1 const& _range1_end,
                       iterator2 const& _range2_begin, iterator2 const& _range2_end,
                       typename boost::enable_if<
                         boost::is_convertible<I2, iterator2>,  
                         compare
                       >::type const& comp_ = compare())
        : impl(_range1_begin, _range1_end, _range2_begin, _range2_end,
               false, _range1_begin, _range2_it, comp_)
      {
        if (this->range2_begin == this->range2_end)
          this->use_range1 = true;
        else
          this->range1_it = std::upper_bound(this->range1_begin, this->range1_end, *this->range2_it, this->_comp);
      }
      
      bool use1() const { return this->use_range1; }
      iterator1 const& base1() const { return this->range1_it; }
      
      bool use2() const { return !use1(); }
      iterator2 const& base2() const { return this->range2_it; }
      
      compare& comp() { return this->_comp; }
      compare const& comp() const { return this->_comp; }

      iterator1 const& begin1() const { return this->range1_begin; }
      iterator1 const& end1() const { return this->range1_end; } 
      
      iterator2 const& begin2() const { return this->range2_begin; }
      iterator2 const& end2() const { return this->range2_end; }
      
    private:

      merging_iterator(bool start_with_first, iterator1 const& _range1_it, iterator2 const& _range2_it,
                       iterator1 const& _range1_begin, iterator1 const& _range1_end,
                       iterator2 const& _range2_begin, iterator2 const& _range2_end,
                       compare const& comp_ = compare()) :
        impl(_range1_begin, _range1_end, _range2_begin, _range2_end,
             start_with_first, _range1_it, _range2_it, comp_)
      {
      }
      
      friend class boost::iterator_core_access;
      template<typename, typename, typename>
      friend class merging_iterator;
      
      template<typename I1, typename I2, typename C>
      bool equal(merging_iterator<I1,I2,C> const& other) const
      {
        return this->use_range1 == other.use_range1
            && this->range1_it == other.range1_it
            && this->range2_it == other.range2_it;
      }
    };
    
    template<typename ConstructTag, typename Iterator1, typename Iterator2, typename Compare>
    merging_iterator<Iterator1, Iterator2, Compare> make_merging_iterator(
                                                      ConstructTag const& construct_tag,
                                                      Iterator1 const& range1_begin, Iterator1 const& range1_end,
                                                      Iterator2 const& range2_begin, Iterator2 const& range2_end,
                                                      Compare const& comp
                                                    )
    {
      return merging_iterator<Iterator1, Iterator2, Compare>(construct_tag,
                                                             range1_begin, range1_end,
                                                             range2_begin, range2_end,
                                                             comp);
    }
    
    template<typename ConstructTag, typename Iterator1, typename Iterator2>
    merging_iterator<Iterator1, Iterator2> make_merging_iterator(
                                             ConstructTag const& construct_tag,
                                             Iterator1 const& range1_begin, Iterator1 const& range1_end,
                                             Iterator2 const& range2_begin, Iterator2 const& range2_end
                                           )
    {
      return merging_iterator<Iterator1, Iterator2>(construct_tag,
                                                    range1_begin, range1_end,
                                                    range2_begin, range2_end);
    }

  }
}

#endif /* TLIB_ITERATOR_MERGING_ITERATOR_HPP */
