#ifndef LMP_OBJ_MESSAGE_ID_ACK_HPP_
#define LMP_OBJ_MESSAGE_ID_ACK_HPP_
/*
 * MessageIdAck.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdClass.hpp"

namespace lmp
{
  namespace obj
  {
    template <>
    struct ObjectClassTypeTraits<msgid::ClassType, msgid::ClassType::MessageIdAck>
    {
      typedef typename msgid::ClassType      ctype_type;
      typedef typename msgid::MessageIdBody  data_type;
      typedef typename msgid::IsEqualFtor    equal_ftor_type;
      typedef typename msgid::GetLengthFtor  get_length_ftor_type;
      static const ctype_type                ctype = msgid::ClassType::MessageIdAck;
    };
    template <typename Iterator>
    struct ObjectClassTypeParseTraits<Iterator, msgid::ClassType, msgid::ClassType::MessageIdAck>
    {
      typedef msgid::parse::message_id_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct ObjectClassTypeGenerateTraits<OutputIterator, msgid::ClassType, msgid::ClassType::MessageIdAck>
    {
      typedef msgid::generate::message_id_body_grammar<OutputIterator>  grammar_type;
    };
    namespace msgid
    {
      typedef ObjectClassTypeData<ObjectClassTypeTraits<msgid::ClassType,
                                                        msgid::ClassType::MessageIdAck>>  MessageIdAckData;
      const lmp::WORD messageIdAckLength = c_objHeaderLength + 4;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_ACK_HPP_ */
