/*
 * NodeIdData.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "NodeIdData.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>

namespace lmp
{
  namespace obj
  {
    const lmp::WORD NodeIdData::c_contentsLength = sizeof(lmp::DWORD);;

    NodeIdData::NodeIdData(
      lmp::DWORD  nodeId)
    : m_nodeId(nodeId)
    {}
    ObjectHeader::OptEncError NodeIdData::encode(
  	  boost::asio::mutable_buffer&  buffer) const
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
  	  lmp::DWORD* pDWordData  = boost::asio::buffer_cast<lmp::DWORD*>(buffer);
  	  if (bufSize >= c_contentsLength &&
  		  pDWordData)
  	  {
  		*pDWordData  = boost::endian::native_to_big(m_nodeId);
  		buffer = buffer + 4;
  		return boost::none;
  	  }
      return ObjectHeader::OptEncError(ObjectHeader::insufficient_buffer_length);
    }
    NodeIdData::DataTypeDecodingResult NodeIdData::decode(
        	boost::asio::const_buffer&    buffer)
    {
      std::size_t bufSize = boost::asio::buffer_size(buffer);
      const lmp::DWORD* pNodeId = boost::asio::buffer_cast<const lmp::DWORD*>(buffer);
      buffer = buffer + 4;
	  if (pNodeId)
	  {
        return
          DataTypeDecodingResult(opt_data_type(NodeIdData(boost::endian::big_to_native(*pNodeId))),
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
