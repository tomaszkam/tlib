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
#include <tlib/mpl/arithmetic/integral_vector.hpp>

using namespace tlib::mpl;
using namespace tlib::mpl::arithmetic;

BOOST_AUTO_TEST_SUITE(integral_vector_test)

BOOST_AUTO_TEST_CASE(test_integral_vector)
{
  BOOST_CHECK((std::is_same<
                 integral_vector<int>,
                 vector<>
               >::value));
  BOOST_CHECK((std::is_same<
                 integral_vector<int, 10>,
                 vector<std::integral_constant<int, 10>>
               >::value));
  BOOST_CHECK((std::is_same<
                 integral_vector<int, 10, 15>,
                 vector<
                   std::integral_constant<int, 10>, 
                   std::integral_constant<int, 15>
                 >
               >::value));
  BOOST_CHECK((std::is_same<
                 integral_vector<int, 10, 15, 20>,
                 vector<
                   std::integral_constant<int, 10>, 
                   std::integral_constant<int, 15>,
                   std::integral_constant<int, 20>
                 >
               >::value));
  BOOST_CHECK((std::is_same<
                 integral_vector<bool, true, false>,
                 vector<std::true_type, std::false_type>
               >::value));
  
}

BOOST_AUTO_TEST_SUITE_END()

#else
  #warning "This test requires C++11 support." 
#endif //C++11