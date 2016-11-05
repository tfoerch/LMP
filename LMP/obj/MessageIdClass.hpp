#ifndef LMP_OBJ_MESSAGE_ID_CLASS_HPP_
#define LMP_OBJ_MESSAGE_ID_CLASS_HPP_
/*
 * MessageIdClass.hpp
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
	namespace msgid
	{
      enum class ClassType : lmp::BYTE
	  {
  	    MessageId = 1,
		MessageIdAck
	  };
      std::ostream& operator<<(
        std::ostream&     os,
  	    const ClassType&  cType);
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CLASS_HPP_ */
