#ifndef LMP_OBJ_HELLO_PARSER_HPP_
#define LMP_OBJ_HELLO_PARSER_HPP_
/*
 * HelloParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloAst.hpp"

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

      struct hello_class;
      typedef
        x3::rule<hello_class, hello::ast::Hello>  hello_type;
      BOOST_SPIRIT_DECLARE(hello_type);
    }
    parser::hello_type const& hello_parser();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_PARSER_HPP_ */
