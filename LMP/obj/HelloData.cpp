/*
 * HelloData.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "HelloData.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>

namespace lmp
{
  namespace obj
  {
    const lmp::WORD HelloData::c_contentsLength = 2*sizeof(lmp::DWORD);

    HelloData::HelloData(
      lmp::DWORD  txSeqNum,
	  lmp::DWORD  rcvSeqNum)
    : m_txSeqNum(txSeqNum),
	  m_rcvSeqNum(rcvSeqNum)
    {}
    ObjectHeader::OptEncError HelloData::encode(
  	boost::asio::mutable_buffer&  buffer) const
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
	  lmp::DWORD* pDWordData  = boost::asio::buffer_cast<lmp::DWORD*>(buffer);
      if (bufSize >= c_contentsLength &&
    	  pDWordData)
      {
    	*pDWordData  = boost::endian::native_to_big(m_txSeqNum);
  	    buffer = buffer + 4;
  	    pDWordData  = boost::asio::buffer_cast<lmp::DWORD*>(buffer);
  	    if (pDWordData)
  	    {
  	      *pDWordData  = boost::endian::native_to_big(m_rcvSeqNum);
  	      buffer = buffer + 4;
  	      return boost::none;
  	    }
      }
      return ObjectHeader::OptEncError(ObjectHeader::insufficient_buffer_length);
    }
  } // namespace obj
} // namespace lmp
