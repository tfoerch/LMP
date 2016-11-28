/*
 * ConfigAck.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigAck_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::config_ack_grammar<BufIterType>;

namespace lmp
{
  namespace msg
  {
    ConfigAck::ConfigAck(
      const lmp::obj::LocalCCId&     localCCId,
	  const lmp::obj::LocalNodeId&   localNodeId,
	  const lmp::obj::RemoteCCId&    remoteCCId,
	  const lmp::obj::MessageIdAck&  messageIdAck,
	  const lmp::obj::RemoteNodeId&  remoteNodeId)
    : m_localCCId(localCCId),
	  m_localNodeId(localNodeId),
	  m_remoteCCId(remoteCCId),
	  m_messageIdAck(messageIdAck),
	  m_remoteNodeId(remoteNodeId)
    {}
    const mtype::MsgType ConfigAck::do_getMsgType() const
    {
      return mtype::ConfigAck;
    }
    lmp::WORD ConfigAck::do_getContentsLength() const
    {
      return
        ( m_localCCId.getObjLength() +
      	  m_localNodeId.getObjLength() +
		  m_remoteCCId.getObjLength() +
		  m_messageIdAck.getObjLength() +
		  m_remoteNodeId.getObjLength() );
    }
    CommonHeader::OptEncError ConfigAck::do_encodeContents(
  	  boost::asio::mutable_buffer&  buffer) const
    {
      obj::ObjectHeader::OptEncError optEncError = m_localCCId.encode(buffer);
      if (optEncError &&
    	  *optEncError == obj::ObjectHeader::insufficient_buffer_length)
      {
    	return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
      }
      else
      {
    	optEncError = m_localNodeId.encode(buffer);
    	if (optEncError &&
    		*optEncError == obj::ObjectHeader::insufficient_buffer_length)
    	{
    	  return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
    	}
    	else
    	{
    	  optEncError = m_remoteCCId.encode(buffer);
    	  if (optEncError &&
    		  *optEncError == obj::ObjectHeader::insufficient_buffer_length)
    	  {
    		return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
    	  }
    	  else
    	  {
    		optEncError = m_messageIdAck.encode(buffer);
    		if (optEncError &&
    		    *optEncError == obj::ObjectHeader::insufficient_buffer_length)
    		{
    		  return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
    		}
    		else
    		{
    		  optEncError = m_remoteNodeId.encode(buffer);
    		  if (optEncError &&
    		      *optEncError == obj::ObjectHeader::insufficient_buffer_length)
    		  {
    			return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
    		  }
    		}
    	  }
        }
      }
      return boost::none;
    }
    namespace parse
    {
	  std::ostream& operator<<(
	    std::ostream&             os,
		const ConfigAckMsgData& configAck)
	  {
	    std::cout << "ConfigAckMsg(" << static_cast<lmp::WORD>(configAck.m_flags)
		          << ", " << configAck.m_localCCId
		  		  << ", " << configAck.m_localNodeId
				  << ", " << configAck.m_remoteCCId
				  << ", " << configAck.m_messageId
				  << ", " << configAck.m_remoteNodeId
				  << ")";
	    return os;
	  }
    }
  } // namespace msg
} // namespace lmp
