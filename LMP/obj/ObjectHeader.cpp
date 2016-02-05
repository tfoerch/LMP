/*
 * ObjectHeader.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ObjectHeader.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>
//#include <iostream>

namespace lmp
{
  namespace obj
  {

    const lmp::WORD       ObjectHeader::c_headerLength = 4;
    const lmp::BYTE       ObjectHeader::c_negotiableMask = 0x80;
    const lmp::BYTE       ObjectHeader::c_classTypeMask = 0x7f;

    ObjectHeader::OptEncError ObjectHeader::encode(
      boost::asio::mutable_buffer&  buffer) const
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      unsigned char* pCharData = boost::asio::buffer_cast<unsigned char*>(buffer);
      if (bufSize >= c_headerLength &&
    	  pCharData)
      {
    	*pCharData =
    	  ( m_negotiable ?
    	    c_negotiableMask | ( c_classTypeMask & m_classType ) :
			( c_classTypeMask & m_classType ) );
    	buffer = buffer + 1;
    	pCharData = boost::asio::buffer_cast<unsigned char*>(buffer);
    	if (pCharData)
    	{
    	  *pCharData = static_cast<lmp::BYTE>(m_objectClass);
    	  buffer = buffer + 1;
    	  lmp::WORD* pWordData  = boost::asio::buffer_cast<lmp::WORD*>(buffer);
    	  if (pWordData)
    	  {
    		*pWordData  = boost::endian::native_to_big(m_objLength);
      	    buffer = buffer + 2;
    		return boost::none;
    	  }
    	}
      }
      return OptEncError(insufficient_buffer_length);
    }

    ObjectHeader::DecodingResult ObjectHeader::decode(
  	  boost::asio::const_buffer&    buffer)
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      const unsigned char* pCharData = boost::asio::buffer_cast<const unsigned char*>(buffer);
      if (bufSize >= c_headerLength &&
    	  pCharData)
      {
    	// std::cout << "bufSize = " << bufSize << std::endl;
    	bool negotiable = (c_negotiableMask & *pCharData);
        lmp::BYTE classType  = (c_classTypeMask & *pCharData);
        buffer = buffer + 1;
        pCharData = boost::asio::buffer_cast<const unsigned char*>(buffer);
        if (pCharData)
        {
          lmp::BYTE objectClass = *pCharData;
          // std::cout << "msgType = " << static_cast<lmp::WORD>(msgType) << std::endl;
          buffer = buffer + 1;
          const lmp::WORD* pWordData = boost::asio::buffer_cast<const lmp::WORD*>(buffer);
          if (pWordData)
          {
        	lmp::WORD objLength = boost::endian::big_to_native(*pWordData);
            buffer = buffer + 2;
        	OptObjectClass optObjectClass = objectClass_cast(objectClass);
        	if (optObjectClass)
        	{
        	  // std::cout << "msgType = " << *optMsgType << std::endl;
        	  return DecodingResult(OptHeader(ObjectHeader(negotiable,
        			                                       classType,
														   *optObjectClass,
														   objLength)),
            			            boost::none);
        	}
        	else
        	{
        	  return DecodingResult(boost::none, OptDecError(not_supported_object_class));
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
      	// std::cout << "invalid_length" << std::endl;
      	return DecodingResult(boost::none, OptDecError(invalid_length));
      }
    }

    ObjectHeader::OptObjectClass ObjectHeader::objectClass_cast(
  	  lmp::BYTE                     objectClassByte)
    {
      OptObjectClass result;
      const otype::ObjectClass objectClass = static_cast<otype::ObjectClass>(objectClassByte);
      switch(objectClass)
      {
        case otype::ControlChannelID:
        case otype::NodeID:
        case otype::LinkID:
        case otype::InterfaceID:
        case otype::MessageID:
        case otype::Config:
        case otype::Hello:
          result = objectClass;
          break;
        default:
          break;
      }
      return result;
    }

  } // namespace msg
} // namespace lmp
