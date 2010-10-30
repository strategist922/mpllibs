#ifndef MPLLIBS_PRINTF_POP_EXPECTED_H
#define MPLLIBS_PRINTF_POP_EXPECTED_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/util/pair.h>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>

namespace mpllibs
{
  namespace safe_printf
  {
    template <class Expected>
    struct PopExpected :
      boost::mpl::eval_if<
        typename boost::mpl::front<Expected>::type::first,
        boost::mpl::push_front<
          typename boost::mpl::pop_front<Expected>::type,
          mpllibs::metaparse::util::pair<
            boost::mpl::false_,
            typename boost::mpl::front<Expected>::type::second
          >
        >,
        boost::mpl::eval_if<
          typename boost::mpl::front<Expected>::type::second::first,
          boost::mpl::push_front<
            typename boost::mpl::pop_front<Expected>::type,
            mpllibs::metaparse::util::pair<
              boost::mpl::false_,
              mpllibs::metaparse::util::pair<
                boost::mpl::false_,
                typename boost::mpl::front<Expected>::type::second::second
              >
            >
          >,
          boost::mpl::pop_front<Expected>
        >
      >
    {};
  }
}

#endif

