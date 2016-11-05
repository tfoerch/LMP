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
      static boost::optional<msgid::ClassType> classType_cast(
        lmp::BYTE                     classTypeByte)
	  {
    	boost::optional<msgid::ClassType>  result;
        const msgid::ClassType cType = static_cast<msgid::ClassType>(classTypeByte);
        switch(cType)
        {
          case msgid::ClassType::MessageId:
          case msgid::ClassType::MessageIdAck:
        	result = cType;
        	break;
          default:
        	break;
        }
        return result;
	  }
    };
    template <>
    struct ObjectClassCTypeTraits<msgid::ClassType, msgid::ClassType::MessageId>
    {
      typedef MessageIdIF    object_ctype_if_type;
      typedef MessageIdData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
    template <>
    struct ObjectClassCTypeTraits<msgid::ClassType, msgid::ClassType::MessageIdAck>
    {
      typedef MessageIdIF    object_ctype_if_type;
      typedef MessageIdData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_TYPE_TRAITS_HPP_ */
