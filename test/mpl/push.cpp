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
#include <tlib/mpl/push.hpp>

using namespace tlib::mpl;

BOOST_AUTO_TEST_SUITE(push_test)

BOOST_AUTO_TEST_CASE(test_push_back)
{
  BOOST_CHECK((std::is_same<
                 typename push_back<vector<>, int>::type,
                 vector<int>
               >::value));
  BOOST_CHECK((std::is_same<
                 typename push_back<vector<>, int, float>::type,
                 vector<int, float>
               >::value));
  BOOST_CHECK((std::is_same<
                 typename push_back<vector<void>, int, float>::type,
                 vector<void, int, float>
               >::value));
  BOOST_CHECK((std::is_same<
                 typename push_back<vector<void, double>, int, float>::type,
                 vector<void, double, int, float>
               >::value));

  BOOST_CHECK((std::is_same<
                 Push_back<vector<>, int>,
                 vector<int>
               >::value));
  BOOST_CHECK((std::is_same<
                 Push_back<vector<>, int, float>,
                 vector<int, float>
               >::value));
  BOOST_CHECK((std::is_same<
                 Push_back<vector<void>, int, float>,
                 vector<void, int, float>
               >::value));
  BOOST_CHECK((std::is_same<
                 Push_back<vector<void, double>, int, float>,
                 vector<void, double, int, float>
               >::value));
}

BOOST_AUTO_TEST_CASE(test_push_front)
{
  BOOST_CHECK((std::is_same<
                 typename push_front<vector<>, int>::type,
                 vector<int>
               >::value));
  BOOST_CHECK((std::is_same<
                 typename push_front<vector<>, int, float>::type,
                 vector<int, float>
               >::value));
  BOOST_CHECK((std::is_same<
                 typename push_front<vector<void>, int, float>::type,
                 vector<int, float, void>
               >::value));
  BOOST_CHECK((std::is_same<
                 typename push_front<vector<void, double>, int, float>::type,
                 vector<int, float, void, double>
               >::value));
  
  BOOST_CHECK((std::is_same<
                 Push_front<vector<>, int>,
                 vector<int>
               >::value));
  BOOST_CHECK((std::is_same<
                 Push_front<vector<>, int, float>,
                 vector<int, float>
               >::value));
  BOOST_CHECK((std::is_same<
                 Push_front<vector<void>, int, float>,
                 vector<int, float, void>
               >::value));
  BOOST_CHECK((std::is_same<
                 Push_front<vector<void, double>, int, float>,
                 vector<int, float, void, double>
               >::value));
}

BOOST_AUTO_TEST_SUITE_END()

#else
  #warning "This test requires C++11 support." 
#endif //C++11