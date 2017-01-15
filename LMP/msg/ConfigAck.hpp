#ifndef LMP_MSG_CONFIGACK_HPP_
#define LMP_MSG_CONFIGACK_HPP_
/*
 * ConfigAck.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/RemoteNodeId.hpp"
#include "CommonHeader.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

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
      std::ostream&        os,
      const ConfigAckMsg&  configAck);
    bool operator==(
      const ConfigAckMsg&  first,
      const ConfigAckMsg&  second);
    lmp::DWORD getLength(
      const ConfigAckMsg&  configAck);
    struct GetConfigAckLength
    {
      template<typename> struct result { typedef lmp::DWORD type; };
      template<typename ConfigAckMsg>
      lmp::DWORD operator()(
        const ConfigAckMsg& configAck) const
      { return lmp::msg::getLength(configAck); }
    };
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct config_ack_grammar : qi::grammar<Iterator, ConfigAckMsg(CommonHeader)>
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
    	qi::rule<Iterator, ConfigAckMsg(CommonHeader)>                                     config_ack_rule;
      };
    }
    namespace generate
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct config_ack_grammar : karma::grammar<OutputIterator, ConfigAckMsg()>
      {
        config_ack_grammar();

        boost::phoenix::function<lmp::msg::GetConfigAckLength>                               phx_getLength;
        lmp::obj::generate::object_class_grammar<OutputIterator,
                                                 lmp::obj::ccid::ClassType,
                                                 lmp::obj::ccid::ClassType::LocalCCId>       local_ccid;
        lmp::obj::generate::object_class_grammar<OutputIterator,
                                                 lmp::obj::ccid::ClassType,
                                                 lmp::obj::ccid::ClassType::RemoteCCId>      remote_ccid;
        lmp::obj::generate::object_class_grammar<OutputIterator,
                                                 lmp::obj::nodeid::ClassType,
                                                 lmp::obj::nodeid::ClassType::LocalNodeId>   local_node_id;
        lmp::obj::generate::object_class_grammar<OutputIterator,
                                                 lmp::obj::nodeid::ClassType,
                                                 lmp::obj::nodeid::ClassType::RemoteNodeId>  remote_node_id;
        lmp::obj::generate::object_class_grammar<OutputIterator,
                                                 lmp::obj::msgid::ClassType,
                                                 lmp::obj::msgid::ClassType::MessageIdAck>   message_id_ack;
        karma::rule<OutputIterator, ConfigAckMsg&()>                                         common_header;
        karma::rule<OutputIterator, ConfigAckMsg()>                                          config_ack_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGACK_HPP_ */
