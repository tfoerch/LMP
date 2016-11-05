#ifndef LMP_OBJ_NODE_ID_CLASS_HPP_
#define LMP_OBJ_NODE_ID_CLASS_HPP_
/*
 * NodeIdClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"

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
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CLASS_HPP_ */
