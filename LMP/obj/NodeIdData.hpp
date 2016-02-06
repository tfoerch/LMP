#ifndef LMP_OBJ_NODE_ID_DATA_HPP_
#define LMP_OBJ_NODE_ID_DATA_HPP_
/*
 * NodeIdData.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for WORD
#include "obj/LMPObjectIF.hpp"

namespace lmp
{
  namespace obj
  {
    class NodeIdData
	{
	public:
      typedef boost::optional<NodeIdData>                            opt_data_type;
      typedef std::pair<opt_data_type, ObjectHeader::OptDecError>    DataTypeDecodingResult;
      NodeIdData(
    	lmp::DWORD  nodeId);
      inline lmp::DWORD getNodeId() const { return m_nodeId; }
      static lmp::WORD getContentsLength() { return c_contentsLength; }
      ObjectHeader::OptEncError encode(
    	boost::asio::mutable_buffer&  buffer) const;
      static DataTypeDecodingResult decode(
    	boost::asio::const_buffer&    buffer);
	private:
  	  lmp::DWORD              m_nodeId;
      static const lmp::WORD  c_contentsLength;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_DATA_HPP_ */
