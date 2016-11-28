/*
 * ObjectHeader.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ObjectHeader_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/endian/conversion.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::parse::object_header_fix_length_grammar<BufIterType>;
template struct lmp::obj::parse::object_header_unknown_class_type_grammar<BufIterType>;
template struct lmp::obj::parse::object_header_unknown_object_class_grammar<BufIterType>;
template struct lmp::obj::generate::object_header_grammar<BufOutIterType>;

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
        	  std::cout << "objectClass = " << *optObjectClass << std::endl;
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
    std::ostream& operator<<(
      std::ostream&            os,
	  const ObjectHeaderData&  objectHeader)
    {
  	  os << static_cast<lmp::WORD>(objectHeader.m_object_class) << ", "
  	     << static_cast<lmp::WORD>(objectHeader.m_class_type) << ", "
		 << (objectHeader.m_negotiable ? "negotiable" : "not negotiable") << ", "
		   << objectHeader.m_length;
  	  return os;
    }
    ObjectHeaderData::ObjectHeaderData()
    {}
    ObjectHeaderData::ObjectHeaderData(
  	  lmp::BYTE               object_class,
	  lmp::BYTE               class_type,
	  lmp::WORD               length)
    : m_object_class(object_class),
	  m_class_type(class_type),
	  m_length(length)
    {}
    namespace parse
    {
      ObjectHeaderFixLengthInput::ObjectHeaderFixLengthInput(
        lmp::BYTE               object_class,
		lmp::BYTE               class_type,
		lmp::WORD               length)
      : m_object_class(object_class),
		m_class_type(class_type),
		m_length(length)
	  {}
      std::ostream& operator<<(
        std::ostream&                          os,
  	    const ObjectHeaderUnknownCTypeOutput&  unknownClassType)
      {
    	os << static_cast<lmp::WORD>(unknownClassType.m_class_type) << ", "
    	   << (unknownClassType.m_negotiable ? "negotiable" : "not negotiable") << ", "
		   << unknownClassType.m_length;
    	return os;
      }
    } // namespace parse
  } // namespace obj
} // namespace lmp
