#ifndef LMP_OBJ_MESSAGE_ID_TYPE_TRAITS_HPP_
#define LMP_OBJ_MESSAGE_ID_TYPE_TRAITS_HPP_
/*
 * MessageIdTraits.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "obj/MessageIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"

namespace lmp
{
  namespace obj
  {
    class MessageIdData;
    class MessageIdIF;
    template <>
    struct ObjectClassBaseTraits<msgid::ClassType>
    {
      static const otype::ObjectClass  c_object_class = otype::MessageID;
    };
    template <>
    struct ObjectClassCTypeTraits<msgid::ClassType, msgid::MessageId>
    {
      typedef MessageIdIF    object_ctype_if_type;
      typedef MessageIdData  data_type;
    };
    template <>
    struct ObjectClassCTypeTraits<msgid::ClassType, msgid::MessageIdAck>
    {
      typedef MessageIdIF    object_ctype_if_type;
      typedef MessageIdData  data_type;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_TYPE_TRAITS_HPP_ */
