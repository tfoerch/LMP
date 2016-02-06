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
    const lmp::WORD ControlChannelIdData::c_contentsLength = sizeof(lmp::DWORD);

    ControlChannelIdData::ControlChannelIdData(
      lmp::DWORD  controlChannelId)
    : m_controlChannelId(controlChannelId)
    {}
    ObjectHeader::OptEncError ControlChannelIdData::encode(
  	  boost::asio::mutable_buffer&  buffer) const
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
  	  lmp::DWORD* pDWordData  = boost::asio::buffer_cast<lmp::DWORD*>(buffer);
  	  if (bufSize >= c_contentsLength &&
  		  pDWordData)
  	  {
  		*pDWordData  = boost::endian::native_to_big(m_controlChannelId);
  		buffer = buffer + 4;
  		return boost::none;
  	  }
      return ObjectHeader::OptEncError(ObjectHeader::insufficient_buffer_length);
    }
    ControlChannelIdData::DataTypeDecodingResult ControlChannelIdData::decode(
        	boost::asio::const_buffer&    buffer)
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      const lmp::DWORD* pControlChannelId = boost::asio::buffer_cast<const lmp::DWORD*>(buffer);
	  buffer = buffer + 4;
	  if (pControlChannelId)
	  {
        return
          DataTypeDecodingResult(opt_data_type(ControlChannelIdData(boost::endian::big_to_native(*pControlChannelId))),
    	    		             boost::none);
	  }
      else
      {
        return
          DataTypeDecodingResult(boost::none,
        		                 ObjectHeader::OptDecError(ObjectHeader::unspecified_decoding_error));
      }
    }
  } // namespace obj
} // namespace lmp
