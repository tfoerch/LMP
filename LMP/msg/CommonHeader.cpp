/*
 * CommonHeader.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CommonHeader.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>
//#include <iostream>

namespace lmp
{
  namespace msg
  {

    const lmp::WORD       CommonHeader::c_headerLength = 8;
    const lmp::BYTE       CommonHeader::c_versionMask = 0xf0;
    const lmp::BYTE       CommonHeader::c_supportedVersion = 1;
    const lmp::BYTE       CommonHeader::c_controlChannelDownMask = 0x01;
    const lmp::BYTE       CommonHeader::c_lmpRestartMask = 0x02;;

    CommonHeader::OptEncError CommonHeader::encode(
      boost::asio::mutable_buffer&  buffer) const
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      unsigned char* pCharData = boost::asio::buffer_cast<unsigned char*>(buffer);
      if (bufSize >= c_headerLength &&
    	  pCharData)
      {
    	*pCharData = (m_version << 4);
        buffer = buffer + 1;
        pCharData = boost::asio::buffer_cast<unsigned char*>(buffer);
        if (pCharData)
        {
          *pCharData = 0x00;
          buffer = buffer + 1;
          pCharData = boost::asio::buffer_cast<unsigned char*>(buffer);
          if (pCharData)
          {
            *pCharData =
              ( m_controlChannelDown ?
                ( m_lmpRestart ?
                  c_controlChannelDownMask | c_lmpRestartMask :
				  c_controlChannelDownMask ) :
				( m_lmpRestart ?
				  c_lmpRestartMask :
				  0x00 ) );
            buffer = buffer + 1;
            pCharData = boost::asio::buffer_cast<unsigned char*>(buffer);
            if (pCharData)
            {
              *pCharData = static_cast<lmp::BYTE>(m_msgType);
              buffer = buffer + 1;
              lmp::WORD* pWordData  = boost::asio::buffer_cast<lmp::WORD*>(buffer);
              if (pWordData)
              {
                *pWordData  = boost::endian::native_to_big(m_lmpLength);
                buffer = buffer + 2;
                pWordData  = boost::asio::buffer_cast<lmp::WORD*>(buffer);
                if (pWordData)
                {
                  *pWordData  = 0x00;
                  return boost::none;
                }
              }
            }
          }
        }
      }
      return OptEncError(insufficient_buffer_length);
    }

    CommonHeader::DecodingResult CommonHeader::decode(
  	  boost::asio::const_buffer&    buffer)
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      const unsigned char* pCharData = boost::asio::buffer_cast<const unsigned char*>(buffer);
      if (bufSize >= c_headerLength &&
    	  pCharData)
      {
    	// std::cout << "bufSize = " << bufSize << std::endl;
        lmp::BYTE  version = (c_versionMask & *pCharData) >> 4;
        if (version == c_supportedVersion)
        {
          // std::cout << "version = " << static_cast<lmp::WORD>(version) << std::endl;
          buffer = buffer + 2;
          pCharData = boost::asio::buffer_cast<const unsigned char*>(buffer);
          if (pCharData)
          {
        	bool controlChannelDown = (c_controlChannelDownMask & *pCharData);
        	bool lmpRestart = (c_lmpRestartMask & *pCharData);
        	buffer = buffer + 1;
            pCharData = boost::asio::buffer_cast<const unsigned char*>(buffer);
            if (pCharData)
            {
              lmp::BYTE  msgType = *pCharData;
              // std::cout << "msgType = " << static_cast<lmp::WORD>(msgType) << std::endl;
              buffer = buffer + 1;
          	  const lmp::WORD* pWordData = boost::asio::buffer_cast<const lmp::WORD*>(buffer);
              if (pWordData)
              {
            	lmp::WORD lmpLength = boost::endian::big_to_native(*pWordData);
                // std::cout << "lmpLength = " << lmpLength << std::endl;
                buffer = buffer + 4; // length and reserved field
            	OptMsgType optMsgType = msgType_cast(msgType);
            	if (optMsgType)
            	{
                  // std::cout << "msgType = " << *optMsgType << std::endl;
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
      	// std::cout << "invalid_length" << std::endl;
      	return DecodingResult(boost::none, OptDecError(invalid_length));
      }
    }

    CommonHeader::OptMsgType CommonHeader::msgType_cast(
  	lmp::BYTE                     msgTypeByte)
    {
      OptMsgType result;
      const mtype::MsgType msgType = static_cast<mtype::MsgType>(msgTypeByte);
      switch(msgType)
      {
        case mtype::Config:
        case mtype::ConfigAck:
        case mtype::ConfigNack:
        case mtype::Hello:
          result = msgType;
          break;
        default:
          break;
      }
      return result;
    }

  } // namespace msg
} // namespace lmp
