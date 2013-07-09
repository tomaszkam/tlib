/**
 * tlib::type_traits library
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
#include <utility>
#include <tuple>
#include <array>
#include <boost/test/unit_test.hpp>
#include <tlib/type_traits/is_tuple.hpp>

using namespace tlib::type_traits;

BOOST_AUTO_TEST_SUITE(is_tuple_test)

BOOST_AUTO_TEST_CASE(test_has_tuple_size)
{
  BOOST_CHECK((has_tuple_size<std::tuple<>>::value));
  BOOST_CHECK((has_tuple_size<std::pair<int, int>>::value));
  BOOST_CHECK((has_tuple_size<std::array<int, 2>>::value));
  BOOST_CHECK((!has_tuple_size<int>::value));
}
  
BOOST_AUTO_TEST_CASE(test_has_tuple_element)
{
  BOOST_CHECK((has_tuple_element<0, std::tuple<int>>::value));
  
  BOOST_CHECK((has_tuple_element<0, std::tuple<int, long, int>>::value));
  BOOST_CHECK((has_tuple_element<1, std::tuple<int, long, int>>::value));
  BOOST_CHECK((has_tuple_element<2, std::tuple<int, long, int>>::value));
   
  BOOST_CHECK((has_tuple_element<0, std::pair<int, int>>::value));
  BOOST_CHECK((has_tuple_element<1, std::pair<int, int>>::value));

  BOOST_CHECK((has_tuple_element<0, std::array<int, 3>>::value));
  BOOST_CHECK((has_tuple_element<1, std::array<int, 3>>::value));
  BOOST_CHECK((has_tuple_element<2, std::array<int, 3>>::value));
  
  BOOST_CHECK((!has_tuple_element<0, int>::value));
  BOOST_CHECK((!has_tuple_element<1, int>::value));
}

BOOST_AUTO_TEST_CASE(test_has_tuple_get)
{
  BOOST_CHECK((has_tuple_get<0, std::tuple<int>>::value));
  
  BOOST_CHECK((has_tuple_get<0, std::tuple<int, long, int>>::value));
  BOOST_CHECK((has_tuple_get<1, std::tuple<int, long, int>>::value));
  BOOST_CHECK((has_tuple_get<2, std::tuple<int, long, int>>::value));
   
  BOOST_CHECK((has_tuple_get<0, std::pair<int, int>>::value));
  BOOST_CHECK((has_tuple_get<1, std::pair<int, int>>::value));

  BOOST_CHECK((has_tuple_get<0, std::array<int, 3>>::value));
  BOOST_CHECK((has_tuple_get<1, std::array<int, 3>>::value));
  BOOST_CHECK((has_tuple_get<2, std::array<int, 3>>::value));
  
  BOOST_CHECK((!has_tuple_get<0, int>::value));
  BOOST_CHECK((!has_tuple_get<1, int>::value));
}

BOOST_AUTO_TEST_CASE(test_is_tuple)
{
  BOOST_CHECK((is_tuple<std::tuple<>>::value));
  BOOST_CHECK((is_tuple<std::pair<int, int>>::value));
  BOOST_CHECK((is_tuple<std::array<int, 2>>::value));
  BOOST_CHECK((!is_tuple<int>::value));
}

BOOST_AUTO_TEST_SUITE_END()

#else
  #warning "This test requires C++11 support." 
#endif //C++11