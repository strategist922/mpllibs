// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metamonad/writer.hpp>
#include <mpllibs/metamonad/list.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/plus.hpp>

#include "common.hpp"

using boost::mpl::list;
using boost::mpl::pair;
using boost::mpl::plus;
  
namespace
{
  template <class A>
  struct log_plus
  {
    typedef log_plus type;
    
    template <class R>
    struct apply : pair<plus<A, R>, list<A> > {};
  };

}

BOOST_AUTO_TEST_CASE(test_writer)
{
  using mpllibs::metatest::meta_require;

  using mpllibs::metamonad::writer_tag;
  using mpllibs::metamonad::list_tag;
  using mpllibs::metamonad::monad;
  
  using boost::mpl::equal_to;
  using boost::mpl::equal;
  using boost::mpl::apply;

  typedef writer_tag<list_tag> list_writer_tag;
  
  typedef apply<monad<list_writer_tag>::return_, int11>::type return11;
  
  meta_require<
    equal_to<int11, return11::first>
  >(MPLLIBS_HERE, "test_return_value");
  
  meta_require<
    equal<list<>, return11::second>
  >(MPLLIBS_HERE, "test_return_log");

  meta_require<
    equal_to<
      int13,
      apply<
        monad<list_writer_tag>::bind,
        return11,
        log_plus<int2>
      >::type::first
    >
  >(MPLLIBS_HERE, "test_bind_value");

  meta_require<
    equal<
      list<int2>,
      apply<
        monad<list_writer_tag>::bind,
        return11,
        log_plus<int2>
      >::type::second
    >
  >(MPLLIBS_HERE, "test_bind_log");
}


