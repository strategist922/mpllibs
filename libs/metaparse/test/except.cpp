// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metaparse/except.hpp>
#include <mpllibs/metaparse/one_char.hpp>
#include <mpllibs/metaparse/fail.hpp>
#include <mpllibs/metaparse/is_error.hpp>
#include <mpllibs/metaparse/source_position.hpp>
#include <mpllibs/metaparse/get_result.hpp>

#include "common.hpp"

#include <mpllibs/metatest/has_type.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply_wrap.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_except)
{
  using mpllibs::metatest::has_type;
  using mpllibs::metatest::meta_require;
  
  using mpllibs::metaparse::is_error;
  using mpllibs::metaparse::except;
  using mpllibs::metaparse::one_char;
  using mpllibs::metaparse::start;
  using mpllibs::metaparse::get_result;
  using mpllibs::metaparse::fail;
  
  using boost::mpl::apply_wrap2;
  using boost::mpl::equal_to;
  using boost::mpl::string;

  typedef string<'fail'> test_error_msg;

  meta_require<
    has_type<except<one_char, int13, test_error_msg> >
  >(MPLLIBS_HERE, "test_has_type");

  meta_require<
    is_error<
      apply_wrap2<except<one_char, int13, test_error_msg>, str_hello, start>
    >
  >(MPLLIBS_HERE, "test_with_good");
  
  meta_require<
    equal_to<
      get_result<
        apply_wrap2<
          except<fail<test_error_msg>, int13, test_error_msg>,
          str_hello,
          start
        >
      >::type,
      int13
    >
  >(MPLLIBS_HERE, "test_with_bad");
}



