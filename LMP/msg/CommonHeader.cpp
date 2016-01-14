/*
 * CommonHeader.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CommonHeader.hpp"
#include <boost/asio/buffer.hpp>

namespace lmp
{
  namespace msg
  {

    const lmp::WORD       CommonHeader::c_headerLength = 8;
    const lmp::BYTE       CommonHeader::c_versionMask = 0xf0;
    const lmp::BYTE       CommonHeader::c_supportedVersion = 1;
    const lmp::BYTE       CommonHeader::c_controlChannelDownMask = 0x01;
    const lmp::BYTE       CommonHeader::c_lmpRestart = 0x02;;

    CommonHeader::OptEncError CommonHeader::encode(
      boost::asio::mutable_buffer&  buffer) const
    {
      CommonHeader::OptEncError encResult;
      return encResult;
    }
    CommonHeader::DecodingResult CommonHeader::decode(
  	  boost::asio::const_buffer&    buffer)
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      const unsigned char* pCharData = boost::asio::buffer_cast<const unsigned char*>(buffer);
      if (bufSize >= c_headerLength ||
    	  pCharData)
      {
        lmp::BYTE  version = (c_versionMask & *pCharData) >> 4;
        if (version == c_supportedVersion)
        {
          buffer+2;
          pCharData = boost::asio::buffer_cast<const unsigned char*>(buffer);
          if (pCharData)
          {
        	bool controlChannelDown = (c_controlChannelDownMask & *pCharData);
        	bool lmpRestart = (c_lmpRestart & *pCharData);
        	buffer+1;
            pCharData = boost::asio::buffer_cast<const unsigned char*>(buffer);
            if (pCharData)
            {
              lmp::BYTE  msgType = *pCharData;
          	  buffer+1;
          	  const lmp::WORD* pWordData = boost::asio::buffer_cast<const lmp::WORD*>(buffer);
              if (pWordData)
              {
            	lmp::WORD lmpLength = *pWordData;
            	OptMsgType optMsgType = msgType_cast(msgType);
            	if (optMsgType)
            	{
            	  return DecodingResult(OptHeader(CommonHeader(version,
            			                                       controlChannelDown,
															   lmpRestart,
															   *optMsgType,
															   lmpLength)),
            			                boost::none);
            	}
            	else
            	{
                  return DecodingResult(boost::none, OptDecError(not_supported_msgType));
            	}
              }
              else
              {
                return DecodingResult(boost::none, OptDecError(unspecified_decoding_error));
              }
            }
            else
            {
              return DecodingResult(boost::none, OptDecError(unspecified_decoding_error));
            }
          }
          else
          {
        	return DecodingResult(boost::none, OptDecError(unspecified_decoding_error));
          }
        }
        else
        {
          return DecodingResult(boost::none, OptDecError(not_supported_version));
        }
      }
      else
      {
      	return DecodingResult(boost::none, OptDecError(invalid_length));
      }
    }
    CommonHeader::OptMsgType CommonHeader::msgType_cast(
  	lmp::BYTE                     msgTypeByte)
    {
      OptMsgType result;
      const MsgType msgType = static_cast<MsgType>(msgTypeByte);
      switch(msgType)
      {
        case Config:
        case ConfigAck:
        case ConfigNack:
          result = msgType;
          break;
        default:
          break;
      }
      return result;
    }

  } // namespace msg
} // namespace lmp
