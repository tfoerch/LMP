#ifndef LMP_MSG_CONFIGACK_HPP_
#define LMP_MSG_CONFIGACK_HPP_
/*
 * ConfigAck.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/LMPMessageIF.hpp"
#include "obj/LocalCCId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/RemoteNodeId.hpp"
#include "CommonHeader.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    struct ConfigAckMsg
	{
      lmp::BYTE                           m_flags;
      lmp::obj::ccid::LocalCCIdData       m_localCCId;
      lmp::obj::nodeid::LocalNodeIdData   m_localNodeId;
      lmp::obj::ccid::RemoteCCIdData      m_remoteCCId;
      lmp::obj::msgid::MessageIdAckData   m_messageId;
      lmp::obj::nodeid::RemoteNodeIdData  m_remoteNodeId;
	};
    std::ostream& operator<<(
      std::ostream&             os,
	  const ConfigAckMsg& configAck);
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct config_ack_grammar : qi::grammar<Iterator, ConfigAckMsg(CommonHeaderOutput)>
      {
    	config_ack_grammar();

        lmp::obj::parse::object_class_grammar<Iterator,
		                                      lmp::obj::ccid::ClassType,
											  lmp::obj::ccid::ClassType::LocalCCId>    local_ccid;
        lmp::obj::parse::object_class_grammar<Iterator,
		                                      lmp::obj::ccid::ClassType,
											  lmp::obj::ccid::ClassType::RemoteCCId>    remote_ccid;
        lmp::obj::parse::object_class_grammar<Iterator,
		                                      lmp::obj::nodeid::ClassType,
											  lmp::obj::nodeid::ClassType::LocalNodeId>    local_node_id;
        lmp::obj::parse::object_class_grammar<Iterator,
           		                              lmp::obj::nodeid::ClassType,
											  lmp::obj::nodeid::ClassType::RemoteNodeId>   remote_node_id;
        lmp::obj::parse::object_class_grammar<Iterator,
                                              lmp::obj::msgid::ClassType,
											  lmp::obj::msgid::ClassType::MessageIdAck>    message_id_ack;
    	qi::rule<Iterator, ConfigAckMsg(CommonHeaderOutput)>             config_ack_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGACK_HPP_ */
