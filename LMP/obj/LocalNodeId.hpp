#ifndef LMP_OBJ_LOCAL_NODE_ID_HPP_
#define LMP_OBJ_LOCAL_NODE_ID_HPP_
/*
 * LocalNodeId.hpp
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
    typedef ObjectClassType<nodeid::ClassType, nodeid::LocalNodeId>  LocalNodeId;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_NODE_ID_HPP_ */
