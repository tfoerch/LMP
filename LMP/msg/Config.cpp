/*
 * Config.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Config.hpp"

namespace lmp
{
  namespace msg
  {
    Config::Config(
      const lmp::obj::LocalCCId&    localCCId,
      lmp::DWORD                    messageId,
      lmp::DWORD                    localNodeId,
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
      return m_localCCId.getObjLength() + 4 + 4 + m_helloConfig.getObjLength();
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
        optEncError = m_helloConfig.encode(buffer);
        if (optEncError &&
        	*optEncError == obj::ObjectHeader::insufficient_buffer_length)
        {
          return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
        }
      }
      return boost::none;
    }
  } // namespace msg
} // namespace lmp
