#ifndef LMP_MSG_CONFIGNACK_HPP_
#define LMP_MSG_CONFIGNACK_HPP_
/*
 * ConfigNack.hpp
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
#include "obj/HelloConfig.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace config_nack
    {
      struct ConfigNackBody
      {
        lmp::obj::ccid::LocalCCIdData       m_localCCId;
        lmp::obj::nodeid::LocalNodeIdData   m_localNodeId;
        lmp::obj::ccid::RemoteCCIdData      m_remoteCCId;
        lmp::obj::msgid::MessageIdAckData   m_messageId;
        lmp::obj::nodeid::RemoteNodeIdData  m_remoteNodeId;
        lmp::obj::config::HelloConfigData   m_helloConfig;
      };
      std::ostream& operator<<(
        std::ostream&          os,
        const ConfigNackBody&  configNackBody);
      struct IsEqualFtor
      {
        bool operator()(
          const ConfigNackBody&  first,
          const ConfigNackBody&  second) const;
      };
      struct GetLengthFtor
      {
        lmp::WORD operator()(
          const ConfigNackBody&  configNackBody) const;
      };
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct config_nack_body_grammar : qi::grammar<Iterator, ConfigNackBody(lmp::WORD)>
        {
          config_nack_body_grammar();

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
          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::config::ClassType,
                                                lmp::obj::config::ClassType::HelloConfig>    hello_config;
          qi::rule<Iterator, ConfigNackBody(lmp::WORD)>                                    config_nack_body_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct config_nack_body_grammar : karma::grammar<OutputIterator, ConfigNackBody()>
        {
          config_nack_body_grammar();

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
          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::config::ClassType,
                                                   lmp::obj::config::ClassType::HelloConfig>   hello_config;
          karma::rule<OutputIterator, ConfigNackBody()>                                        config_nack_body_rule;
        };
      }
    }
    template <>
    struct MessageTypeTraits<MsgType::ConfigNack>
    {
      typedef MsgType                      message_type;
      typedef config_nack::ConfigNackBody  data_type;
      typedef config_nack::IsEqualFtor     equal_ftor_type;
      typedef config_nack::GetLengthFtor   get_length_ftor_type;
      static const message_type            msg_type_value; // = MsgType::ConfigNack;
    };
    template <typename Iterator>
    struct MessageTypeParseTraits<Iterator, MsgType::ConfigNack>
    {
      typedef config_nack::parse::config_nack_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct MessageTypeGenerateTraits<OutputIterator, MsgType::ConfigNack>
    {
      typedef config_nack::generate::config_nack_body_grammar<OutputIterator>  grammar_type;
    };
    typedef MessageTypeData<MessageTypeTraits<MsgType::ConfigNack>>  ConfigNackMsg;
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGNACK_HPP_ */
