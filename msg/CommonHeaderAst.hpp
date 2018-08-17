#ifndef LMP_MSG_COMMONHEADER_AST_HPP_
#define LMP_MSG_COMMONHEADER_AST_HPP_
/*
 * CommonHeaderAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include "MessageType.hpp"

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      struct CommonHeaderFlags
      {
        bool  m_controlChannelDown;
        bool  m_LMP_restart;
      };
      template <typename   MsgTypeTraits>
      struct CommonHeader
      {
//        CommonHeader() = default;
//        CommonHeader(
//          const CommonHeaderFlags&  headerFlags)
//        : m_controlChannelDown(headerFlags.m_controlChannelDown),
//          m_LMP_restart(headerFlags.m_LMP_restart)
//        {
//        }
//        CommonHeader& operator=(
//          const CommonHeaderFlags&  headerFlags)
//        {
//          m_controlChannelDown = headerFlags.m_controlChannelDown;
//          m_LMP_restart = headerFlags.m_LMP_restart;
//          return *this;
//        }
        typedef typename MsgTypeTraits::message_type  message_type;
        static const message_type                     c_msgType;
        bool                                          m_controlChannelDown;
        bool                                          m_LMP_restart;
      };
      struct CommonHeaderUnknownMsgType
      {
        lmp::BYTE          m_msgType;
        CommonHeaderFlags  m_flags;
      };
      template<typename MsgTypeTraits>
      struct ConstructCommonHeader
      {
        template<typename> struct result { typedef CommonHeader<MsgTypeTraits> type; };
        CommonHeader<MsgTypeTraits> operator()(
          const CommonHeaderFlags&  headerFlags) const
        {
          CommonHeader<MsgTypeTraits> result = { headerFlags.m_controlChannelDown, headerFlags.m_LMP_restart };
          return result; // CommonHeader<MsgTypeTraits>(headerFlags);
        }
      };
      template<typename MsgTypeTraits>
      struct GetFlags
      {
        template<typename> struct result { typedef lmp::BYTE type; };
        lmp::BYTE operator()(
          const CommonHeader<MsgTypeTraits>&  header) const
        {
          return
            ( header.m_controlChannelDown ?
              ( header.m_LMP_restart ?
                c_controlChannelDownMask & c_lmpRestartMask :
                c_controlChannelDownMask ) :
              ( header.m_LMP_restart ?
                c_lmpRestartMask :
                0 ) );
        }
      };
      struct GetFlagsFromCommonHeaderFlags
      {
        template<typename> struct result { typedef lmp::BYTE type; };
        lmp::BYTE operator()(
          const CommonHeaderFlags&  headerFlags) const
        {
          return
            ( headerFlags.m_controlChannelDown ?
              ( headerFlags.m_LMP_restart ?
                c_controlChannelDownMask & c_lmpRestartMask :
                c_controlChannelDownMask ) :
              ( headerFlags.m_LMP_restart ?
                c_lmpRestartMask :
                0 ) );
        }
      };

      std::ostream& operator<<(
        std::ostream&             os,
        const CommonHeaderFlags&  commonHeaderFlags);
      std::ostream& operator<<(
        std::ostream&             os,
        const CommonHeaderUnknownMsgType&       commonHeader);
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_COMMONHEADER_AST_HPP_ */
