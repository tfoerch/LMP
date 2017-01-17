#ifndef LMP_MSG_CONFIG_DEF_HPP_
#define LMP_MSG_CONFIG_DEF_HPP_
/*
 * Config_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Config.hpp"
#include "CommonHeader_def.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/karma_attr_cast.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


//BOOST_FUSION_ADAPT_STRUCT(
//  lmp::msg::ConfigMsg,
//  (lmp::BYTE,                               m_flags)
//  (lmp::obj::ccid::LocalCCIdData,           m_localCCId)
//  (lmp::obj::msgid::MessageIdData,          m_messageId)
//  (lmp::obj::nodeid::LocalNodeIdData,       m_localNodeId)
//  (lmp::obj::config::ConfigObjectSequence,  m_configObjects)
//)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::ConfigBody,
  (lmp::obj::ccid::LocalCCIdData,           m_localCCId)
  (lmp::obj::msgid::MessageIdData,          m_messageId)
  (lmp::obj::nodeid::LocalNodeIdData,       m_localNodeId)
  (lmp::obj::config::ConfigObjectSequence,  m_configObjects)
)


namespace lmp
{
  namespace msg
  {
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      config_body_grammar<Iterator>::config_body_grammar()
      : config_body_grammar<Iterator>::base_type(config_body_rule, "config_body")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_a;
        using qi::_1;
        using qi::attr;
        using phoenix::at_c;
        using namespace qi::labels;

        config_body_rule %=
            local_ccid
            >> message_id
            >> local_node_id
            >> config_object_sequence(_r1 -
                                      c_headerLength -
                                      phx_getCCIdLength(at_c<0>(_val)) -
                                      phx_getMessageIdLength(at_c<1>(_val)) -
                                      phx_getNodeIdLength(at_c<2>(_val)))
            ;

        config_body_rule.name("config_body");
      }

//      template <typename Iterator>
//      config_grammar<Iterator>::config_grammar()
//      : config_grammar<Iterator>::base_type(config_rule, "config")
//      {
//        using qi::byte_;
//        using qi::big_word;
//        using qi::_a;
//        using qi::_1;
//        using qi::attr;
//        using phoenix::at_c;
//        using namespace qi::labels;
//
//        config_rule %=
//            attr(at_c<0>(_r1))
//            >> local_ccid
//            >> message_id
//            >> local_node_id
//            >> config_object_sequence(at_c<2>(_r1) -
//                                      c_headerLength -
//                                      phx_getCCIdLength(at_c<1>(_val)) -
//                                      phx_getMessageIdLength(at_c<2>(_val)) -
//                                      phx_getNodeIdLength(at_c<3>(_val)))
//            ;
//
//        config_rule.name("config");
//      }
    } // namespace parse
    namespace generate
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      config_body_grammar<OutputIterator>::config_body_grammar()
      : config_body_grammar::base_type(config_body_rule, "config_body")
      {
        using phoenix::at_c;
        using qi::byte_;
        using qi::big_word;
        using qi::attr;
        using namespace qi::labels;

        config_body_rule %=
            local_ccid
            << message_id
            << local_node_id
            << config_object_sequence
            ;

        config_body_rule.name("config_body");
      }
//      template <typename OutputIterator>
//      config_grammar<OutputIterator>::config_grammar()
//      : config_grammar::base_type(config_rule, "config")
//      {
//        using phoenix::at_c;
//        using qi::byte_;
//        using qi::big_word;
//        using qi::attr;
//        using namespace qi::labels;
//
//        config_rule %=
//            common_header [ _1 = _val  ]
//            << local_ccid
//            << message_id
//            << local_node_id
//            << config_object_sequence
//            ;
//
//        common_header =
//            byte_       [ _1 = (c_supportedVersion << 4) ]  // version
//            << byte_    [ _1 = at_c<0>(_val) ]              // flags
//            << byte_    [ _1 = 0 ]                          // reserved
//            << byte_    [ _1 = static_cast<std::underlying_type<MsgType>::type>(MsgType::Config) ]              // msg type
//            << big_word [ _1 = phx_getLength(_val) ]        // length
//            << big_word [ _1 = 0 ]                          // reserved
//            ;
//
//        config_rule.name("config");
//      }
    } // namespace generate
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_DEF_HPP_ */
