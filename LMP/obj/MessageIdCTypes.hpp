#ifndef LMP_OBJ_MESSAGE_ID_CTYPES_HPP_
#define LMP_OBJ_MESSAGE_ID_CTYPES_HPP_
/*
 * MessageIdCTypes.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/UnknownMessageIdCType.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
	namespace msgid
	{
	typedef
	  boost::variant<lmp::obj::msgid::MessageIdData,
	                 lmp::obj::msgid::MessageIdAckData,
					 lmp::obj::msgid::UnknownMessageIdCTypeData>   MessageIdCTypes;
      std::ostream& operator<<(
        std::ostream&                  os,
  	    const MessageIdCTypes&         messageIdCTypes);
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
        struct message_id_ctypes_grammar : qi::grammar<Iterator, MessageIdCTypes()>
        {
      	  message_id_ctypes_grammar();

      	  lmp::obj::parse::object_class_grammar<Iterator,
		                                        lmp::obj::msgid::ClassType,
												lmp::obj::msgid::ClassType::MessageId>      local_msgid;
      	  lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::msgid::ClassType,
												lmp::obj::msgid::ClassType::MessageIdAck>   remote_msgid;
          lmp::obj::msgid::parse::unknown_message_id_grammar<Iterator>  unknown_msgid_ctype;
      	  qi::rule<Iterator, MessageIdCTypes()>                         message_id_ctypes_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CTYPES_HPP_ */
