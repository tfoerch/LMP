#ifndef LMP_OBJ_NODE_ID_IF_HPP_
#define LMP_OBJ_NODE_ID_IF_HPP_
/*
 * NodeIdIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>                  // for WORD
#include <NodeIdData.hpp>

namespace lmp
{
  namespace obj
  {
    class NodeIdIF
	{
	public:
      inline lmp::DWORD getNodeId() const { return do_getData().getNodeId(); }
      virtual ~NodeIdIF(){}
	private:
      virtual const NodeIdData& do_getData() const = 0;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_IF_HPP_ */
