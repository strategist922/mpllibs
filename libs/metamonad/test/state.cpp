// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metamonad/state.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/quote.hpp>

#include "common.hpp"

using boost::mpl::plus;

namespace
{
  template <class N>
  struct plusn
  {
    typedef plusn type;

    template <class A>
    struct apply
    {
    private:
      struct impl
      {
        typedef impl type;
  
        template <class S>
        struct apply :
          boost::mpl::pair<typename plus<A, N>::type, typename plus<S, N>::type>
        {};
      };
    public:
      typedef impl type;
    };
  };
}

BOOST_AUTO_TEST_CASE(test_state)
{
  using mpllibs::metatest::meta_require;

  using mpllibs::metamonad::state_tag;
  using mpllibs::metamonad::monad;

  using boost::mpl::equal_to;
  using boost::mpl::apply;
  using boost::mpl::int_;
  using boost::mpl::quote1;

  typedef int_<24> int24;
  typedef int_<14> int14;
  typedef apply<monad<state_tag>::return_, int11>::type return11;
  
  meta_require<
    equal_to<int11, apply<return11, int13>::type::first>
  >(MPLLIBS_HERE, "test_return_value");
  
  meta_require<
    equal_to<int13, apply<return11, int13>::type::second>
  >(MPLLIBS_HERE, "test_return_state");

  meta_require<
    equal_to<
      int24,
      apply<
        apply<monad<state_tag>::bind, return11, plusn<int13> >::type,
        int1
      >::type::first
    >
  >(MPLLIBS_HERE, "test_bind_value");

  meta_require<
    equal_to<
      int14,
      apply<
        apply<monad<state_tag>::bind, return11, plusn<int13> >::type,
        int1
      >::type::second
    >
  >(MPLLIBS_HERE, "test_bind_state");
}


