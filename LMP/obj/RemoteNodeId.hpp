#ifndef LMP_OBJ_REMOTE_NODE_ID_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_HPP_
/*
 * RemoteNodeId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/NodeIdTypeTraits.hpp"
#include "obj/NodeIdIF.hpp"
#include "obj/NodeIdData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<nodeid::ClassType, nodeid::RemoteNodeId>  RemoteNodeId;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_HPP_ */
