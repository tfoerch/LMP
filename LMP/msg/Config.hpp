#ifndef LMP_MSG_CONFIG_HPP_
#define LMP_MSG_CONFIG_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <LMPMessageIF.hpp>
#include <ProtocolTypes.hpp>                  // for DWORD
#include <HelloConfig.hpp>

namespace lmp
{
  namespace msg
  {
    class Config : public LMPMessageIF
	{
	public:
      Config(
		lmp::DWORD                    localCCId,
        lmp::DWORD                    messageId,
        lmp::DWORD                    localNodeId,
		const lmp::obj::HelloConfig&  helloConfig);
      inline lmp::WORD getLocalCCId() const { return m_localCCId; }
      inline lmp::WORD getMessageId() const { return m_messageId; }
      inline lmp::WORD getLocalNodeId() const { return m_localNodeId; }
      inline const lmp::obj::HelloConfig& getHelloConfig() const { return m_helloConfig; }
    private:
      virtual const mtype::MsgType do_getMsgType() const;
      virtual lmp::WORD do_getContentsLength() const;
      virtual CommonHeader::OptEncError do_encodeContents(
    	boost::asio::mutable_buffer&  buffer) const;
	  lmp::DWORD             m_localCCId;
	  lmp::DWORD             m_messageId;
	  lmp::DWORD             m_localNodeId;
	  lmp::obj::HelloConfig  m_helloConfig;
	};
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_HPP_ */
