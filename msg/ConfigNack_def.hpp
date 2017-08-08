#ifndef LMP_MSG_CONFIGNACK_DEF_HPP_
#define LMP_MSG_CONFIGNACK_DEF_HPP_
/*
 * ConfigNack_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigNack.hpp"
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

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::config_nack::ConfigNackBody,
  (lmp::obj::ccid::LocalCCIdData,       m_localCCId)
  (lmp::obj::nodeid::LocalNodeIdData,   m_localNodeId)
  (lmp::obj::ccid::RemoteCCIdData,      m_remoteCCId)
  (lmp::obj::msgid::MessageIdAckData,   m_messageId)
  (lmp::obj::nodeid::RemoteNodeIdData,  m_remoteNodeId)
  (lmp::obj::config::HelloConfigData,   m_helloConfig)
)

namespace lmp
{
  namespace msg
  {
    namespace config_nack
    {
      namespace parse
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        config_nack_body_grammar<Iterator>::config_nack_body_grammar()
        : config_nack_body_grammar<Iterator>::base_type(config_nack_body_rule, "config_nack_body")
        {
          using qi::byte_;
          using qi::big_word;
          using qi::_a;
          using qi::_1;
          using qi::attr;
          using phoenix::at_c;
          using namespace qi::labels;

          config_nack_body_rule %=
              local_ccid
              >> local_node_id
              >> remote_ccid
              >> message_id_ack
              >> remote_node_id
              >> hello_config
              ;

          config_nack_body_rule.name("config_nack_body");
        }
      } // namespace parse
      namespace generate
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        config_nack_body_grammar<OutputIterator>::config_nack_body_grammar()
        : config_nack_body_grammar::base_type(config_nack_body_rule, "config_nack_body")
        {
          using phoenix::at_c;
          using qi::byte_;
          using qi::big_word;
          using qi::attr;
          using namespace qi::labels;

          config_nack_body_rule %=
              local_ccid
              << local_node_id
              << remote_ccid
              << message_id_ack
              << remote_node_id
              << hello_config
              ;

          config_nack_body_rule.name("config_nack_body");
        }
      } // namespace generate
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGNACK_DEF_HPP_ */
