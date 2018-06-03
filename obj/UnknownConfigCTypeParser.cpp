/*
 * UnknownConfigCTypeParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownConfigCTypeAst.hpp"
#include "obj/UnknownConfigCTypeParser_def.hpp"
#include "obj/LMPParseConfig.hpp"

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      BOOST_SPIRIT_INSTANTIATE(
        unknown_config_ctype_type, iterator_type, context_type);

    }
  }
}

