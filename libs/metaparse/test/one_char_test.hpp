// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This header file contains code that is reused by other cpp files

#include <mpllibs/metaparse/is_error.hpp>
#include <mpllibs/metaparse/source_position.hpp>
#include <mpllibs/metaparse/get_result.hpp>
#include <mpllibs/metaparse/get_remaining.hpp>
#include <mpllibs/metaparse/get_position.hpp>
#include <mpllibs/metaparse/iterate_c.hpp>

#include "common.hpp"

#include <mpllibs/metatest/test.hpp>
#include <mpllibs/metatest/has_type.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply_wrap.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

namespace
{
  using mpllibs::metaparse::start;
  
  using boost::mpl::list_c;
  using boost::mpl::apply_wrap2;

  typedef list_c<char, 'a','\n','b'> unix_multi_line_text;
  typedef list_c<char, 'a','\r','\n','b'> dos_multi_line_text;
  typedef list_c<char, 'a','\r','b'> mac_multi_line_text;

  typedef apply_wrap2<oc, str_hello, start> parse_first_char;
}

BOOST_AUTO_TEST_CASE(TEST_NAME)
{
  using mpllibs::metatest::meta_require;
  using mpllibs::metatest::has_type;
  
  using mpllibs::metaparse::get_result;
  using mpllibs::metaparse::get_remaining;
  using mpllibs::metaparse::get_position;
  using mpllibs::metaparse::is_error;
  using mpllibs::metaparse::iterate_c;
  using mpllibs::metaparse::get_line;
  
  using boost::mpl::equal_to;

  meta_require<has_type<oc> >(MPLLIBS_HERE, "test_has_type");

  meta_require<
    equal_to<get_result<parse_first_char>::type, char_h>
  >(MPLLIBS_HERE, "test_for_non_empty_string");

  meta_require<
    equal_to<
      get_result<
        apply_wrap2<
          oc,
          get_remaining<parse_first_char>::type,
          get_position<parse_first_char>::type
        >
      >::type,
      char_e
    >
  >(MPLLIBS_HERE, "test_for_non_empty_string_second");

  meta_require<
    is_error<apply_wrap2<oc, str_, start> >
  >(MPLLIBS_HERE, "test_for_empty_string");
  
  meta_require<
    equal_to<
      int2,
      get_line<
        get_position<
          apply_wrap2<iterate_c<oc, 2>, unix_multi_line_text, start>
        >
      >
    >
  >(MPLLIBS_HERE, "test_unix_multi_line_text");

  meta_require<
    equal_to<
      int2,
      get_line<
        get_position<apply_wrap2<iterate_c<oc, 3>, dos_multi_line_text, start> >
      >
    >
  >(MPLLIBS_HERE, "test_dos_multi_line_text");

  meta_require<
    equal_to<
      int2,
      get_line<
        get_position<apply_wrap2<iterate_c<oc, 2>, mac_multi_line_text, start> >
      >
    >
  >(MPLLIBS_HERE, "test_mac_multi_line_text");
}



