/*
 * HelloConfigParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"
#include "obj/HelloConfigParser_def.hpp"
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
        hello_config_type, iterator_type, context_type);

    }
  }
}

