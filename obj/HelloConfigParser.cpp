/*
 * HelloConfigParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"
#include "obj/HelloConfigParser_def.hpp"
#include "obj/ObjectHeaderParser_def.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include "obj/LMPParseConfig.hpp"
#else
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;

      BOOST_SPIRIT_INSTANTIATE(
        hello_config_type, iterator_type, context_type);
#else
      typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
      template struct hello_config_grammar<BufIterType>;
#endif /* USE_SPIRIT_X3_PARSER */

    }
  }
}

