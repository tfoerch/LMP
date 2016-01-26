#ifndef LMP_OBJ_NODE_ID_TYPE_TRAITS_HPP_
#define LMP_OBJ_NODE_ID_TYPE_TRAITS_HPP_
/*
 * NodeIdTraits.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include <NodeIdClass.hpp>
#include <ObjectClassTypeTraits.hpp>

namespace lmp
{
  namespace obj
  {
    class NodeIdData;
    class NodeIdIF;
    template <>
    struct ObjectClassBaseTraits<nodeid::ClassType>
    {
      static const otype::ObjectClass  c_object_class = otype::NodeID;
    };
    template <>
    struct ObjectClassCTypeTraits<nodeid::ClassType, nodeid::LocalNodeId>
    {
      typedef NodeIdIF    object_ctype_if_type;
      typedef NodeIdData  data_type;
    };
    template <>
    struct ObjectClassCTypeTraits<nodeid::ClassType, nodeid::RemoteNodeId>
    {
      typedef NodeIdIF    object_ctype_if_type;
      typedef NodeIdData  data_type;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_TYPE_TRAITS_HPP_ */
