#ifndef LMP_MSG_CONFIG_HPP_
#define LMP_MSG_CONFIG_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/LMPMessageIF.hpp"
#include "obj/LocalCCId.hpp"
#include "obj/MessageId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/HelloConfig.hpp"
#include "CommonHeader.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    class CommonHeader;
    class Config : public LMPMessageIF
	{
	public:
      typedef boost::optional<Config>      OptMsg;
      enum decoding_error
	  {
		invalid_length,
		unspecified_decoding_error
	  };
      typedef boost::optional<decoding_error>    OptDecError;
      typedef std::pair<OptMsg, OptDecError>  DecodingResult;
      Config(
        const lmp::obj::LocalCCId&    localCCId,
		const lmp::obj::MessageId&    messageId,
		const lmp::obj::LocalNodeId&  localNodeId,
		const lmp::obj::HelloConfig&  helloConfig);
      inline const lmp::obj::LocalCCId& getLocalCCId() const { return m_localCCId; }
      inline const lmp::obj::MessageId& getMessageId() const { return m_messageId; }
      inline const lmp::obj::LocalNodeId& getLocalNodeId() const { return m_localNodeId; }
      inline const lmp::obj::HelloConfig& getHelloConfig() const { return m_helloConfig; }
      static DecodingResult decode(
        const CommonHeader&         msgHeader,
    	boost::asio::const_buffer&  buffer);
    private:
      virtual const mtype::MsgType do_getMsgType() const;
      virtual lmp::WORD do_getContentsLength() const;
      virtual CommonHeader::OptEncError do_encodeContents(
    	boost::asio::mutable_buffer&  buffer) const;
	  lmp::obj::LocalCCId    m_localCCId;
	  lmp::obj::MessageId    m_messageId;
	  lmp::obj::LocalNodeId  m_localNodeId;
	  lmp::obj::HelloConfig  m_helloConfig;
	};
    namespace parse
    {
      struct ConfigMsgData
	  {
	    lmp::BYTE                          m_flags;
		lmp::obj::ccid::LocalCCIdData      m_localCCId;
		lmp::obj::msgid::MessageIdData     m_messageId;
		lmp::obj::nodeid::LocalNodeIdData  m_localNodeId;
		lmp::obj::config::HelloConfigData  m_helloConfig;
	  };
      std::ostream& operator<<(
        std::ostream&         os,
	    const ConfigMsgData&  config);
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct config_grammar : qi::grammar<Iterator, ConfigMsgData(CommonHeaderOutput)>
      {
    	config_grammar();

        lmp::obj::parse::object_class_grammar<Iterator,
		                                      lmp::obj::ccid::ClassType,
											  lmp::obj::ccid::ClassType::LocalCCId>    local_ccid;
        lmp::obj::nodeid::parse::local_node_id_grammar<Iterator>             local_node_id;
        lmp::obj::msgid::parse::message_id_grammar<Iterator>                 message_id;
        lmp::obj::parse::object_class_grammar<Iterator,
		                                      lmp::obj::config::ClassType,
											  lmp::obj::config::ClassType::HelloConfig>     hello_config;
    	qi::rule<Iterator, ConfigMsgData(CommonHeaderOutput)>                config_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_HPP_ */
