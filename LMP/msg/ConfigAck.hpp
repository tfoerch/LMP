#ifndef LMP_MSG_CONFIGACK_HPP_
#define LMP_MSG_CONFIGACK_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <LMPMessageIF.hpp>
#include <LocalCCId.hpp>
#include <LocalNodeId.hpp>
#include <RemoteCCId.hpp>
#include <MessageIdAck.hpp>
#include <RemoteNodeId.hpp>
#include <ProtocolTypes.hpp>                  // for DWORD

namespace lmp
{
  namespace msg
  {
    class ConfigAck : public LMPMessageIF
	{
	public:
      ConfigAck(
    	const lmp::obj::LocalCCId&     localCCId,
		const lmp::obj::LocalNodeId&   localNodeId,
    	const lmp::obj::RemoteCCId&    remoteCCId,
		const lmp::obj::MessageIdAck&  messageIdAck,
		const lmp::obj::RemoteNodeId&  remoteNodeId);
      inline const lmp::obj::LocalCCId& getLocalCCId() const { return m_localCCId; }
      inline const lmp::obj::LocalNodeId& getLocalNodeId() const { return m_localNodeId; }
      inline const lmp::obj::RemoteCCId& getRemoteCCId() const { return m_remoteCCId; }
      inline const lmp::obj::MessageIdAck& getMessageIdAck() const { return m_messageIdAck; }
      inline const lmp::obj::RemoteNodeId& getRemoteNodeId() const { return m_remoteNodeId; }
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
	};
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGACK_HPP_ */
