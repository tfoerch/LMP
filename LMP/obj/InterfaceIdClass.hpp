#ifndef LMP_OBJ_INTERFACE_ID_CLASS_HPP_
#define LMP_OBJ_INTERFACE_ID_CLASS_HPP_
/*
 * InterfaceIdClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <LMPObjectIF.hpp>

namespace lmp
{
  namespace obj
  {
	namespace ifid
	{
      enum ClassType
	  {
  	    IPv4LocalInterfaceId = 1,
		IPv4RemoteInterfaceId,
		IPv6LocalInterfaceId,
		IPv6RemoteInterfaceId,
		UnnumberedLocalInterfaceId,
		UnnumberedRemoteInterfaceId
	  };
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_INTERFACE_ID_CLASS_HPP_ */
