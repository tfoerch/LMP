#ifndef LMP_OBJ_NODE_ID_CLASS_HPP_
#define LMP_OBJ_NODE_ID_CLASS_HPP_
/*
 * NodeIdClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>

namespace lmp
{
  namespace obj
  {
    namespace nodeid
    {
      enum class ClassType : lmp::BYTE
      {
        LocalNodeId = 1,
        RemoteNodeId
      };
      std::ostream& operator<<(
        std::ostream&     os,
        const ClassType&  cType);
      struct NodeIdBody
      {
        lmp::DWORD  m_nodeId;
      };
      std::ostream& operator<<(
        std::ostream&      os,
        const NodeIdBody&  nodeIdBody);
      struct IsEqualFtor
      {
        bool operator()(
          const NodeIdBody& first,
          const NodeIdBody& second) const;
      };
      struct GetLengthFtor
      {
        lmp::WORD operator()(
          const NodeIdBody&  nodeIdBody) const;
        static const lmp::WORD c_length;
      };
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct node_id_body_grammar : qi::grammar<Iterator, NodeIdBody(lmp::WORD)>
        {
          node_id_body_grammar();

          qi::rule<Iterator, NodeIdBody(lmp::WORD)>  node_id_body_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct node_id_body_grammar : karma::grammar<OutputIterator, NodeIdBody()>
        {
          node_id_body_grammar();

          karma::rule<OutputIterator, NodeIdBody()>                  node_id_body_rule;
        };
      }
    }
    template <>
    struct ObjectClassTypeConst<nodeid::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::NodeID;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CLASS_HPP_ */
