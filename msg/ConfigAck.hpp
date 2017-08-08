#ifndef LMP_MSG_CONFIGACK_HPP_
#define LMP_MSG_CONFIGACK_HPP_
/*
 * ConfigAck.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageType.hpp"
#include "obj/LocalCCId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/RemoteNodeId.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace config_ack
    {
      struct ConfigAckBody
      {
        lmp::obj::ccid::LocalCCIdData       m_localCCId;
        lmp::obj::nodeid::LocalNodeIdData   m_localNodeId;
        lmp::obj::ccid::RemoteCCIdData      m_remoteCCId;
        lmp::obj::msgid::MessageIdAckData   m_messageId;
        lmp::obj::nodeid::RemoteNodeIdData  m_remoteNodeId;
      };
      std::ostream& operator<<(
        std::ostream&         os,
        const ConfigAckBody&  configAckBody);
      struct IsEqualFtor
      {
        bool operator()(
          const ConfigAckBody&  first,
          const ConfigAckBody&  second) const;
      };
      struct GetLengthFtor
      {
        lmp::WORD operator()(
          const ConfigAckBody&  configAckBody) const;
      };
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct config_ack_body_grammar : qi::grammar<Iterator, ConfigAckBody(lmp::WORD)>
        {
          config_ack_body_grammar();

          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::ccid::ClassType,
                                                lmp::obj::ccid::ClassType::LocalCCId>    local_ccid;
          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::ccid::ClassType,
                                                lmp::obj::ccid::ClassType::RemoteCCId>    remote_ccid;
          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::nodeid::ClassType,
                                                lmp::obj::nodeid::ClassType::LocalNodeId>    local_node_id;
          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::nodeid::ClassType,
                                                lmp::obj::nodeid::ClassType::RemoteNodeId>   remote_node_id;
          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::msgid::ClassType,
                                                lmp::obj::msgid::ClassType::MessageIdAck>    message_id_ack;
          qi::rule<Iterator, ConfigAckBody(lmp::WORD)>                                    config_ack_body_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct config_ack_body_grammar : karma::grammar<OutputIterator, ConfigAckBody()>
        {
          config_ack_body_grammar();

          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::ccid::ClassType,
                                                   lmp::obj::ccid::ClassType::LocalCCId>       local_ccid;
          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::ccid::ClassType,
                                                   lmp::obj::ccid::ClassType::RemoteCCId>      remote_ccid;
          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::nodeid::ClassType,
                                                   lmp::obj::nodeid::ClassType::LocalNodeId>   local_node_id;
          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::nodeid::ClassType,
                                                   lmp::obj::nodeid::ClassType::RemoteNodeId>  remote_node_id;
          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::msgid::ClassType,
                                                   lmp::obj::msgid::ClassType::MessageIdAck>   message_id_ack;
          karma::rule<OutputIterator, ConfigAckBody()>                                         config_ack_body_rule;
        };
      }
    }
    template <>
    struct MessageTypeTraits<MsgType::ConfigAck>
    {
      typedef MsgType                     message_type;
      typedef config_ack::ConfigAckBody   data_type;
      typedef config_ack::IsEqualFtor     equal_ftor_type;
      typedef config_ack::GetLengthFtor   get_length_ftor_type;
      static const message_type           msg_type_value; // = MsgType::ConfigAck;
    };
    template <typename Iterator>
    struct MessageTypeParseTraits<Iterator, MsgType::ConfigAck>
    {
      typedef config_ack::parse::config_ack_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct MessageTypeGenerateTraits<OutputIterator, MsgType::ConfigAck>
    {
      typedef config_ack::generate::config_ack_body_grammar<OutputIterator>  grammar_type;
    };
    typedef MessageTypeData<MessageTypeTraits<MsgType::ConfigAck>>  ConfigAckMsg;
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGACK_HPP_ */
