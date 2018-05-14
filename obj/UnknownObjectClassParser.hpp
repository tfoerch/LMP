#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_PARSER_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_PARSER_HPP_
/*
 * UnknownObjectClassParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownObjectClassAst.hpp"

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

      struct unknown_object_class_class;
      typedef
        x3::rule<unknown_object_class_class, ast::UnknownObjectClass>  unknown_object_class_type;
      BOOST_SPIRIT_DECLARE(unknown_object_class_type);
    }
    parser::unknown_object_class_type const& unknown_object_class();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS_PARSER_HPP_ */
