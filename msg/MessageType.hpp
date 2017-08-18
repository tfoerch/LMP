#ifndef LMP_MSG_MESSAGE_TYPE_HPP_
#define LMP_MSG_MESSAGE_TYPE_HPP_
/*
 * MessageType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>

namespace lmp
{
  namespace msg
  {
    enum class MsgType : lmp::BYTE
    {
      Config = 1,
      ConfigAck,
      ConfigNack,
      Hello
    };
    std::ostream& operator<<(
      std::ostream&   os,
      const MsgType&  msgType);
    template <MsgType msgType>
    struct MessageTypeTraits
    {
      typedef MsgType            message_type;
      static const message_type  msg_type_value = msgType;
    };
    template <typename Iterator, MsgType msgType>
    struct MessageTypeParseTraits
    {
    };
    template <typename OutputIterator, MsgType msgType>
    struct MessageTypeGenerateTraits
    {
    };
    // instantiate following with MessageTypeData<MessageTypeTraits<msgType>>
    template <typename   MsgTypeTraits>
    class MessageTypeData
    {
    public:
      typedef typename MsgTypeTraits::message_type     message_type;
      // static const message_type                        msgType = template MsgTypeTraits::msg_type_value;
      bool                                             m_controlChannelDown;
      bool                                             m_LMP_restart;
      typename MsgTypeTraits::data_type                m_data;
    };
    template <typename   MsgTypeTraits>
    std::ostream& operator<<(
      std::ostream&                          os,
      const MessageTypeData<MsgTypeTraits>&  messageTypeData);
    template <typename   MsgTypeTraits>
    bool operator==(
       const MessageTypeData<MsgTypeTraits>&  first,
       const MessageTypeData<MsgTypeTraits>&  second);
    template <typename   MsgTypeTraits>
    lmp::WORD getLength(
      const MessageTypeData<MsgTypeTraits>&  messageTypeData);
    template <typename   MsgTypeTraits>
    struct GetLength
    {
      template<typename> struct result { typedef lmp::WORD type; };
      lmp::WORD operator()(
        const MessageTypeData<MsgTypeTraits>&  messageTypeData) const
      {
        return getLength(messageTypeData);
      }
    };
    template <typename   MsgTypeTraits>
    lmp::BYTE getFlags(
      const MessageTypeData<MsgTypeTraits>&  messageTypeData);
    template <typename   MsgTypeTraits>
    struct GetFlags
    {
      template<typename> struct result { typedef lmp::BYTE type; };
      lmp::BYTE operator()(
        const MessageTypeData<MsgTypeTraits>&  messageTypeData) const
      {
        return getFlags(messageTypeData);
      }
    };
    const lmp::WORD  c_headerLength = 8;
    const lmp::BYTE  c_versionMask = 0xf0;
    const lmp::BYTE  c_supportedVersion = 1;
    const lmp::BYTE  c_controlChannelDownMask = 0x01;
    const lmp::BYTE  c_lmpRestartMask = 0x02;
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator, MsgType msgType>
      struct message_type_grammar : qi::grammar<Iterator,
                                                MessageTypeData<MessageTypeTraits<msgType>>(bool,
                                                                                            bool,
                                                                                            lmp::WORD)>
      {
        message_type_grammar();

        typename MessageTypeParseTraits<Iterator, msgType>::grammar_type       message_body;
        qi::rule<Iterator,
                 MessageTypeData<MessageTypeTraits<msgType>>(bool,
                                                             bool,
                                                             lmp::WORD)>       message_type_rule;
      };
    }
    namespace generate
    {
      namespace qi = boost::spirit::qi;
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator, MsgType msgType>
      struct message_type_grammar : karma::grammar<OutputIterator, MessageTypeData<MessageTypeTraits<msgType>>()>
      {
        message_type_grammar();

        boost::phoenix::function<GetLength<MessageTypeTraits<msgType>>>              phx_getLength;
        boost::phoenix::function<GetFlags<MessageTypeTraits<msgType>>>               phx_getFlags;
        karma::rule<OutputIterator, MessageTypeData<MessageTypeTraits<msgType>>&()>  common_header;
        typename MessageTypeGenerateTraits<OutputIterator, msgType>::grammar_type    message_body;
        karma::rule<OutputIterator, MessageTypeData<MessageTypeTraits<msgType>>()>   message_type_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_TYPE_HPP_ */
