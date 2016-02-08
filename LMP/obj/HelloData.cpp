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
    HelloData::DataTypeDecodingResult HelloData::decode(
        	boost::asio::const_buffer&    buffer)
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      const lmp::DWORD* pTxSeqNum = boost::asio::buffer_cast<const lmp::DWORD*>(buffer);
      buffer = buffer + 4;
	  if (pTxSeqNum)
	  {
	    const lmp::DWORD* pRcvSeqNum = boost::asio::buffer_cast<const lmp::DWORD*>(buffer);
	    buffer = buffer + 4;
	    if (pRcvSeqNum)
	    {
          return
            DataTypeDecodingResult(opt_data_type(HelloData(boost::endian::big_to_native(*pTxSeqNum),
            		                                       boost::endian::big_to_native(*pRcvSeqNum))),
    	    		               boost::none);
	    }
	  }
	  return
        DataTypeDecodingResult(boost::none,
        		               ObjectHeader::OptDecError(ObjectHeader::unspecified_decoding_error));
    }
  } // namespace obj
} // namespace lmp
