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
    const lmp::WORD HelloConfigData::c_contentsLength = 2*sizeof(lmp::WORD);

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
      if (bufSize >= c_contentsLength &&
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
    HelloConfigData::DataTypeDecodingResult HelloConfigData::decode(
        	boost::asio::const_buffer&    buffer)
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      const lmp::WORD* pHelloIntv = boost::asio::buffer_cast<const lmp::WORD*>(buffer);
      buffer = buffer + 2;
	  if (pHelloIntv)
	  {
	    const lmp::WORD* pHelloDeadIntv = boost::asio::buffer_cast<const lmp::WORD*>(buffer);
	    buffer = buffer + 2;
	    if (pHelloDeadIntv)
	    {
          return
            DataTypeDecodingResult(opt_data_type(HelloConfigData(boost::endian::big_to_native(*pHelloIntv),
            		                                             boost::endian::big_to_native(*pHelloDeadIntv))),
    	    		               boost::none);
	    }
	  }
	  return
        DataTypeDecodingResult(boost::none,
        		               ObjectHeader::OptDecError(ObjectHeader::unspecified_decoding_error));
    }
  } // namespace obj
} // namespace lmp
