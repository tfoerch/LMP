/*
 * UnknownHelloCTypeParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownHelloCTypeAst.hpp"
#include "obj/UnknownHelloCTypeParser_def.hpp"
#include "obj/LMPParseConfig.hpp"

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      BOOST_SPIRIT_INSTANTIATE(
        unknown_hello_ctype_type, iterator_type, context_type);

    }
  }
}

