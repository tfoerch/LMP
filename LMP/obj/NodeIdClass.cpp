/*
 * NodeIdClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdClass.hpp"

namespace lmp
{
  namespace obj
  {
	namespace nodeid
	{
	  std::ostream& operator<<(
	    std::ostream&     os,
		const ClassType&  cType)
	  {
		switch(cType)
		{
		  case ClassType::LocalNodeId:
			os << "LocalNodeId";
			break;
		  case ClassType::RemoteNodeId:
			os << "RemoteNodeId";
			break;
		}
		return os;
	  }
	}
  } // namespace obj
} // namespace lmp

