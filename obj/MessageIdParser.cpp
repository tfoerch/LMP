/*
 * MessageIdParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAst.hpp"
#include "obj/MessageIdParser_def.hpp"
#include "obj/ObjectHeaderParser_def.hpp"
#include "obj/LMPParseConfig.hpp"

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      BOOST_SPIRIT_INSTANTIATE(
        message_id_type, iterator_type, context_type);

    }
  }
}

