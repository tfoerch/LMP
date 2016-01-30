/*
 * MessageIdData.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "MessageIdData.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>

namespace lmp
{
  namespace obj
  {
    const lmp::WORD MessageIdData::c_contentsLength = sizeof(lmp::DWORD);

    MessageIdData::MessageIdData(
      lmp::DWORD  messageId)
    : m_messageId(messageId)
    {}
    ObjectHeader::OptEncError MessageIdData::encode(
  	  boost::asio::mutable_buffer&  buffer) const
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
  	  lmp::DWORD* pDWordData  = boost::asio::buffer_cast<lmp::DWORD*>(buffer);
  	  if (bufSize >= c_contentsLength &&
  		  pDWordData)
  	  {
  		*pDWordData  = boost::endian::native_to_big(m_messageId);
  		buffer = buffer + 4;
  		return boost::none;
  	  }
      return ObjectHeader::OptEncError(ObjectHeader::insufficient_buffer_length);
    }
  } // namespace obj
} // namespace lmp
