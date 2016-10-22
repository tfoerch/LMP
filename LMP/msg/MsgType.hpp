#ifndef LMP_MSG_MSGTYPE_HPP_
#define LMP_MSG_MSGTYPE_HPP_
/*
 * MsgType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"

namespace lmp
{
  namespace msg
  {
    enum class MsgType : lmp::BYTE
	{
      Config = 1,
      ConfigAck,
	  ConfigNack,
	  Hello
    };
    namespace mtype
    {
      enum MsgType
	  {
    	Config = 1,
		ConfigAck,
		ConfigNack,
		Hello
	  };
    } // namespace mtype
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_HPP_ */
