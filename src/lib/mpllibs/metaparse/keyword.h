#ifndef MPLLIBS_PARSER_KEYWORD_H
#define MPLLIBS_PARSER_KEYWORD_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/lit.h>
#include <mpllibs/metaparse/return.h>
#include <mpllibs/metaparse/sequence.h>
#include <mpllibs/metaparse/second_of.h>

#include <mpllibs/metaparse/util/lazy_if.h>

#include <boost/mpl/if.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>

namespace mpllibs
{
  namespace metaparse
  {
    struct accepted_keyword {};

    template <class s, class result_type>
    struct keyword;
    
    namespace impl
    {
      template <class s, class result_type>
      struct nonemptyKeyword :
        mpllibs::metaparse::second_of<
          mpllibs::metaparse::sequence<
            mpllibs::metaparse::lit<typename boost::mpl::front<s>::type>,
            mpllibs::metaparse::keyword<
              typename boost::mpl::pop_front<s>::type,
              result_type
            >
          >,
          mpllibs::metaparse::return_<result_type>
        >
      {};
    }
    
    // Does not consume/check anything after the keyword
    template <class s, class result_type = accepted_keyword>
    struct keyword :
      mpllibs::metaparse::util::lazy_if<
        boost::mpl::empty<s>,
        mpllibs::metaparse::return_<result_type>,
        mpllibs::metaparse::impl::nonemptyKeyword<s, result_type>
      >::type
    {};
  }
}

#endif

