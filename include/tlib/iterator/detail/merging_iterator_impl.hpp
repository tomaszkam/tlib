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
#ifndef TLIB_ITERATOR_DETAIL_MERGING_ITERATOR_IMPL_HPP
#define	TLIB_ITERATOR_DETAIL_MERGING_ITERATOR_IMPL_HPP

#include <boost/iterator/iterator_categories.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <tlib/iterator/detail/common_reference.hpp>
#include <tlib/iterator/detail/common_value_type.hpp>
#include <tlib/iterator/is_compatible.hpp>

namespace tlib
{
  namespace iterator
  {
    namespace detail
    {
      template<typename Iterator1, typename Iterator2, typename Compare,
               typename Traversal = typename boost::mpl::if_<
                  boost::is_convertible<
                    typename boost::common_type<
                      typename boost::iterator_traversal<Iterator1>::type,
                      typename boost::iterator_traversal<Iterator2>::type
                    >::type,
                    boost::bidirectional_traversal_tag
                  >,
                  boost::bidirectional_traversal_tag,
                  typename boost::common_type<
                    typename boost::iterator_traversal<Iterator1>::type,
                    typename boost::iterator_traversal<Iterator2>::type
                  >::type
              >::type
             >
      struct merging_iterator_impl;
      
      template<typename Iterator1, typename Iterator2, typename Compare>
      struct merging_iterator_impl<
               Iterator1, Iterator2, Compare,
               boost::single_pass_traversal_tag
             >
      {
        typedef Iterator1 iterator1;
        typedef Iterator2 iterator2;
        typedef Compare compare;

        typedef boost::single_pass_traversal_tag traversal;

        merging_iterator_impl(iterator1 const& _range1_begin, iterator1 const& _range1_end,
                              iterator2 const& _range2_begin, iterator2 const& _range2_end,
                              bool start_with_range1, iterator1 const& _range1_it, iterator2 const& _range2_it,
                              compare const& comp) :
          range1_begin(_range1_begin), range1_end(_range1_end),
          range2_begin(_range2_begin), range2_end(_range2_end),
          use_range1(start_with_range1), range1_it(_range1_it), range2_it(_range2_it),
          _comp(comp)
        {}

        typename tlib::iterator::detail::common_reference<iterator1, iterator2>::type
        dereference() const
        {
          if (use_range1)
            return *range1_it;
          else
            return *range2_it;
        }

        void increment()
        {
          if (use_range1)
            range1_it++;
          else
            range2_it++;

          set_use_range1();
        }
        
      protected:
        void set_use_range1()
        {
          if (range2_it == range2_end)
            use_range1 = true;
          else if (range1_it == range1_end)
            use_range1 = false; 
          else
            use_range1 = !_comp(*range2_it, *range1_it); //*1 <= *2 
        }
        

        iterator1 range1_begin, range1_end;
        iterator2 range2_begin, range2_end;
        bool use_range1;
        iterator1 range1_it;
        iterator2 range2_it;

        compare _comp;
      };

      template<typename Iterator1, typename Iterator2, typename Compare>
      struct merging_iterator_impl<
              Iterator1, Iterator2, Compare,
              boost::forward_traversal_tag
            > :
        public merging_iterator_impl<
                Iterator1, Iterator2, Compare,
                boost::single_pass_traversal_tag
              >
      {
      private:
        typedef merging_iterator_impl<
                Iterator1, Iterator2, Compare,
                boost::single_pass_traversal_tag
              > parent;
      public:
        typedef typename parent::iterator1 iterator1;
        typedef typename parent::iterator2 iterator2;
        typedef typename parent::compare   compare;

        typedef boost::forward_traversal_tag traversal;

        merging_iterator_impl(iterator1 const& _range1_begin, iterator1 const& _range1_end,
                              iterator2 const& _range2_begin, iterator2 const& _range2_end,
                              bool start_with_range1, iterator1 const& _range1_it, iterator2 const& _range2_it,
                              compare const& comp) :
          parent(_range1_begin, _range1_end, _range2_begin, _range2_end,
                 start_with_range1, _range1_it, _range2_it, comp)
        {}
      };
    
      template<typename Iterator1, typename Iterator2, typename Compare>
      struct merging_iterator_impl<
              Iterator1, Iterator2, Compare,
              boost::bidirectional_traversal_tag
            > :
        public merging_iterator_impl<
                Iterator1, Iterator2, Compare,
                boost::forward_traversal_tag
              >
      {
      private:
        typedef merging_iterator_impl<
                Iterator1, Iterator2, Compare,
                boost::forward_traversal_tag
              > parent;
      public:
        typedef typename parent::iterator1 iterator1;
        typedef typename parent::iterator2 iterator2;
        typedef typename parent::compare   compare;
        
        typedef boost::bidirectional_traversal_tag traversal;
     
        merging_iterator_impl(iterator1 const& _range1_begin, iterator1 const& _range1_end,
                              iterator2 const& _range2_begin, iterator2 const& _range2_end,
                              bool start_with_range1, iterator1 const& _range1_it, iterator2 const& _range2_it,
                              compare const& comp) :
          parent(_range1_begin, _range1_end, _range2_begin, _range2_end,
                 start_with_range1, _range1_it, _range2_it, comp)
        {}

        void decrement()
        {
          if (use_range1)
          {
            if (range2_begin == range2_end)
              return set_prev1();
             
            iterator2 prev_range2_it = range2_it;
            if (range2_it != range2_begin) 
              --prev_range2_it;
              
            if (range1_it != range1_end
             && !_comp(*prev_range2_it, *range1_it)) //*prev2 >= *cur1
              return set_prev1();
            
            if (range1_it == range1_begin)
              return set_prev2();
            
            iterator1 prev_range1_it = range1_it;
            --prev_range1_it;
            
            if (_comp(*prev_range2_it, *prev_range1_it)) //*prev1 > *prev2
              range1_it = prev_range1_it;
            else
              return set_prev2();
          }
          else
          {
            if (range1_begin == range1_end)
              return set_prev2();
            
            iterator1 prev_range1_it = range1_it;
            if (range1_it != range1_begin)
              --prev_range1_it;
            
            if (_comp(*range2_it, *prev_range1_it))  // *prev1 > *cur2
              return set_prev2();
            
            if (range2_it == range2_begin)
              return set_prev1();
            
            iterator2 prev_range2_it = range2_it;
            --prev_range2_it;
            
            if (!_comp(*prev_range2_it, *prev_range1_it)) //*prev2 >= *prev1
              range2_it = prev_range2_it;
            else
              return set_prev1();
          }
        }

      protected:
        using parent::range1_begin;
        using parent::range1_end;
        using parent::range2_begin;
        using parent::range2_end;
        using parent::use_range1;
        using parent::range1_it;
        using parent::range2_it;
        using parent::_comp;
        
      private:
        void set_prev1() {
          use_range1 = true;
          if (range1_it != range1_begin)
            --range1_it;
        }

        void set_prev2() {
          use_range1 = false;
          if (range2_it != range2_begin)
            --range2_it;
        }
      };
    }
  }
}

#endif	/* TLIB_ITERATOR_DETAIL_MERGING_ITERATOR_IMPL_HPP */

