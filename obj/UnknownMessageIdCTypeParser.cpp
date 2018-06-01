/*
 * UnknownMessageIdCTypeParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownMessageIdCTypeAst.hpp"
#include "obj/UnknownMessageIdCTypeParser_def.hpp"
#include "obj/LMPParseConfig.hpp"

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      BOOST_SPIRIT_INSTANTIATE(
        unknown_message_id_ctype_type, iterator_type, context_type);

    }
  }
}

