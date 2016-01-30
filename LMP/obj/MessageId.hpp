#ifndef LMP_OBJ_MESSAGE_ID_HPP_
#define LMP_OBJ_MESSAGE_ID_HPP_
/*
 * MessageId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <MessageIdClass.hpp>
#include <ObjectClassTypeTraits.hpp>
#include <ObjectClassType.hpp>
#include <MessageIdTypeTraits.hpp>
#include <MessageIdIF.hpp>
#include <MessageIdData.hpp>

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<msgid::ClassType, msgid::MessageId>  MessageId;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_HPP_ */
