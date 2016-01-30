#ifndef LMP_OBJ_REMOTE_NODE_ID_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_HPP_
/*
 * RemoteNodeId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <NodeIdClass.hpp>
#include <ObjectClassTypeTraits.hpp>
#include <ObjectClassType.hpp>
#include <NodeIdTypeTraits.hpp>
#include <NodeIdIF.hpp>
#include <NodeIdData.hpp>

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<nodeid::ClassType, nodeid::RemoteNodeId>  RemoteNodeId;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_HPP_ */
