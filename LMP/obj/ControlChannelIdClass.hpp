#ifndef LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_HPP_
#define LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_HPP_
/*
 * ControlChannelIdClass.hpp
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
	namespace ccid
	{
      enum class ClassType : lmp::BYTE
	  {
  	    LocalCCId = 1,
		RemoteCCId
	  };
      std::ostream& operator<<(
        std::ostream&     os,
  	    const ClassType&  cType);
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_HPP_ */
