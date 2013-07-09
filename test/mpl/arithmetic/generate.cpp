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

#include <boost/test/unit_test.hpp>
#include <tlib/mpl/arithmetic/integral_vector.hpp>
#include <tlib/mpl/arithmetic/generate.hpp>

using namespace tlib::mpl;
using namespace tlib::mpl::arithmetic;

BOOST_AUTO_TEST_SUITE(generate_test)

BOOST_AUTO_TEST_CASE(test_generate_empty)
{
  BOOST_CHECK((std::is_same<
                typename generate<int, 1, 1>::type,
                integral_vector<int>
              >::value));

  BOOST_CHECK((std::is_same<
                Generate<int, 1, 1>,
                integral_vector<int>
              >::value));
}

BOOST_AUTO_TEST_CASE(test_generate_increment)
{

  BOOST_CHECK((std::is_same<
                 typename generate<int, 1, 4>::type,
                 integral_vector<int, 1, 2, 3>
               >::value));
  BOOST_CHECK((std::is_same<
                typename generate<int, 2, 10>::type,
                integral_vector<int, 2, 3, 4, 5, 6, 7, 8, 9>
              >::value));

  BOOST_CHECK((std::is_same<
                 Generate<int, 1, 4>,
                 integral_vector<int, 1, 2, 3>
               >::value));
  BOOST_CHECK((std::is_same<
                Generate<int, 2, 10>,
                integral_vector<int, 2, 3, 4, 5, 6, 7, 8, 9>
              >::value));
}

BOOST_AUTO_TEST_CASE(test_generate_decrement)
{
  BOOST_CHECK((std::is_same<
                typename generate<int, 4, 1>::type,
                integral_vector<int, 4, 3, 2>
              >::value));
  BOOST_CHECK((std::is_same<
              typename generate<int, 10, 2>::type,
              integral_vector<int, 10, 9, 8, 7, 6, 5, 4, 3>
            >::value));
  BOOST_CHECK((std::is_same<
              Generate<int, 4, 1>,
              integral_vector<int, 4, 3, 2>
            >::value));
  BOOST_CHECK((std::is_same<
              Generate<int, 10, 2>,
              integral_vector<int, 10, 9, 8, 7, 6, 5, 4, 3>
            >::value));
}

BOOST_AUTO_TEST_SUITE_END()

#else
  #warning "This test requires C++11 support." 
#endif //C++11