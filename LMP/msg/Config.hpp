#ifndef LMP_MSG_CONFIG_HPP_
#define LMP_MSG_CONFIG_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCId.hpp"
#include "obj/MessageId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/ConfigObjectSequence.hpp"
#include "CommonHeader.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
//    struct ConfigMsg
//    {
//      lmp::BYTE                               m_flags;
//      lmp::obj::ccid::LocalCCIdData           m_localCCId;
//      lmp::obj::msgid::MessageIdData          m_messageId;
//      lmp::obj::nodeid::LocalNodeIdData       m_localNodeId;
//      lmp::obj::config::ConfigObjectSequence  m_configObjects;
//    };
//    std::ostream& operator<<(
//      std::ostream&     os,
//      const ConfigMsg&  config);
//    bool operator==(
//      const ConfigMsg&  first,
//      const ConfigMsg&  second);
//    lmp::DWORD getLength(
//      const ConfigMsg&  config);
//    struct GetConfigLength
//    {
//      template<typename> struct result { typedef lmp::DWORD type; };
//      template<typename ConfigMsg>
//      lmp::DWORD operator()(
//        const ConfigMsg& config) const
//      { return lmp::msg::getLength(config); }
//    };
    struct ConfigBody
    {
      lmp::obj::ccid::LocalCCIdData           m_localCCId;
      lmp::obj::msgid::MessageIdData          m_messageId;
      lmp::obj::nodeid::LocalNodeIdData       m_localNodeId;
      lmp::obj::config::ConfigObjectSequence  m_configObjects;
    };
    std::ostream& operator<<(
      std::ostream&      os,
      const ConfigBody&  configBody);
    struct IsEqualFtor
    {
      bool operator()(
        const ConfigBody& first,
        const ConfigBody& second) const;
    };
    struct GetLengthFtor
    {
      lmp::WORD operator()(
        const ConfigBody&  configBody) const;
    };
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct config_body_grammar : qi::grammar<Iterator, ConfigBody(lmp::WORD)>
      {
        config_body_grammar();

        boost::phoenix::function<lmp::obj::GetLength<lmp::obj::ObjectClassTypeTraits<lmp::obj::ccid::ClassType,
                                                                                     lmp::obj::ccid::ClassType::LocalCCId>>>      phx_getCCIdLength;
        boost::phoenix::function<lmp::obj::GetLength<lmp::obj::ObjectClassTypeTraits<lmp::obj::nodeid::ClassType,
                                                                                     lmp::obj::nodeid::ClassType::LocalNodeId>>>  phx_getNodeIdLength;
        boost::phoenix::function<lmp::obj::GetLength<lmp::obj::ObjectClassTypeTraits<lmp::obj::msgid::ClassType,
                                                                                     lmp::obj::msgid::ClassType::MessageId>>>     phx_getMessageIdLength;
        lmp::obj::parse::object_class_grammar<Iterator,
                                              lmp::obj::ccid::ClassType,
                                              lmp::obj::ccid::ClassType::LocalCCId>      local_ccid;
        lmp::obj::parse::object_class_grammar<Iterator,
                                              lmp::obj::nodeid::ClassType,
                                              lmp::obj::nodeid::ClassType::LocalNodeId>  local_node_id;
        lmp::obj::parse::object_class_grammar<Iterator,
                                              lmp::obj::msgid::ClassType,
                                              lmp::obj::msgid::ClassType::MessageId>     message_id;
        lmp::obj::config::parse::config_object_sequence_grammar<Iterator>                config_object_sequence;
        qi::rule<Iterator, ConfigBody(lmp::WORD)>                                        config_body_rule;
      };
//      template <typename Iterator>
//      struct config_grammar : qi::grammar<Iterator, ConfigMsg(CommonHeader)>
//      {
//    	config_grammar();
//
//        boost::phoenix::function<lmp::obj::GetLength<lmp::obj::ObjectClassTypeTraits<lmp::obj::ccid::ClassType,
//                                                                                     lmp::obj::ccid::ClassType::LocalCCId>>>      phx_getCCIdLength;
//        boost::phoenix::function<lmp::obj::GetLength<lmp::obj::ObjectClassTypeTraits<lmp::obj::nodeid::ClassType,
//                                                                                     lmp::obj::nodeid::ClassType::LocalNodeId>>>  phx_getNodeIdLength;
//        boost::phoenix::function<lmp::obj::GetLength<lmp::obj::ObjectClassTypeTraits<lmp::obj::msgid::ClassType,
//                                                                                     lmp::obj::msgid::ClassType::MessageId>>>     phx_getMessageIdLength;
//        lmp::obj::parse::object_class_grammar<Iterator,
//                                              lmp::obj::ccid::ClassType,
//                                              lmp::obj::ccid::ClassType::LocalCCId>      local_ccid;
//        lmp::obj::parse::object_class_grammar<Iterator,
//                                              lmp::obj::nodeid::ClassType,
//                                              lmp::obj::nodeid::ClassType::LocalNodeId>  local_node_id;
//        lmp::obj::parse::object_class_grammar<Iterator,
//                                              lmp::obj::msgid::ClassType,
//                                              lmp::obj::msgid::ClassType::MessageId>     message_id;
//        lmp::obj::config::parse::config_object_sequence_grammar<Iterator>                config_object_sequence;
//    	qi::rule<Iterator, ConfigMsg(CommonHeader)>                                      config_rule;
//      };
    }
    namespace generate
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct config_body_grammar : karma::grammar<OutputIterator, ConfigBody()>
      {
        config_body_grammar();

        lmp::obj::generate::object_class_grammar<OutputIterator,
                                                 lmp::obj::ccid::ClassType,
                                                 lmp::obj::ccid::ClassType::LocalCCId>      local_ccid;
        lmp::obj::generate::object_class_grammar<OutputIterator,
                                                 lmp::obj::nodeid::ClassType,
                                                 lmp::obj::nodeid::ClassType::LocalNodeId>  local_node_id;
        lmp::obj::generate::object_class_grammar<OutputIterator,
                                                 lmp::obj::msgid::ClassType,
                                                 lmp::obj::msgid::ClassType::MessageId>     message_id;
        lmp::obj::config::generate::config_object_sequence_grammar<OutputIterator>          config_object_sequence;
        karma::rule<OutputIterator, ConfigBody()>                                           config_body_rule;
      };
//      template <typename OutputIterator>
//      struct config_grammar : karma::grammar<OutputIterator, ConfigMsg()>
//      {
//        config_grammar();
//
//        boost::phoenix::function<lmp::msg::GetConfigLength>                                 phx_getLength;
//        lmp::obj::generate::object_class_grammar<OutputIterator,
//                                                 lmp::obj::ccid::ClassType,
//                                                 lmp::obj::ccid::ClassType::LocalCCId>      local_ccid;
//        lmp::obj::generate::object_class_grammar<OutputIterator,
//                                                 lmp::obj::nodeid::ClassType,
//                                                 lmp::obj::nodeid::ClassType::LocalNodeId>  local_node_id;
//        lmp::obj::generate::object_class_grammar<OutputIterator,
//                                                 lmp::obj::msgid::ClassType,
//                                                 lmp::obj::msgid::ClassType::MessageId>     message_id;
//        lmp::obj::config::generate::config_object_sequence_grammar<OutputIterator>          config_object_sequence;
//        karma::rule<OutputIterator, ConfigMsg&()>                                           common_header;
//        karma::rule<OutputIterator, ConfigMsg()>                                            config_rule;
//      };
    }
    template <>
    struct MessageTypeTraits<MsgType::Config>
    {
      typedef MsgType            message_type;
      typedef ConfigBody         data_type;
      typedef IsEqualFtor        equal_ftor_type;
      typedef GetLengthFtor      get_length_ftor_type;
      static const message_type  msg_type_value; // = MsgType::Config;
    };
    template <typename Iterator>
    struct MessageTypeParseTraits<Iterator, MsgType::Config>
    {
      typedef parse::config_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct MessageTypeGenerateTraits<OutputIterator, MsgType::Config>
    {
      typedef generate::config_body_grammar<OutputIterator>  grammar_type;
    };
    typedef MessageTypeData<MessageTypeTraits<MsgType::Config>>  ConfigMsg;
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_HPP_ */
