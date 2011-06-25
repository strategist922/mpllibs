#ifndef MPLLIBS_METAPARSE_UTIL_IS_LETTER_HPP
#define MPLLIBS_METAPARSE_UTIL_IS_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/util/is_ucase_letter.hpp>
#include <mpllibs/metaparse/util/is_lcase_letter.hpp>

#include <mpllibs/metatest/to_stream.hpp>

#include <boost/mpl/or.hpp>
#include <boost/mpl/apply.hpp>

namespace mpllibs
{
  namespace metaparse
  {
    namespace util
    {
      struct is_letter
      {
        typedef is_letter type;
        
        template <class S>
        struct apply :
          boost::mpl::or_<
            boost::mpl::apply<is_lcase_letter, S>,
            boost::mpl::apply<is_ucase_letter, S>
          >
        {};
      };
    }
  }
}

MPLLIBS_DEFINE_TO_STREAM_FOR_TYPE(
  mpllibs::metaparse::util::is_letter,
  "is_letter"
)

#endif

