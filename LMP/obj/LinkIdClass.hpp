#ifndef LMP_OBJ_LINK_ID_CLASS_HPP_
#define LMP_OBJ_LINK_ID_CLASS_HPP_
/*
 * LinkIdClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <LMPObjectIF.hpp>

namespace lmp
{
  namespace obj
  {
	namespace linkid
	{
      enum ClassType
	  {
  	    IPv4LocalLinkId = 1,
		IPv4RemoteLinkId,
		IPv6LocalLinkId,
		IPv6RemoteLinkId,
		UnnumberedLocalLinkId,
		UnnumberedRemoteLinkId
	  };
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LINK_ID_CLASS_HPP_ */
