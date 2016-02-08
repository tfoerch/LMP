#ifndef LMP_OBJ_MESSAGE_ID_DATA_HPP_
#define LMP_OBJ_MESSAGE_ID_DATA_HPP_
/*
 * MessageIdData.hpp
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
    class MessageIdData
	{
	public:
      typedef boost::optional<MessageIdData>                         opt_data_type;
      typedef std::pair<opt_data_type, ObjectHeader::OptDecError>    DataTypeDecodingResult;
      MessageIdData(
    	lmp::DWORD  MessageId);
      inline lmp::DWORD getMessageId() const { return m_messageId; }
      static lmp::WORD getContentsLength() { return c_contentsLength; }
      ObjectHeader::OptEncError encode(
    	boost::asio::mutable_buffer&  buffer) const;
      static DataTypeDecodingResult decode(
    	boost::asio::const_buffer&    buffer);
	private:
  	  lmp::DWORD              m_messageId;
      static const lmp::WORD  c_contentsLength;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_DATA_HPP_ */
