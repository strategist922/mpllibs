// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/token.hpp>
#include <mpllibs/metaparse/keyword.hpp>
#include <mpllibs/metaparse/is_error.hpp>
#include <mpllibs/metaparse/source_position.hpp>
#include <mpllibs/metaparse/get_result.hpp>
#include <mpllibs/metaparse/get_remaining.hpp>

#include "common.hpp"

#include <mpllibs/metatest/test.hpp>
#include <mpllibs/metatest/has_type.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/equal.hpp>

using mpllibs::metatest::suite_path;
using mpllibs::metatest::has_type;

using mpllibs::metaparse::keyword;
using mpllibs::metaparse::get_result;
using mpllibs::metaparse::token;
using mpllibs::metaparse::start;
using mpllibs::metaparse::get_remaining;
using mpllibs::metaparse::is_error;

using boost::mpl::list_c;
using boost::mpl::equal_to;
using boost::mpl::apply;
using boost::mpl::equal;

namespace
{
  const suite_path suite("token");

  typedef list_c<char, 'h', 'e', 'l', 'l', 'o', ' ', '\t'> str_hello_t;
      
  typedef keyword<str_hello, int13> test_parser;
  typedef token<test_parser> test_token;

  typedef has_type<test_token> test_has_type;

  typedef
    equal_to<
      get_result<apply<test_token, str_hello, start> >::type,
      get_result<apply<test_parser, str_hello, start> >::type
    >
    test_no_space;

  typedef
    equal_to<
      get_result<apply<test_token, str_hello_t, start> >::type,
      get_result<apply<test_parser, str_hello, start> >::type
    >
    test_spaces;

  typedef
    equal<get_remaining<apply<test_token, str_hello_t, start> >::type, str_>
    test_spaces_consumed;

  typedef is_error<apply<test_token, str_, start> > test_fail;
}

MPLLIBS_ADD_TEST(suite, test_has_type)
MPLLIBS_ADD_TEST(suite, test_no_space)
MPLLIBS_ADD_TEST(suite, test_spaces)
MPLLIBS_ADD_TEST(suite, test_spaces_consumed)
MPLLIBS_ADD_TEST(suite, test_fail)


