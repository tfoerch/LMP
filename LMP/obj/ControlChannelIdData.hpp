#ifndef LMP_OBJ_CONTROL_CHANNEL_ID_DATA_HPP_
#define LMP_OBJ_CONTROL_CHANNEL_ID_DATA_HPP_
/*
 * ControlChannelIdData.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>                  // for WORD
#include <LMPObjectIF.hpp>

namespace lmp
{
  namespace obj
  {
    class ControlChannelIdData
	{
	public:
      ControlChannelIdData(
    	lmp::DWORD  controlChannelId);
      inline lmp::DWORD getControlChannelId() const { return m_controlChannelId; }
      lmp::WORD getContentsLength() const { return c_contentsLength; }
      ObjectHeader::OptEncError encode(
    	boost::asio::mutable_buffer&  buffer) const;
	private:
  	  lmp::DWORD              m_controlChannelId;
      static const lmp::WORD  c_contentsLength;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONTROL_CHANNEL_ID_DATA_HPP_ */
