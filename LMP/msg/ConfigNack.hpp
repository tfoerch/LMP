#ifndef LMP_MSG_CONFIGNACK_HPP_
#define LMP_MSG_CONFIGNACK_HPP_
/*
 * ConfigNack.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/RemoteNodeId.hpp"
#include "obj/HelloConfig.hpp"
#include "CommonHeader.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    struct ConfigNackMsg
    {
      lmp::BYTE                           m_flags;
      lmp::obj::ccid::LocalCCIdData       m_localCCId;
      lmp::obj::nodeid::LocalNodeIdData   m_localNodeId;
      lmp::obj::ccid::RemoteCCIdData      m_remoteCCId;
      lmp::obj::msgid::MessageIdAckData   m_messageId;
      lmp::obj::nodeid::RemoteNodeIdData  m_remoteNodeId;
      lmp::obj::config::HelloConfigData   m_helloConfig;
    };
    std::ostream& operator<<(
      std::ostream&         os,
      const ConfigNackMsg&  configNack);
    bool operator==(
      const ConfigNackMsg&  first,
      const ConfigNackMsg&  second);
    lmp::DWORD getLength(
      const ConfigNackMsg&  configNack);
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct config_nack_grammar : qi::grammar<Iterator, ConfigNackMsg(CommonHeader)>
      {
    	config_nack_grammar();

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
        lmp::obj::parse::object_class_grammar<Iterator,
                                              lmp::obj::config::ClassType,
                                              lmp::obj::config::ClassType::HelloConfig>    hello_config;
    	qi::rule<Iterator, ConfigNackMsg(CommonHeader)>                                    config_nack_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGNACK_HPP_ */
