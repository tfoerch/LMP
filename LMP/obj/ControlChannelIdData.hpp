#ifndef LMP_OBJ_CONTROL_CHANNEL_ID_DATA_HPP_
#define LMP_OBJ_CONTROL_CHANNEL_ID_DATA_HPP_
/*
 * ControlChannelIdData.hpp
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
    class ControlChannelIdData
	{
	public:
      typedef boost::optional<ControlChannelIdData>                  opt_data_type;
      typedef std::pair<opt_data_type, ObjectHeader::OptDecError>    DataTypeDecodingResult;
      ControlChannelIdData(
    	lmp::DWORD  controlChannelId);
      inline lmp::DWORD getControlChannelId() const { return m_controlChannelId; }
      static lmp::WORD getContentsLength() { return c_contentsLength; }
      ObjectHeader::OptEncError encode(
    	boost::asio::mutable_buffer&  buffer) const;
      static DataTypeDecodingResult decode(
    	boost::asio::const_buffer&    buffer);
	private:
  	  lmp::DWORD              m_controlChannelId;
      static const lmp::WORD  c_contentsLength;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONTROL_CHANNEL_ID_DATA_HPP_ */
