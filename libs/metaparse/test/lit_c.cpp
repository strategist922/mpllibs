// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/is_error.hpp>
#include <mpllibs/metaparse/source_position.hpp>
#include <mpllibs/metaparse/get_result.hpp>
#include <mpllibs/metaparse/get_remaining.hpp>
#include <mpllibs/metaparse/get_position.hpp>

#include "common.hpp"

#include <mpllibs/metatest/test.hpp>
#include <mpllibs/metatest/has_type.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply.hpp>

using mpllibs::metatest::suite_path;
using mpllibs::metatest::has_type;

using mpllibs::metaparse::get_result;
using mpllibs::metaparse::start;
using mpllibs::metaparse::is_error;
using mpllibs::metaparse::get_remaining;
using mpllibs::metaparse::get_position;

using boost::mpl::equal_to;
using boost::mpl::apply;

namespace
{
  const suite_path suite("lit_c");

  typedef has_type<lit_c_h> test_has_type;

  typedef
    equal_to<get_result<apply<lit_c_h, str_hello, start> >::type, char_h>
    test_accept;

  typedef is_error<apply<lit_c_h, str_bello, start> > test_reject;

  typedef is_error< apply<lit_c_h, str_, start> > test_with_empty_string;

  typedef
    equal_to<
      get_result<
        apply<
          lit_c_e,
          get_remaining<apply<lit_c_h, str_hello, start> >::type,
          get_position<apply<lit_c_h, str_hello, start> >::type
        >
      >::type,
      char_e
    >
    test_remaining_string;
}

MPLLIBS_ADD_TEST(suite, test_has_type)
MPLLIBS_ADD_TEST(suite, test_accept)
MPLLIBS_ADD_TEST(suite, test_reject)
MPLLIBS_ADD_TEST(suite, test_with_empty_string)
MPLLIBS_ADD_TEST(suite, test_remaining_string)

