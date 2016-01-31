#ifndef LMP_OBJ_MESSAGE_ID_ACK_HPP_
#define LMP_OBJ_MESSAGE_ID_ACK_HPP_
/*
 * MessageIdAck.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/MessageIdTypeTraits.hpp"
#include "obj/MessageIdIF.hpp"
#include "obj/MessageIdData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<msgid::ClassType, msgid::MessageIdAck>  MessageIdAck;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_ACK_HPP_ */
