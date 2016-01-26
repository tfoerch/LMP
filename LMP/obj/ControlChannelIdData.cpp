/*
 * ControlChannelIdData.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ControlChannelIdData.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>

namespace lmp
{
  namespace obj
  {
    const lmp::WORD ControlChannelIdData::c_contentsLength = 8;

    ControlChannelIdData::ControlChannelIdData(
      lmp::DWORD  controlChannelId)
    : m_controlChannelId(controlChannelId)
    {}
    ObjectHeader::OptEncError ControlChannelIdData::encode(
  	  boost::asio::mutable_buffer&  buffer) const
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
  	  lmp::DWORD* pDWordData  = boost::asio::buffer_cast<lmp::DWORD*>(buffer);
  	  if (bufSize >= sizeof(lmp::DWORD) &&
  		  pDWordData)
  	  {
  		*pDWordData  = boost::endian::native_to_big(m_controlChannelId);
  		buffer = buffer + 4;
  		return boost::none;
  	  }
      return ObjectHeader::OptEncError(ObjectHeader::insufficient_buffer_length);
    }
  } // namespace obj
} // namespace lmp
