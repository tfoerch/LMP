#ifndef LMP_MSG_CONFIGNACK_HPP_
#define LMP_MSG_CONFIGNACK_HPP_
/*
 * ConfigNack.hpp
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
#include "obj/HelloConfig.hpp"
#include "CommonHeader.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    class ConfigNack : public LMPMessageIF
	{
	public:
      ConfigNack(
    	const lmp::obj::LocalCCId&     localCCId,
		const lmp::obj::LocalNodeId&   localNodeId,
    	const lmp::obj::RemoteCCId&    remoteCCId,
		const lmp::obj::MessageIdAck&  messageIdAck,
		const lmp::obj::RemoteNodeId&  remoteNodeId,
		const lmp::obj::HelloConfig&   helloConfig);
      inline const lmp::obj::LocalCCId& getLocalCCId() const { return m_localCCId; }
      inline const lmp::obj::LocalNodeId& getLocalNodeId() const { return m_localNodeId; }
      inline const lmp::obj::RemoteCCId& getRemoteCCId() const { return m_remoteCCId; }
      inline const lmp::obj::MessageIdAck& getMessageIdAck() const { return m_messageIdAck; }
      inline const lmp::obj::RemoteNodeId& getRemoteNodeId() const { return m_remoteNodeId; }
      inline const lmp::obj::HelloConfig& getHelloConfig() const { return m_helloConfig; }
    private:
      virtual const mtype::MsgType do_getMsgType() const;
      virtual lmp::WORD do_getContentsLength() const;
      virtual CommonHeader::OptEncError do_encodeContents(
    	boost::asio::mutable_buffer&  buffer) const;
	  lmp::obj::LocalCCId     m_localCCId;
	  lmp::obj::LocalNodeId   m_localNodeId;
	  lmp::obj::RemoteCCId    m_remoteCCId;
	  lmp::obj::MessageIdAck  m_messageIdAck;
	  lmp::obj::RemoteNodeId  m_remoteNodeId;
	  lmp::obj::HelloConfig   m_helloConfig;
	};
    namespace parse
    {
	  struct ConfigNackMsgData
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
	    std::ostream&          os,
	    const ConfigNackMsgData& configNack);
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct config_nack_grammar : qi::grammar<Iterator, ConfigNackMsgData(CommonHeaderOutput)>
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
											  lmp::obj::config::ClassType::HelloConfig>     hello_config;
    	qi::rule<Iterator, ConfigNackMsgData(CommonHeaderOutput)>            config_nack_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGNACK_HPP_ */
