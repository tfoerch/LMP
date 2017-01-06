#ifndef LMP_OBJ_REMOTE_NODE_ID_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_HPP_
/*
 * RemoteNodeId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/NodeIdClass.hpp"

namespace lmp
{
  namespace obj
  {
    template <>
    struct ObjectClassTypeTraits<nodeid::ClassType, nodeid::ClassType::RemoteNodeId>
    {
      typedef typename nodeid::ClassType      ctype_type;
      typedef typename nodeid::NodeIdBody     data_type;
      typedef typename nodeid::IsEqualFtor    equal_ftor_type;
      typedef typename nodeid::GetLengthFtor  get_length_ftor_type;
      static const ctype_type                 ctype = nodeid::ClassType::RemoteNodeId;
    };
    template <typename Iterator>
    struct ObjectClassTypeParseTraits<Iterator, nodeid::ClassType, nodeid::ClassType::RemoteNodeId>
    {
      typedef nodeid::parse::node_id_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct ObjectClassTypeGenerateTraits<OutputIterator, nodeid::ClassType, nodeid::ClassType::RemoteNodeId>
    {
      typedef nodeid::generate::node_id_body_grammar<OutputIterator>  grammar_type;
    };
    namespace nodeid
    {
      typedef ObjectClassTypeData<ObjectClassTypeTraits<nodeid::ClassType,
                                                        nodeid::ClassType::RemoteNodeId>>  RemoteNodeIdData;
      const lmp::WORD remoteNodeIdLength = c_objHeaderLength + 4;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_HPP_ */
