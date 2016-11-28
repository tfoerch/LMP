/*
 * Config.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Config_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::config_grammar<BufIterType>;

namespace lmp
{
  namespace msg
  {
    Config::Config(
      const lmp::obj::LocalCCId&    localCCId,
	  const lmp::obj::MessageId&    messageId,
	  const lmp::obj::LocalNodeId&  localNodeId,
 	  const lmp::obj::HelloConfig&  helloConfig)
    : m_localCCId(localCCId),
	  m_messageId(messageId),
	  m_localNodeId(localNodeId),
	  m_helloConfig(helloConfig)
    {}
    const mtype::MsgType Config::do_getMsgType() const
    {
      return mtype::Config;
    }
    lmp::WORD Config::do_getContentsLength() const
    {
      return
        ( m_localCCId.getObjLength() +
          m_messageId.getObjLength() +
		  m_localNodeId.getObjLength() +
		  m_helloConfig.getObjLength() );
    }
    CommonHeader::OptEncError Config::do_encodeContents(
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
    	optEncError = m_messageId.encode(buffer);
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
        	optEncError = m_helloConfig.encode(buffer);
        	if (optEncError &&
        	    *optEncError == obj::ObjectHeader::insufficient_buffer_length)
        	{
        	  return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
        	}
          }
        }
      }
      return boost::none;
    }
    Config::DecodingResult Config::decode(
      const CommonHeader&         msgHeader,
  	  boost::asio::const_buffer&  buffer)
    {
      // std::cout << "Config::decode" << std::endl;
      DecodingResult decodingResult;
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      std::size_t bytesRead = CommonHeader::c_headerLength;
	  // <LOCAL_CCID>
	  lmp::obj::LocalCCId::DecodingResult localCCIdDecodingResult;
      if (bufSize > lmp::obj::ObjectHeader::c_headerLength &&
     	  bytesRead + lmp::obj::ObjectHeader::c_headerLength < msgHeader.getLmpLength())
      {
      	lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
            lmp::obj::ObjectHeader::decode(buffer);
      	if (headerDecodingResult.first)
      	{
      	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
      	  if (header.getObjectClass() == lmp::obj::otype::ControlChannelID)
      	  {
      		lmp::obj::ObjectClassIF<lmp::obj::ccid::ClassType>::OptClassType optCType =
      		  lmp::obj::ObjectClassIF<lmp::obj::ccid::ClassType>::classType_cast(header.getClassType());
       	    if (optCType &&
       	    	*optCType == lmp::obj::ccid::ClassType::LocalCCId)
       	    {
       	      localCCIdDecodingResult =
       	        lmp::obj::LocalCCId::decode(header, buffer);
       	      if (localCCIdDecodingResult.first)
       	      {
       			const lmp::obj::LocalCCId& localCCId = *localCCIdDecodingResult.first;
       	    	std::cout << "localCCId = " << localCCId.getControlChannelId() << std::endl;
       	      }
       	      else if (localCCIdDecodingResult.second)
       	      {
       	    	if (*localCCIdDecodingResult.second == lmp::obj::ObjectHeader::invalid_length)
       	    	{
       	    	  decodingResult.second = OptDecError(invalid_length);
       	    	}
       	    	else
       	    	{
       	    	  decodingResult.second = OptDecError(unspecified_decoding_error);
       	    	}
       	      }
       	    }
      	  }
      	}
      }
      // <MESSAGE_ID>
      if (!decodingResult.second)
      {
	    lmp::obj::MessageId::DecodingResult messageIdDecodingResult;
	    if (bufSize > lmp::obj::ObjectHeader::c_headerLength &&
		    bytesRead + lmp::obj::ObjectHeader::c_headerLength < msgHeader.getLmpLength())
	    {
	      lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
	        lmp::obj::ObjectHeader::decode(buffer);
	      if (headerDecodingResult.first)
	      {
	    	const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	    	if (header.getObjectClass() == lmp::obj::otype::MessageID)
	    	{
	          lmp::obj::ObjectClassIF<lmp::obj::msgid::ClassType>::OptClassType optCType =
			    lmp::obj::ObjectClassIF<lmp::obj::msgid::ClassType>::classType_cast(header.getClassType());
	          if (optCType &&
	        	  *optCType == lmp::obj::msgid::ClassType::MessageId)
	          {
	        	messageIdDecodingResult =
				  lmp::obj::MessageId::decode(header, buffer);
	        	if (messageIdDecodingResult.first)
	        	{
	        	  const lmp::obj::MessageId& messageId = *messageIdDecodingResult.first;
	        	  std::cout << "messageId = " << messageId.getMessageId() << std::endl;
	        	}
	          }
	    	}
	      }
	    }
	    // <LOCAL_NODE_ID>
	    if (!decodingResult.second)
	    {
	      lmp::obj::LocalNodeId::DecodingResult localNodeIdDecodingResult;
	      if (bufSize > lmp::obj::ObjectHeader::c_headerLength &&
		      bytesRead + lmp::obj::ObjectHeader::c_headerLength < msgHeader.getLmpLength())
	      {
	        lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
			  lmp::obj::ObjectHeader::decode(buffer);
	        if (headerDecodingResult.first)
	        {
	          const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	          if (header.getObjectClass() == lmp::obj::otype::NodeID)
	          {
	    	    lmp::obj::ObjectClassIF<lmp::obj::nodeid::ClassType>::OptClassType optCType =
			      lmp::obj::ObjectClassIF<lmp::obj::nodeid::ClassType>::classType_cast(header.getClassType());
	    	    if (optCType &&
	    		    *optCType == lmp::obj::nodeid::ClassType::LocalNodeId)
	    	    {
	    		  localNodeIdDecodingResult =
				    lmp::obj::LocalNodeId::decode(header, buffer);
	    		  if (localNodeIdDecodingResult.first)
	    		  {
				    const lmp::obj::LocalNodeId& localNodeId = *localNodeIdDecodingResult.first;
				    std::cout << "localNodeId = " << localNodeId.getNodeId() << std::endl;
	    		  }
	    	    }
	          }
	        }
	      }
	      // <CONFIG> = HelloConfig
	      if (!decodingResult.second)
	      {
	    	lmp::obj::HelloConfig::DecodingResult helloConfigDecodingResult;
	    	if (bufSize > lmp::obj::ObjectHeader::c_headerLength &&
		        bytesRead + lmp::obj::ObjectHeader::c_headerLength < msgHeader.getLmpLength())
	    	{
     		  lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
     		    lmp::obj::ObjectHeader::decode(buffer);
     		  if (headerDecodingResult.first)
     		  {
		        const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
		        if (header.getObjectClass() == lmp::obj::otype::Config)
		        {
		          lmp::obj::ObjectClassIF<lmp::obj::config::ClassType>::OptClassType optCType =
			        lmp::obj::ObjectClassIF<lmp::obj::config::ClassType>::classType_cast(header.getClassType());
		          if (optCType &&
				      *optCType == lmp::obj::config::ClassType::HelloConfig)
		          {
			        helloConfigDecodingResult =
				      lmp::obj::HelloConfig::decode(header, buffer);
			        if (helloConfigDecodingResult.first)
			        {
				      const lmp::obj::HelloConfig& helloConfig = *helloConfigDecodingResult.first;
				      std::cout << "helloIntv = " << helloConfig.getHelloIntv()
					            << ", helloDeadIntv = " << helloConfig.getHelloDeadIntv() << std::endl;
				      decodingResult.first =
				        OptMsg(Config(*localCCIdDecodingResult.first,
				    	 	          *messageIdDecodingResult.first,
									  *localNodeIdDecodingResult.first,
									  *helloConfigDecodingResult.first));
			        }
		          }
			    }
		      }
     		}
     	  }
	    }
      }
      return decodingResult;
    }
    namespace parse
    {
	  std::ostream& operator<<(
	    std::ostream&          os,
		const ConfigMsgData& config)
	  {
		std::cout << "ConfigMsg(" << static_cast<lmp::WORD>(config.m_flags)
				  << ", " << config.m_localCCId
		    	  << ", " << config.m_messageId
				  << ", " << config.m_localNodeId
				  << ", " << config.m_helloConfig
				  << ")";
		return os;
	  }
    }
  } // namespace msg
} // namespace lmp
