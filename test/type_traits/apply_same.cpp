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
#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <tlib/type_traits/apply_same.hpp>

using namespace tlib::type_traits;

BOOST_AUTO_TEST_SUITE(apply_same_test)

BOOST_AUTO_TEST_CASE(test_none)
{
  BOOST_CHECK((std::is_same<
                 typename apply_same_as<int>::to<float>::type,
                 float
               >::value));

  BOOST_CHECK((std::is_same<
                 Apply_same_as<int>::To<float>,
                 float
               >::value));
}
 
BOOST_AUTO_TEST_CASE(test_cv)
{
  BOOST_CHECK((std::is_same<
                 typename apply_same_as<int const>::to<float>::type,
                 float const
               >::value));
  BOOST_CHECK((std::is_same<
                 typename apply_same_as<int volatile>::to<float>::type,
                 float volatile
               >::value));
  BOOST_CHECK((std::is_same<
                typename apply_same_as<int const volatile>::to<float>::type,
                float const volatile
              >::value));
  
  BOOST_CHECK((std::is_same<
                 Apply_same_as<int const>::To<float>,
                 float const
               >::value));
  BOOST_CHECK((std::is_same<
                 Apply_same_as<int volatile>::To<float>,
                 float volatile
               >::value));
  BOOST_CHECK((std::is_same<
                 Apply_same_as<int const volatile>::To<float>,
                 float const volatile
              >::value));
}

BOOST_AUTO_TEST_CASE(test_rvalue_ref)
{
  BOOST_CHECK((std::is_same<
                 typename apply_same_as<int&&>::to<float>::type,
                 float&&
               >::value));
  BOOST_CHECK((std::is_same<
                 typename apply_same_as<int const&&>::to<float>::type,
                 float const&&
               >::value));
  BOOST_CHECK((std::is_same<
                 typename apply_same_as<int volatile&&>::to<float>::type,
                 float volatile&&
               >::value));
  BOOST_CHECK((std::is_same<
                 typename apply_same_as<int const volatile&&>::to<float>::type,
                 float const volatile&&
              >::value));
  
  BOOST_CHECK((std::is_same<
                 Apply_same_as<int&&>::To<float>,
                 float&&
               >::value));
  BOOST_CHECK((std::is_same<
                 Apply_same_as<int const&&>::To<float>,
                 float const&&
               >::value));
  BOOST_CHECK((std::is_same<
                 Apply_same_as<int volatile&&>::To<float>,
                 float volatile&&
               >::value));
  BOOST_CHECK((std::is_same<
                 Apply_same_as<int const volatile&&>::To<float>,
                 float const volatile&&
              >::value));
}

BOOST_AUTO_TEST_SUITE_END()

#else
  #warning "This test requires C++11 support." 
#endif //C++11