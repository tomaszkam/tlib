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
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <tlib/iterator/merging_iterator.hpp>
#include <boost/range/adaptor/filtered.hpp>


BOOST_AUTO_TEST_SUITE(merging_iterator_test)

int a[6] = { 1, 3, 4, 5, 6, 7 };
int b[4] = { 2, 4, 8, 10 };
typedef int* nested_iteator;
typedef tlib::iterator::merging_iterator<int*, int*> int_iterator_typ;

BOOST_AUTO_TEST_CASE(test_default_constructor)
{
  int_iterator_typ it;
  
  BOOST_CHECK(it.use1());
  BOOST_CHECK_EQUAL(it.base1(), nested_iteator());
  
  BOOST_CHECK(!it.use2());
  BOOST_CHECK_EQUAL(it.base2(), nested_iteator());
  
  BOOST_CHECK_EQUAL(it.begin1(), nested_iteator());
  BOOST_CHECK_EQUAL(it.end1(), nested_iteator());

  BOOST_CHECK_EQUAL(it.begin2(), nested_iteator());
  BOOST_CHECK_EQUAL(it.end2(), nested_iteator());
}

BOOST_AUTO_TEST_CASE(test_begin_both_ranges)
{
  int_iterator_typ begin(tlib::iterator::begin, a, a+6, b, b+4), end(tlib::iterator::end, a, a+6, b, b+4);
  
  BOOST_CHECK(begin.use1());
  BOOST_CHECK_EQUAL(begin.base1(), a);
  
  BOOST_CHECK(!begin.use2());
  BOOST_CHECK_EQUAL(begin.base2(), b);
  
  BOOST_CHECK_EQUAL(begin.begin1(), a);
  BOOST_CHECK_EQUAL(begin.end1(), a+6);
  
  BOOST_CHECK_EQUAL(begin.begin2(), b);
  BOOST_CHECK_EQUAL(begin.end2(), b+4);
  
  BOOST_REQUIRE(begin != end);
  BOOST_CHECK_EQUAL(*begin, 1);
}

BOOST_AUTO_TEST_CASE(test_begin_empty1)
{
  int_iterator_typ begin(tlib::iterator::begin, a, a, b, b+4), end(tlib::iterator::end, a, a, b, b+4);
  
  BOOST_CHECK(!begin.use1());
  BOOST_CHECK_EQUAL(begin.base1(), a);
  
  BOOST_CHECK(begin.use2());
  BOOST_CHECK_EQUAL(begin.base2(), b);
  
  BOOST_CHECK_EQUAL(begin.begin1(), a);
  BOOST_CHECK_EQUAL(begin.end1(), a);
  
  BOOST_CHECK_EQUAL(begin.begin2(), b);
  BOOST_CHECK_EQUAL(begin.end2(), b+4);
  
  BOOST_REQUIRE(begin != end);
  BOOST_CHECK_EQUAL(*begin, 2);
}

BOOST_AUTO_TEST_CASE(test_begin_empty2)
{
  int_iterator_typ begin(tlib::iterator::begin,a, a+6, b, b), end(tlib::iterator::end, a, a+6, b, b);
  
  BOOST_CHECK(begin.use1());
  BOOST_CHECK_EQUAL(begin.base1(), a);
  
  BOOST_CHECK(!begin.use2());
  BOOST_CHECK_EQUAL(begin.base2(), b);
  
  BOOST_CHECK_EQUAL(begin.begin1(), a);
  BOOST_CHECK_EQUAL(begin.end1(), a+6);
  
  BOOST_CHECK_EQUAL(begin.begin2(), b);
  BOOST_CHECK_EQUAL(begin.end2(), b);
  
  BOOST_REQUIRE(begin != end);
  BOOST_CHECK_EQUAL(*begin, 1);
}

BOOST_AUTO_TEST_CASE(test_begin_both_empty)
{
  int_iterator_typ begin(tlib::iterator::begin,a, a, b, b), end(tlib::iterator::end, a, a, b, b);
  
  BOOST_CHECK(begin.use1());
  BOOST_CHECK_EQUAL(begin.base1(), a);
  
  BOOST_CHECK(!begin.use2());
  BOOST_CHECK_EQUAL(begin.base2(), b);
  
  BOOST_CHECK_EQUAL(begin.begin1(), a);
  BOOST_CHECK_EQUAL(begin.end1(), a);
  
  BOOST_CHECK_EQUAL(begin.begin2(), b);
  BOOST_CHECK_EQUAL(begin.end2(), b);
  
  BOOST_CHECK(begin == end);
}

BOOST_AUTO_TEST_CASE(test_end)
{
  int_iterator_typ end(tlib::iterator::end, a, a+6, b, b+4);
  
  BOOST_CHECK(end.use1());
  BOOST_CHECK_EQUAL(end.base1(), a+6);
  
  BOOST_CHECK(!end.use2());
  BOOST_CHECK_EQUAL(end.base2(), b+4);

  BOOST_CHECK_EQUAL(end.begin1(), a);
  BOOST_CHECK_EQUAL(end.end1(), a+6);
  
  BOOST_CHECK_EQUAL(end.begin2(), b);
  BOOST_CHECK_EQUAL(end.end2(), b+4);
}

BOOST_AUTO_TEST_CASE(test_from1_both_ranges)
{
  int_iterator_typ from1(tlib::iterator::from1(a+2), a, a+6, b, b+4);
  
  BOOST_CHECK(from1.use1());
  BOOST_CHECK_EQUAL(from1.base1(), a+2);
  
  BOOST_CHECK(!from1.use2());
  BOOST_CHECK_EQUAL(from1.base2(), b+1);
  
  BOOST_CHECK_EQUAL(from1.begin1(), a);
  BOOST_CHECK_EQUAL(from1.end1(), a+6);
  
  BOOST_CHECK_EQUAL(from1.begin2(), b);
  BOOST_CHECK_EQUAL(from1.end2(), b+4);
  
  BOOST_CHECK_EQUAL(*from1, 4);
}

BOOST_AUTO_TEST_CASE(test_from1_empty1)
{
  int_iterator_typ from1(tlib::iterator::from1<int*>(a), a, a, b, b+4);
  
  BOOST_CHECK(!from1.use1());
  BOOST_CHECK_EQUAL(from1.base1(), a);
  
  BOOST_CHECK(from1.use2());
  BOOST_CHECK_EQUAL(from1.base2(), b);
  
  BOOST_CHECK_EQUAL(from1.begin1(), a);
  BOOST_CHECK_EQUAL(from1.end1(), a);
  
  BOOST_CHECK_EQUAL(from1.begin2(), b);
  BOOST_CHECK_EQUAL(from1.end2(), b+4);

  BOOST_CHECK_EQUAL(*from1, 2);
}

BOOST_AUTO_TEST_CASE(test_from1_empty2)
{
  int_iterator_typ from1(tlib::iterator::from1(a+2), a, a+6, b, b);
  
  BOOST_CHECK(from1.use1());
  BOOST_CHECK_EQUAL(from1.base1(), a+2);

  BOOST_CHECK(!from1.use2());
  BOOST_CHECK_EQUAL(from1.base2(), b);
  
  BOOST_CHECK_EQUAL(from1.begin1(), a);
  BOOST_CHECK_EQUAL(from1.end1(), a+6);
  
  BOOST_CHECK_EQUAL(from1.begin2(), b);
  BOOST_CHECK_EQUAL(from1.end2(), b);
  
  BOOST_CHECK_EQUAL(*from1, 4);
}

BOOST_AUTO_TEST_CASE(test_from1_both_empty)
{
  int_iterator_typ from1(tlib::iterator::from1<int*>(a), a, a, b, b);
  
  BOOST_CHECK(from1.use1());
  BOOST_CHECK_EQUAL(from1.base1(), a);
  
  BOOST_CHECK(!from1.use2());
  BOOST_CHECK_EQUAL(from1.base2(), b);
  
  BOOST_CHECK_EQUAL(from1.begin1(), a);
  BOOST_CHECK_EQUAL(from1.end1(), a);
  
  BOOST_CHECK_EQUAL(from1.begin2(), b);
  BOOST_CHECK_EQUAL(from1.end2(), b);
}

BOOST_AUTO_TEST_CASE(test_from2_both_ranges)
{
  int_iterator_typ from2(tlib::iterator::from2(b+1), a, a+6, b, b+4);
  
  BOOST_CHECK(!from2.use1());
  BOOST_CHECK_EQUAL(from2.base1(), a+3);
  
  BOOST_CHECK(from2.use2());
  BOOST_CHECK_EQUAL(from2.base2(), b+1);
  
  BOOST_CHECK_EQUAL(from2.begin1(), a);
  BOOST_CHECK_EQUAL(from2.end1(), a+6);
  
  BOOST_CHECK_EQUAL(from2.begin2(), b);
  BOOST_CHECK_EQUAL(from2.end2(), b+4);
  
  BOOST_CHECK_EQUAL(*from2, 4);
}

BOOST_AUTO_TEST_CASE(test_from2_empty1)
{
  int_iterator_typ from2(tlib::iterator::from2(b+1), a, a, b, b+4);
  
  BOOST_CHECK(!from2.use1());
  BOOST_CHECK_EQUAL(from2.base1(), a);
  
  BOOST_CHECK(from2.use2());
  BOOST_CHECK_EQUAL(from2.base2(), b+1);
  
  BOOST_CHECK_EQUAL(from2.begin1(), a);
  BOOST_CHECK_EQUAL(from2.end1(), a);
  
  BOOST_CHECK_EQUAL(from2.begin2(), b);
  BOOST_CHECK_EQUAL(from2.end2(), b+4);
  
  BOOST_CHECK_EQUAL(*from2, 4);
}

BOOST_AUTO_TEST_CASE(test_from2_empty2)
{
  int_iterator_typ from2(tlib::iterator::from2<int*>(b), a, a+6, b, b);
  
  BOOST_CHECK(from2.use1());
  BOOST_CHECK_EQUAL(from2.base1(), a);
  
  BOOST_CHECK(!from2.use2());
  BOOST_CHECK_EQUAL(from2.base2(), b);
  
  BOOST_CHECK_EQUAL(from2.begin1(), a);
  BOOST_CHECK_EQUAL(from2.end1(), a+6);
  
  BOOST_CHECK_EQUAL(from2.begin2(), b);
  BOOST_CHECK_EQUAL(from2.end2(), b);
  
  BOOST_CHECK_EQUAL(*from2, 1);
}

BOOST_AUTO_TEST_CASE(test_from2_both_empty)
{
  int_iterator_typ from2(tlib::iterator::from2<int*>(b), a, a, b, b);
  
  BOOST_CHECK(from2.use1());
  BOOST_CHECK_EQUAL(from2.base1(), a);
  
  BOOST_CHECK(!from2.use2());
  BOOST_CHECK_EQUAL(from2.base2(), b);
  
  BOOST_CHECK_EQUAL(from2.begin1(), a);
  BOOST_CHECK_EQUAL(from2.end1(), a);
  
  BOOST_CHECK_EQUAL(from2.begin2(), b);
  BOOST_CHECK_EQUAL(from2.end2(), b);
}

BOOST_AUTO_TEST_CASE(test_forward_iteration_both_ranges)
{
  int_iterator_typ begin(tlib::iterator::begin,a, a+6, b, b+4), end(tlib::iterator::end, a, a+6, b, b+4);
  tlib::iterator::merging_iterator<int*, int const*> it = begin;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 1 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[0] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 2 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[0] );
  it++;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 3 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[1] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 4 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[2] );
  it++;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 4 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[1] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 5 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[3] );
  it++;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 6 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[4] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 7 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[5] );
  it++;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 8 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[2] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 10 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[3] );
  it++;
  
  BOOST_CHECK( it == end );
}

BOOST_AUTO_TEST_CASE(test_forward_iteration_empty1)
{
  int_iterator_typ begin(tlib::iterator::begin,a, a, b, b+4), end(tlib::iterator::end, a, a, b, b+4);
  tlib::iterator::merging_iterator<int const*,int*> it = begin;
    
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 2 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[0] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 4 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[1] );
  it++;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 8 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[2] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 10 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[3] );
  it++;
  
  BOOST_CHECK( it == end );
}

BOOST_AUTO_TEST_CASE(test_forward_iteration_empty2)
{
  int_iterator_typ begin(tlib::iterator::begin,a, a+6, b, b), end(tlib::iterator::end, a, a+6, b, b);
  tlib::iterator::merging_iterator<int const*, int const*> it = begin;

  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 1 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[0] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 3 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[1] );
  it++;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 4 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[2] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 5 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[3] );
  it++;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 6 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[4] );
  ++it;
  
  BOOST_REQUIRE( it != end );
  BOOST_CHECK_EQUAL( *it, 7 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[5] );
  it++;
  
  BOOST_CHECK( it == end );
}

BOOST_AUTO_TEST_CASE(test_reverse_iteration_both_ranges)
{
  int_iterator_typ begin(tlib::iterator::begin,a, a+6, b, b+4), end(tlib::iterator::end, a, a+6, b, b+4);
  tlib::iterator::merging_iterator<int*, int const*> it = end;
  
  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 10 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[3] );

  BOOST_REQUIRE( it != begin );
  --it;
  BOOST_CHECK_EQUAL( *it, 8 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[2] );
  
  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 7 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[5] );
  
  BOOST_REQUIRE( it != end );
  --it;
  BOOST_CHECK_EQUAL( *it, 6 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[4] );

  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 5 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[3] );

  BOOST_REQUIRE( it != begin );
  --it;
  BOOST_CHECK_EQUAL( *it, 4 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[1] );

  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 4 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[2] );

  BOOST_REQUIRE( it != begin );
  --it;
  BOOST_CHECK_EQUAL( *it, 3 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[1] );
  
  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 2 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[0] );

  BOOST_REQUIRE( it != begin );
  --it;
  BOOST_CHECK_EQUAL( *it, 1 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[0] );

  BOOST_CHECK( it == begin );
}

BOOST_AUTO_TEST_CASE(test_reverse_iteration_both_empty1)
{
  int_iterator_typ begin(tlib::iterator::begin,a, a, b, b+4), end(tlib::iterator::end, a, a, b, b+4);
  tlib::iterator::merging_iterator<int*, int const*> it = end;
  
  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 10 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[3] );

  BOOST_REQUIRE( it != begin );
  --it;
  BOOST_CHECK_EQUAL( *it, 8 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[2] );

  BOOST_REQUIRE( it != begin );
  --it;
  BOOST_CHECK_EQUAL( *it, 4 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[1] );
  
  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 2 );
  BOOST_CHECK( it.use2() );
  BOOST_CHECK_EQUAL( it.base2(), &b[0] );

  BOOST_CHECK( it == begin );
}

BOOST_AUTO_TEST_CASE(test_reverse_iteration_empty2)
{
  int_iterator_typ begin(tlib::iterator::begin,a, a+6, b, b), end(tlib::iterator::end, a, a+6, b, b);
  tlib::iterator::merging_iterator<int*, int const*> it = end;
  
  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 7 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[5] );
  
  BOOST_REQUIRE( it != end );
  --it;
  BOOST_CHECK_EQUAL( *it, 6 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[4] );

  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 5 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[3] );

  BOOST_REQUIRE( it != begin );
  it--;
  BOOST_CHECK_EQUAL( *it, 4 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[2] );

  BOOST_REQUIRE( it != begin );
  --it;
  BOOST_CHECK_EQUAL( *it, 3 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[1] );

  BOOST_REQUIRE( it != begin );
  --it;
  BOOST_CHECK_EQUAL( *it, 1 );
  BOOST_CHECK( it.use1() );
  BOOST_CHECK_EQUAL( it.base1(), &a[0] );

  BOOST_CHECK( it == begin );
}

BOOST_AUTO_TEST_SUITE_END()

