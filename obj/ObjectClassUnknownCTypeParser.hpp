#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_HPP_
/*
 * ObjectClassUnknownCTypeParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"

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

      struct object_class_unknown_ctype_class;
      template <ObjectClass objClass>
      using object_class_unknown_ctype_type =
        x3::rule<object_class_unknown_ctype_class, ast::ObjectClassUnknownCType<ObjectClassTraits<objClass>>>;
      // BOOST_SPIRIT_DECLARE(object_class_unknown_ctype_type);
      template <typename Iterator, typename Context, typename Attribute, ObjectClass objClass>
      bool parse_rule(object_class_unknown_ctype_type<objClass> rule,
                      Iterator&       first,
                      Iterator const& last,
                      Context const& context,
                      Attribute& attr);
    }
    template <ObjectClass objClass>
    parser::object_class_unknown_ctype_type<objClass> const& object_class_unknown_ctype();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_HPP_ */
