#ifndef LMP_MSG_COMMONHEADER_HPP_
#define LMP_MSG_COMMONHEADER_HPP_
/*
 * CommonHeader.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include "msg/MsgType.hpp"

#include <boost/optional/optional.hpp>     // for optional

#include <utility>

namespace boost
{
  namespace asio
  {
    class const_buffer;
    class mutable_buffer;
  }
}

namespace lmp
{
  namespace msg
  {
    class CommonHeader
	{
	public:
      typedef boost::optional<CommonHeader>      OptHeader;
      enum decoding_error
	  {
    	not_supported_msgType,
		invalid_length,
		not_supported_version,
		not_supported_flag,
		unspecified_decoding_error
	  };
      enum encoding_error
	  {
    	insufficient_buffer_length
	  };
      typedef boost::optional<decoding_error>    OptDecError;
      typedef std::pair<OptHeader, OptDecError>  DecodingResult;
      typedef boost::optional<encoding_error>    OptEncError;
      typedef boost::optional<mtype::MsgType>    OptMsgType;
      inline CommonHeader(
        lmp::BYTE                    version,
		bool                         controlChannelDown,
		bool                         lmpRestart,
		mtype::MsgType               msgType,
		lmp::WORD                    lmpLength)
      : m_version(version),
		m_controlChannelDown(controlChannelDown),
		m_lmpRestart(lmpRestart),
		m_msgType(msgType),
		m_lmpLength(lmpLength)
      {}
      inline lmp::BYTE getVersion() const { return m_version; }
      inline bool isControlChannelDown() const { return m_controlChannelDown; }
      inline bool isLmpRestart() const { return m_lmpRestart; }
      inline const mtype::MsgType getMsgType() const { return m_msgType; }
      inline lmp::WORD getLmpLength() const { return m_lmpLength; }
      OptEncError encode(
        boost::asio::mutable_buffer&  buffer) const;
      static DecodingResult decode(
    	boost::asio::const_buffer&    buffer);
      static OptMsgType msgType_cast(
    	lmp::BYTE                     msgTypeByte);
	private:
      lmp::BYTE                    m_version;
      bool                         m_controlChannelDown;
      bool                         m_lmpRestart;
      mtype::MsgType               m_msgType;
	  lmp::WORD                    m_lmpLength;
	public:
	  static const lmp::WORD       c_headerLength;
	  static const lmp::BYTE       c_versionMask;
	  static const lmp::BYTE       c_supportedVersion;
	  static const lmp::BYTE       c_controlChannelDownMask;
	  static const lmp::BYTE       c_lmpRestartMask;
	};
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_COMMONHEADER_HPP_ */
