#ifndef LMP_OBJ_MESSAGE_ID_PARSER_DEF_HPP_
#define LMP_OBJ_MESSAGE_ID_PARSER_DEF_HPP_
/*
 * MessageIdParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAstAdapted.hpp"
#include "obj/MessageIdParser.hpp"
#include "obj/ObjectHeaderParser_def.hpp"
#include "obj/ObjectClassAst.hpp"
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
      using x3::big_dword;
      using x3::get;
      using x3::with;
      using fusion::at_c;

      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////

      message_id_type const message_id = "message_id";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
//      lmp::WORD var_obj_length;

      auto header = [&](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
      auto ccId = [](auto &ctx) { at_c<1>(_val(ctx)) = _attr(ctx); };
      auto checkLength = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == HeaderCTypeTraits<msgid::ClassType, msgid::ClassType::MessageId>::length; };

//      auto const message_id_def =
//        with<ObjLength>(std::ref(var_obj_length))
//        [
//          object_header_var_length<msgid::ClassType, msgid::ClassType::MessageId> [header]
//          >> eps [checkLength]
//          >> big_dword [ccId]
//        ];

      auto const message_id_def =
        object_header_fix_length<msgid::ClassType, msgid::ClassType::MessageId> // [header]
        >> big_dword //[ccId]
        ;

      BOOST_SPIRIT_DEFINE(message_id);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct message_id_class : x3::annotate_on_success/*, error_handler_base*/ {};
    } // namespace parser

    parser::message_id_type const& message_id()
    {
      return parser::message_id;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_PARSER_DEF_HPP_ */
