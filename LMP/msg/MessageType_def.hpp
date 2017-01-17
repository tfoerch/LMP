#ifndef LMP_MSG_MESSAGE_TYPE_DEF_HPP_
#define LMP_MSG_MESSAGE_TYPE_DEF_HPP_
/*
 * MessageType_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageType.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/karma_attr_cast.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_TPL_STRUCT(
  (MsgTypeTraits),
  (lmp::msg::MessageTypeData)(MsgTypeTraits),
  (bool,                               m_controlChannelDown)
  (bool,                               m_LMP_restart)
  (typename MsgTypeTraits::data_type,  m_data))

namespace lmp
{
  namespace msg
  {
    template <typename   MsgTypeTraits>
    std::ostream& operator<<(
      std::ostream&                          os,
      const MessageTypeData<MsgTypeTraits>&  messageTypeData)
    {
      os << MsgTypeTraits::msg_type_value << '('
         << (messageTypeData.m_controlChannelDown ? "controlChannelDown" : "not controlChannelDown") << ", "
         << (messageTypeData.m_LMP_restart ? "LMP_restart" : "no LMP_restart") << ", "
         << messageTypeData.m_data << ')';
      return os;
    }
    template <typename   MsgTypeTraits>
    bool operator==(
      const MessageTypeData<MsgTypeTraits>&  first,
      const MessageTypeData<MsgTypeTraits>&  second)
    {
      return
        ( first.m_controlChannelDown == second.m_controlChannelDown &&
          first.m_LMP_restart == second.m_LMP_restart &&
          typename MsgTypeTraits::equal_ftor_type()(first.m_data, second.m_data) );
    }
    template <typename   MsgTypeTraits>
    lmp::WORD getLength(
      const MessageTypeData<MsgTypeTraits>&  messageTypeData)
    {
      return
        ( c_headerLength +
          typename MsgTypeTraits::get_length_ftor_type()(messageTypeData.m_data) );
    }
    template <typename   MsgTypeTraits>
    lmp::BYTE getFlags(
      const MessageTypeData<MsgTypeTraits>&  messageTypeData)
    {
      return
        ( messageTypeData.m_controlChannelDown ?
          ( messageTypeData.m_LMP_restart ?
            ( c_controlChannelDownMask | c_lmpRestartMask ) :
            c_controlChannelDownMask ) :
          ( messageTypeData.m_LMP_restart ?
            c_lmpRestartMask :
            0 ) );
    }
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator, MsgType msgType>
      message_type_grammar<Iterator, msgType>::message_type_grammar()
      : message_type_grammar<Iterator, msgType>::base_type(message_type_rule, "message_type")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::eps;
        using qi::_a;
        using qi::_1;
        using qi::attr;
        using phoenix::at_c;
        using namespace qi::labels;

        message_type_rule %=
            attr(_r1)
            >> attr(_r2)
            >> message_body(_r3)
            ;

        message_type_rule.name("message_type");
      }
    } // namespace parse
    namespace generate
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator, MsgType msgType>
      message_type_grammar<OutputIterator, msgType>::message_type_grammar()
      : message_type_grammar::base_type(message_type_rule, "message_type")
      {
        using phoenix::at_c;
        using qi::byte_;
        using qi::big_word;
        using namespace qi::labels;

        message_type_rule =
            common_header [ _1 = _val  ]
            << message_body [ _1 = at_c<2>(_val)  ]
            ;

        common_header =
            byte_       [ _1 = (c_supportedVersion << 4) ]  // version
            << byte_    [ _1 = phx_getFlags(_val) ]         // flags
            << byte_    [ _1 = 0 ]                          // reserved
            << byte_    [ _1 = static_cast<std::underlying_type<MsgType>::type>(msgType) ] // msg type
            << big_word [ _1 = phx_getLength(_val) ]        // length
            << big_word [ _1 = 0 ]                          // reserved
            ;

        message_type_rule.name("message_type");
      }
    } // namespace generate
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_TYPE_DEF_HPP_ */
