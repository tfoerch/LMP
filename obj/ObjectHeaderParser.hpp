#ifndef LMP_OBJ_OBJECTHEADER_PARSER_HPP_
#define LMP_OBJ_OBJECTHEADER_PARSER_HPP_
/*
 * ObjectHeaderParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"

#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      struct object_header_fix_length_class;
      template <typename ClassType, ClassType ctype>
      using object_header_fix_length_type =
        x3::rule<object_header_fix_length_class, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype> > >;
      // BOOST_SPIRIT_DECLARE(object_header_fix_length_type);
      template <typename Iterator, typename Context, typename Attribute, typename ClassType, ClassType ctype>
      bool parse_rule(object_header_fix_length_type<ClassType, ctype> rule,
                      Iterator&       first,
                      Iterator const& last,
                      Context const&  context,
                      Attribute&      attr);

      struct object_header_var_length_class;
      template <typename ClassType, ClassType ctype>
      using object_header_var_length_type =
        x3::rule<object_header_var_length_class, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype> > >;
      // BOOST_SPIRIT_DECLARE(object_header_var_length_type);
      template <typename Iterator, typename Context, typename Attribute, typename ClassType, ClassType ctype>
      bool parse_rule(object_header_var_length_type<ClassType, ctype> rule,
                      Iterator&       first,
                      Iterator const& last,
                      Context const&  context,
                      Attribute&      attr);
    }
    template <typename ClassType, ClassType ctype>
    parser::object_header_fix_length_type<ClassType, ctype> const& object_header_fix_length();
    template <typename ClassType, ClassType ctype>
    parser::object_header_var_length_type<ClassType, ctype> const& object_header_var_length();
  } // namespace obj
} // namespace lmp


#endif /* LMP_OBJ_OBJECTHEADER_PARSER_HPP_ */
