/*
 * MessageIdClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdClass.hpp"

namespace lmp
{
  namespace obj
  {
	namespace msgid
	{
	  std::ostream& operator<<(
	    std::ostream&     os,
		const ClassType&  cType)
	  {
		switch(cType)
		{
		  case ClassType::MessageId:
			os << "MessageId";
			break;
		  case ClassType::MessageIdAck:
			os << "MessageIdAck";
			break;
		}
		return os;
	  }
	}
  } // namespace obj
} // namespace lmp

