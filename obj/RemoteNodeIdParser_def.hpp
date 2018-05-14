#ifndef LMP_OBJ_REMOTE_NODE_ID_PARSER_DEF_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_PARSER_DEF_HPP_
/*
 * RemoteNodeIdParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeIdAstAdapted.hpp"
#include "obj/RemoteNodeIdParser.hpp"
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

      remote_node_id_type const remote_node_id = "remote_node_id";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
//      lmp::WORD var_obj_length;

      auto header = [&](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
      auto ccId = [](auto &ctx) { at_c<1>(_val(ctx)) = _attr(ctx); };
      auto checkLength = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::RemoteNodeId>::length; };

//      auto const remote_node_id_def =
//        with<ObjLength>(std::ref(var_obj_length))
//        [
//          object_header_var_length<nodeid::ClassType, nodeid::ClassType::RemoteNodeId> [header]
//          >> eps [checkLength]
//          >> big_dword [ccId]
//        ];

      auto const remote_node_id_def =
        object_header_fix_length<nodeid::ClassType, nodeid::ClassType::RemoteNodeId> // [header]
        >> big_dword //[ccId]
        ;

      BOOST_SPIRIT_DEFINE(remote_node_id);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct remote_node_id_class : x3::annotate_on_success/*, error_handler_base*/ {};
    } // namespace parser

    parser::remote_node_id_type const& remote_node_id()
    {
      return parser::remote_node_id;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_PARSER_DEF_HPP_ */
