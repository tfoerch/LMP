#ifndef LMP_OBJ_HELLO_CONFIG_PARSER_HPP_
#define LMP_OBJ_HELLO_CONFIG_PARSER_HPP_
/*
 * HelloConfigParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"

#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
//#include <boost/spirit/home/x3.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      struct hello_config_class;
      typedef
        x3::rule<hello_config_class, config::ast::HelloConfig>  hello_config_type;
      BOOST_SPIRIT_DECLARE(hello_config_type);
    }
    parser::hello_config_type const& hello_config();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CONFIG_PARSER_HPP_ */
