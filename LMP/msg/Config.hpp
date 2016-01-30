#ifndef LMP_MSG_CONFIG_HPP_
#define LMP_MSG_CONFIG_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <LMPMessageIF.hpp>
#include <LocalCCId.hpp>
#include <MessageId.hpp>
#include <LocalNodeId.hpp>
#include <HelloConfig.hpp>
#include <ProtocolTypes.hpp>                  // for DWORD

namespace lmp
{
  namespace msg
  {
    class Config : public LMPMessageIF
	{
	public:
      Config(
        const lmp::obj::LocalCCId&    localCCId,
		const lmp::obj::MessageId&    messageId,
		const lmp::obj::LocalNodeId&  localNodeId,
		const lmp::obj::HelloConfig&  helloConfig);
      inline const lmp::obj::LocalCCId& getLocalCCId() const { return m_localCCId; }
      inline const lmp::obj::MessageId& getMessageId() const { return m_messageId; }
      inline const lmp::obj::LocalNodeId& getLocalNodeId() const { return m_localNodeId; }
      inline const lmp::obj::HelloConfig& getHelloConfig() const { return m_helloConfig; }
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
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_HPP_ */
