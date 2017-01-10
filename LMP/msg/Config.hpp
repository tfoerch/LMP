#ifndef LMP_MSG_CONFIG_HPP_
#define LMP_MSG_CONFIG_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/LMPMessageIF.hpp"
#include "obj/LocalCCId.hpp"
#include "obj/MessageId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/ConfigObjectSequence.hpp"
#include "CommonHeader.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    struct ConfigMsg
    {
      lmp::BYTE                               m_flags;
      lmp::obj::ccid::LocalCCIdData           m_localCCId;
      lmp::obj::msgid::MessageIdData          m_messageId;
      lmp::obj::nodeid::LocalNodeIdData       m_localNodeId;
      lmp::obj::config::ConfigObjectSequence  m_configObjects;
    };
    std::ostream& operator<<(
      std::ostream&         os,
      const ConfigMsg&      config);
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct config_grammar : qi::grammar<Iterator, ConfigMsg(CommonHeaderOutput)>
      {
    	config_grammar();

        boost::phoenix::function<lmp::obj::GetLength<lmp::obj::ObjectClassTypeTraits<lmp::obj::ccid::ClassType,
                                                                                     lmp::obj::ccid::ClassType::LocalCCId>>>  phx_getCCIdLength;
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
    	qi::rule<Iterator, ConfigMsg(CommonHeaderOutput)>                                config_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_HPP_ */
