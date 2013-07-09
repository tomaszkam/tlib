/**
 * tlib::mpl library
 *
 * Copyright 2012 (c) Tomasz Kamiński
 *
 * Use, modification, and distribution is subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 *    Authors: Tomasz Kamiński (tomaszkam@gmail.com)
 */
#if __cplusplus >= 201103L //C++11

#define BOOST_TEST_DYN_LINK

#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <tlib/mpl/vector.hpp>

using namespace tlib::mpl;

BOOST_AUTO_TEST_SUITE(vector_test)

BOOST_AUTO_TEST_CASE(test_at)
{
  typedef vector<int, double, float, void> test_vector;

  BOOST_CHECK((std::is_same<typename at<0, test_vector>::type, int>::value));
  BOOST_CHECK((std::is_same<typename at<1, test_vector>::type, double>::value));
  BOOST_CHECK((std::is_same<typename at<2, test_vector>::type, float>::value));
  BOOST_CHECK((std::is_same<typename at<3, test_vector>::type, void>::value));
  
  BOOST_CHECK((std::is_same<At<0, test_vector>, int>::value));
  BOOST_CHECK((std::is_same<At<1, test_vector>, double>::value));
  BOOST_CHECK((std::is_same<At<2, test_vector>, float>::value));
  BOOST_CHECK((std::is_same<At<3, test_vector>, void>::value));
}

BOOST_AUTO_TEST_SUITE_END()

#else
  #warning "This test requires C++11 support." 
#endif //C++11