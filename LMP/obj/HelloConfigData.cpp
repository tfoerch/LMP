/*
 * HelloConfigData.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "HelloConfigData.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>

namespace lmp
{
  namespace obj
  {
    const lmp::WORD HelloConfigData::c_contentsLength = 8;

    HelloConfigData::HelloConfigData(
      lmp::WORD  helloIntv,
	  lmp::WORD  helloDeadIntv)
    : m_helloIntv(helloIntv),
	  m_helloDeadIntv(helloDeadIntv)
    {}
    ObjectHeader::OptEncError HelloConfigData::encode(
  	boost::asio::mutable_buffer&  buffer) const
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
	  lmp::WORD* pWordData  = boost::asio::buffer_cast<lmp::WORD*>(buffer);
      if (bufSize >= 2*sizeof(lmp::WORD) &&
    	  pWordData)
      {
    	*pWordData  = boost::endian::native_to_big(m_helloIntv);
  	    buffer = buffer + 2;
  	    pWordData  = boost::asio::buffer_cast<lmp::WORD*>(buffer);
  	    if (pWordData)
  	    {
  	      *pWordData  = boost::endian::native_to_big(m_helloDeadIntv);
  	      buffer = buffer + 2;
  	      return boost::none;
  	    }
      }
      return ObjectHeader::OptEncError(ObjectHeader::insufficient_buffer_length);
    }
  } // namespace obj
} // namespace lmp
