#ifndef LMP_OBJ_MESSAGE_ID_HPP_
#define LMP_OBJ_MESSAGE_ID_HPP_
/*
 * MessageId.hpp
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
    typedef ObjectClassType<msgid::ClassType, msgid::ClassType::MessageId>  MessageId;
	namespace msgid
	{
	  struct MessageIdData
	  {
	    bool        m_negotiable;
	    lmp::DWORD  m_messageId;
	  };
	  std::ostream& operator<<(
	    std::ostream&         os,
		const MessageIdData&  messageId);
	  const lmp::WORD messageIdLength = objHeaderLength + 4;
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct message_id_grammar : qi::grammar<Iterator, MessageIdData()>
        {
      	  message_id_grammar();

      	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
      	  qi::rule<Iterator, MessageIdData()>                           message_id_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_HPP_ */
