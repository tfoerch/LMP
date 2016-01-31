/*
 * ConfigNack.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigNack.hpp"

namespace lmp
{
  namespace msg
  {
    ConfigNack::ConfigNack(
      const lmp::obj::LocalCCId&     localCCId,
	  const lmp::obj::LocalNodeId&   localNodeId,
	  const lmp::obj::RemoteCCId&    remoteCCId,
	  const lmp::obj::MessageIdAck&  messageIdAck,
	  const lmp::obj::RemoteNodeId&  remoteNodeId,
	  const lmp::obj::HelloConfig&   helloConfig)
    : m_localCCId(localCCId),
	  m_localNodeId(localNodeId),
	  m_remoteCCId(remoteCCId),
	  m_messageIdAck(messageIdAck),
	  m_remoteNodeId(remoteNodeId),
	  m_helloConfig(helloConfig)
    {}
    const mtype::MsgType ConfigNack::do_getMsgType() const
    {
      return mtype::ConfigNack;
    }
    lmp::WORD ConfigNack::do_getContentsLength() const
    {
      return
        ( m_localCCId.getObjLength() +
      	  m_localNodeId.getObjLength() +
		  m_remoteCCId.getObjLength() +
		  m_messageIdAck.getObjLength() +
		  m_remoteNodeId.getObjLength() +
		  m_helloConfig.getObjLength() );
    }
    CommonHeader::OptEncError ConfigNack::do_encodeContents(
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
      		  else
      		  {
      			optEncError = m_helloConfig.encode(buffer);
      			if (optEncError &&
      		        *optEncError == obj::ObjectHeader::insufficient_buffer_length)
      			{
      			  return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
      			}
      		  }
    		}
    	  }
        }
      }
      return boost::none;
    }
  } // namespace msg
} // namespace lmp
