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
#include <tlib/mpl/concatenate.hpp>

using namespace tlib::mpl;

BOOST_AUTO_TEST_SUITE(concatenate_test)

BOOST_AUTO_TEST_CASE(test_concatenate_two_elements)
{
  BOOST_CHECK((std::is_same<
                 typename concatenate<vector<>, vector<>>::type,
                 vector<>
               >::value));
  BOOST_CHECK((std::is_same<
                typename concatenate<vector<>, vector<int, float>>::type,
                vector<int, float>
              >::value));
  BOOST_CHECK((std::is_same<
              typename concatenate<vector<int, float>, vector<>>::type,
              vector<int, float>
            >::value));
  BOOST_CHECK((std::is_same<
              typename concatenate<vector<int, float>, vector<double, int, float>>::type,
              vector<int, float, double, int, float>
            >::value));
  
  BOOST_CHECK((std::is_same<
                 Concatenate<vector<>, vector<>>,
                 vector<>
               >::value));
  BOOST_CHECK((std::is_same<
                Concatenate<vector<>, vector<int, float>>,
                vector<int, float>
              >::value));
  BOOST_CHECK((std::is_same<
              Concatenate<vector<int, float>, vector<>>,
              vector<int, float>
            >::value));
  BOOST_CHECK((std::is_same<
              Concatenate<vector<int, float>, vector<double, int, float>>,
              vector<int, float, double, int, float>
            >::value));
}

BOOST_AUTO_TEST_CASE(test_concatenate_multple_elements)
{
  BOOST_CHECK((std::is_same<
                 typename concatenate<vector<>, vector<>, vector<>>::type,
                 vector<>
               >::value));
  BOOST_CHECK((std::is_same<
                typename concatenate<vector<>, vector<int, float>, vector<>>::type,
                vector<int, float>
              >::value));
  BOOST_CHECK((std::is_same<
              typename concatenate<vector<int, float>, vector<double>, vector<int, float>>::type,
              vector<int, float, double, int, float>
            >::value));
  BOOST_CHECK((std::is_same<
                typename concatenate<vector<int, float>, vector<double>, vector<int, float>, vector<vector<int>>>::type,
                vector<int, float, double, int, float, vector<int>>
               >::value));
  
  BOOST_CHECK((std::is_same<
                 Concatenate<vector<>, vector<>, vector<>>,
                 vector<>
               >::value));
  BOOST_CHECK((std::is_same<
                Concatenate<vector<>, vector<int, float>, vector<>>,
                vector<int, float>
              >::value));
  BOOST_CHECK((std::is_same<
              Concatenate<vector<int, float>, vector<double>, vector<int, float>>,
              vector<int, float, double, int, float>
            >::value));
  BOOST_CHECK((std::is_same<
                Concatenate<vector<int, float>, vector<double>, vector<int, float>, vector<vector<int>>>,
                vector<int, float, double, int, float, vector<int>>
               >::value));
}

BOOST_AUTO_TEST_SUITE_END()

#else
  #warning "This test requires C++11 support." 
#endif //C++11