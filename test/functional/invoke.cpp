/**
 * tlib::functional library
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

#include <tuple>
#include <boost/test/unit_test.hpp>
#include <tlib/functional/expand.hpp>
#include <tlib/functional/invoke.hpp>

using namespace tlib::functional;

BOOST_AUTO_TEST_SUITE(unwind_test)

template<typename T>
void f(T);

struct A {
  A(A const&) = delete;
  A(A &&) = delete;
  A() {}
};

struct G
{
  float operator()(int&& a, int&& b, A&& c)
  {
    return 0.5;
  }
};


BOOST_AUTO_TEST_CASE(test_unwind)
{
  invoke(G(), expand_selected<1, 2, 0>(std::tuple<A,int,int,int>()));  
}

BOOST_AUTO_TEST_SUITE_END()

#else
  #warning "This test requires C++11 support." 
#endif //C++11