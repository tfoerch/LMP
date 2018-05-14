#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_DEF_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_DEF_HPP_
/*
 * ObjectClassUnknownCTypeParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAstAdapted.hpp"
#include "obj/ObjectClassUnknownCTypeParser.hpp"
#include "obj/ObjectHeaderUnknownCTypeParser_def.hpp"
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/binary/binary.hpp>
#include <boost/spirit/home/x3.hpp>

#include <type_traits>


namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;
      namespace fusion = boost::fusion;
      using x3::byte_;
      using x3::big_word;
      using x3::get;
      using x3::with;
      using x3::eps;
      using fusion::at_c;

      ///////////////////////////////////////////////////////////////////////////
      // Rule IDs
      ///////////////////////////////////////////////////////////////////////////

      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////


      template <ObjectClass objClass>
      object_class_unknown_ctype_type<objClass> const
        object_class_unknown_ctype = "object_class_unknown_ctype";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
      lmp::WORD uCTypeLength;

      auto header = [&](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
      auto push_back = [](auto &ctx) { at_c<1>(_val(ctx)).push_back(_attr(ctx)); };
      auto more   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) >  at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };
      auto done   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };

      template <ObjectClass objClass>
      auto const object_class_unknown_ctype_def =
        with<ObjLength>(std::ref(uCTypeLength))
        [
          object_header_unknown_ctype<objClass> [header]  // class type
          >> *( eps [more] >> byte_[push_back] ) >> eps [done] // data
        ];

      template <typename Iterator, typename Context, typename Attribute, ObjectClass objClass>
      inline bool parse_rule( object_class_unknown_ctype_type<objClass> rule, Iterator& first, Iterator const& last , Context const& context, Attribute& attr)
      {
        using boost::spirit::x3::unused;
        static auto const def_ = (object_class_unknown_ctype<objClass> = object_class_unknown_ctype_def<objClass>);
        return def_.parse(first, last, context, unused, attr);
      }
      // BOOST_SPIRIT_DEFINE(object_class_unknown_ctype_inner, object_class_unknown_ctype);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

     // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct object_class_unknown_ctype_class : x3::annotate_on_success/*, error_handler_base*/ {};
    } // namespace parser
    template <ObjectClass objClass>
    parser::object_class_unknown_ctype_type<objClass> const& object_class_unknown_ctype()
    {
      return parser::object_class_unknown_ctype<objClass>;
    }
#if 0
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator, ObjectClass objClass>
      object_class_unknown_ctype_grammar<Iterator, objClass>::object_class_unknown_ctype_grammar()
      : object_class_unknown_ctype_grammar::base_type(object_class_unknown_ctype_rule, "object_class_unknown_ctype")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_1;
        using phoenix::at_c;
        using namespace qi::labels;

        object_class_unknown_ctype_rule =
            byte_ [at_c<0>(_val) = (_1 & lmp::obj::c_classTypeMask), at_c<1>(_val) = (_1 & lmp::obj::c_negotiableMask) ]  // class type
            >> byte_(static_cast<typename std::underlying_type<ObjectClass>::type>(objClass))    // object class
            >> big_word [_a = _1] // length
            >> byte_sequence(_a - lmp::obj::c_objHeaderLength) [ at_c<2>(_val) = _1 ]
            ;

        object_class_unknown_ctype_rule.name("object_class_unknown_ctype");

      }
#endif
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_DEF_HPP_ */
