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
#include "base/ProtocolTypes.hpp"                  // for DWORD

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
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGNACK_HPP_ */
