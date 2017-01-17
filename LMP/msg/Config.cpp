/*
 * Config.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Config_def.hpp"
#include "MessageType_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

const lmp::msg::MsgType lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Config>::msg_type_value = lmp::msg::MsgType::Config;
typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::config_body_grammar<BufIterType>;
template struct lmp::msg::parse::message_type_grammar<BufIterType, lmp::msg::MsgType::Config>;
//template struct lmp::msg::parse::config_grammar<BufIterType>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::msg::generate::config_body_grammar<BufOutIterType>;
template struct lmp::msg::generate::message_type_grammar<BufOutIterType, lmp::msg::MsgType::Config>;
//template struct lmp::msg::generate::config_grammar<BufOutIterType>;
template std::ostream& lmp::msg::operator<< <lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Config>>(
  std::ostream&,
  const lmp::msg::MessageTypeData<lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Config>>&);
template bool lmp::msg::operator== <lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Config>>(
  const lmp::msg::MessageTypeData<lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Config>>&,
  const lmp::msg::MessageTypeData<lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Config>>&);

namespace lmp
{
  namespace msg
  {
    lmp::WORD GetLengthFtor::operator()(
      const ConfigBody&  configBody) const
    {
      return
        ( lmp::obj::getLength(configBody.m_localCCId) +
          lmp::obj::getLength(configBody.m_messageId) +
          lmp::obj::getLength(configBody.m_localNodeId) +
          lmp::obj::config::getLength(configBody.m_configObjects) );
    }
    bool IsEqualFtor::operator()(
      const ConfigBody&  first,
      const ConfigBody&  second) const
    {
      return
        ( first.m_localCCId == second.m_localCCId &&
          first.m_messageId == second.m_messageId &&
          first.m_localNodeId == second.m_localNodeId &&
          first.m_configObjects == second.m_configObjects );
    }
    std::ostream& operator<<(
      std::ostream&      os,
      const ConfigBody&  configBody)
    {
      std::cout << configBody.m_localCCId
		<< ", " << configBody.m_messageId
		<< ", " << configBody.m_localNodeId
		<< ", " << configBody.m_configObjects;
      return os;
    }
  } // namespace msg
} // namespace lmp
