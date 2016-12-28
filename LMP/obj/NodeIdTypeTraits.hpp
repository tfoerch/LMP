#ifndef LMP_OBJ_NODE_ID_TYPE_TRAITS_HPP_
#define LMP_OBJ_NODE_ID_TYPE_TRAITS_HPP_
/*
 * NodeIdTypeTraits.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "obj/NodeIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"

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
      static boost::optional<nodeid::ClassType> classType_cast(
        lmp::BYTE                     classTypeByte)
	  {
    	boost::optional<nodeid::ClassType>  result;
        const nodeid::ClassType cType = static_cast<nodeid::ClassType>(classTypeByte);
        switch(cType)
        {
          case nodeid::ClassType::LocalNodeId:
          case nodeid::ClassType::RemoteNodeId:
        	result = cType;
        	break;
          default:
        	break;
        }
        return result;
	  }
    };
    template <>
    struct ObjectClassTypeConst<nodeid::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::NodeID;
    };
    template <>
    struct ObjectClassCTypeTraits<nodeid::ClassType, nodeid::ClassType::LocalNodeId>
    {
      typedef NodeIdIF    object_ctype_if_type;
      typedef NodeIdData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
    template <>
    struct ObjectClassCTypeTraits<nodeid::ClassType, nodeid::ClassType::RemoteNodeId>
    {
      typedef NodeIdIF    object_ctype_if_type;
      typedef NodeIdData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_TYPE_TRAITS_HPP_ */
