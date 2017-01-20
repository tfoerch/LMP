#ifndef LMP_MSG_CONFIG_DEF_HPP_
#define LMP_MSG_CONFIG_DEF_HPP_
/*
 * Config_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Config.hpp"
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
  lmp::msg::config::ConfigBody,
  (lmp::obj::ccid::LocalCCIdData,           m_localCCId)
  (lmp::obj::msgid::MessageIdData,          m_messageId)
  (lmp::obj::nodeid::LocalNodeIdData,       m_localNodeId)
  (lmp::obj::config::ConfigObjectSequence,  m_configObjects)
)


namespace lmp
{
  namespace msg
  {
    namespace config
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
      } // namespace generate
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_DEF_HPP_ */
