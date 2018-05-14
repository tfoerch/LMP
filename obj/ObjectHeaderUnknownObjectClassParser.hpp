#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_HPP_
/*
 * ObjectHeaderUnknownObjectClassParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownObjectClassAst.hpp"

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

      struct object_header_unknown_object_class_class;
      typedef
        x3::rule<object_header_unknown_object_class_class, ast::ObjectHeaderUnknownObjectClass>  object_header_unknown_object_class_type;
      BOOST_SPIRIT_DECLARE(object_header_unknown_object_class_type);
    }
    parser::object_header_unknown_object_class_type const& object_header_unknown_object_class();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_HPP_ */
