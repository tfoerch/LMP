#ifndef LMP_OBJ_OBJECTHEADER_PARSER_DEF_HPP_
#define LMP_OBJ_OBJECTHEADER_PARSER_DEF_HPP_
/*
 * ObjectHeaderParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAstAdapted.hpp"
#include "obj/ObjectHeaderParser.hpp"
//#include "obj/ObjectClass.hpp"
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
      using x3::omit;
      using x3::eps;
      using x3::expectation_failure;
      using fusion::at_c;

      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////

      template <typename ClassType, ClassType ctype>
      object_header_fix_length_type<ClassType, ctype> const
        object_header_fix_length = "object_header_fix_length";

      template <typename ClassType, ClassType ctype>
      object_header_var_length_type<ClassType, ctype> const
        object_header_var_length = "object_header_var_length";

      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
      struct ObjLength{};

      //auto classTypeAndNeg = [](auto &ctx) { at_c<0>(_val(ctx)) = ( _attr(ctx) & lmp::obj::c_classTypeMask); at_c<1>(_val(ctx)) = ( _attr(ctx) & lmp::obj::c_negotiableMask); };
      auto setNeg = [](auto &ctx) { at_c<0>(_val(ctx)) = true; };
      auto setNeg2 = [](auto &ctx) { at_c<1>(_val(ctx)) = true; };
      auto setNotNeg = [](auto &ctx) { at_c<0>(_val(ctx)) = false; };
      auto push_back = [](auto &ctx) { at_c<1>(_val(ctx)).push_back(_attr(ctx)); };
      auto number = [](auto &ctx) { get<ObjLength>(ctx).get() = _attr(ctx); };
      auto length = [](auto &ctx) { get<ObjLength>(ctx).get() = _attr(ctx); };
      auto setData = [](auto &ctx) { at_c<1>(_val(ctx)) = _attr(ctx); };
      auto more   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) >  at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };
      auto done   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };

      template <typename ClassType, ClassType ctype>
      auto const object_header_fix_length_def =
          ( byte_(static_cast<typename std::underlying_type<ClassType>::type>(ctype)) [setNotNeg] |
            byte_(static_cast<typename std::underlying_type<ClassType>::type>(ctype) + lmp::obj::c_negotiableMask) [setNeg] ) // class type
          >> byte_(static_cast<typename std::underlying_type<ObjectClass>::type>(HeaderObjClassTypeTraits<ClassType>::obj_class)) // object class
          > big_word(HeaderCTypeTraits<ClassType, ctype>::length)     // length
          ;

      template <typename ClassType, ClassType ctype>
      auto const object_header_var_length_def =
          ( byte_(static_cast<typename std::underlying_type<ClassType>::type>(ctype)) [setNotNeg] |
            byte_(static_cast<typename std::underlying_type<ClassType>::type>(ctype) + lmp::obj::c_negotiableMask) [setNeg] ) // class type
          >> byte_(static_cast<typename std::underlying_type<ObjectClass>::type>(HeaderObjClassTypeTraits<ClassType>::obj_class)) // object class
          >> big_word [length]
          ;

      template <typename Iterator, typename Context, typename Attribute, typename ClassType, ClassType ctype>
      inline bool parse_rule( object_header_fix_length_type<ClassType, ctype> rule, Iterator& first, Iterator const& last , Context const& context, Attribute& attr)
      {
        using boost::spirit::x3::unused;
        static auto const def_ = (object_header_fix_length<ClassType, ctype> = object_header_fix_length_def<ClassType, ctype>);
        return def_.parse(first, last, context, unused, attr);
      }

      template <typename Iterator, typename Context, typename Attribute, typename ClassType, ClassType ctype>
      inline bool parse_rule( object_header_var_length_type<ClassType, ctype> rule, Iterator& first, Iterator const& last , Context const& context, Attribute& attr)
      {
        using boost::spirit::x3::unused;
        static auto const def_ = (object_header_var_length<ClassType, ctype> = object_header_var_length_def<ClassType, ctype>);
        return def_.parse(first, last, context, unused, attr);
      }
      // BOOST_SPIRIT_DEFINE(object_header_inner, object_header_fix_length);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct object_header_fix_length_class : x3::annotate_on_success/*, error_handler_base*/ {};
      struct object_header_var_length_class : x3::annotate_on_success/*, error_handler_base*/ {};
    } // namespace parser

    template <typename ClassType, ClassType ctype>
    parser::object_header_fix_length_type<ClassType, ctype> const& object_header_fix_length()
    {
      return parser::object_header_fix_length<ClassType, ctype>;
    }

    template <typename ClassType, ClassType ctype>
    parser::object_header_var_length_type<ClassType, ctype> const& object_header_var_length()
    {
      return parser::object_header_var_length<ClassType, ctype>;
    }

  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_PARSER_DEF_HPP_ */
