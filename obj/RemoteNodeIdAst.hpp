#ifndef LMP_OBJ_REMOTE_NODE_ID_AST_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_AST_HPP_
/*
 * RemoteNodeIdAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/NodeIdClassAst.hpp"
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>


namespace lmp
{
  namespace obj
  {
    template <>
    struct HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::RemoteNodeId>
    {
      typedef typename nodeid::ClassType                ctype_type;
      static const ObjectClass                          obj_class;
      static const ctype_type                           ctype;
      static const lmp::WORD                            length;
    };
    namespace nodeid
    {
      namespace ast
      {
        namespace x3 = boost::spirit::x3;
        struct RemoteNodeId : x3::position_tagged
        {
          typedef
            lmp::obj::ast::ObjectHeader<HeaderCTypeTraits<nodeid::ClassType,
                                                          nodeid::ClassType::RemoteNodeId>>  RemoteNodeIdHeaderType;

          RemoteNodeIdHeaderType  m_header;
          lmp::DWORD              m_nodeId;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_AST_HPP_ */
