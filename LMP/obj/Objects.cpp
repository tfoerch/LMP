/*
 * Objects.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/Objects_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::objects_grammar<BufIterType>;

namespace
{
  struct Objects_Printer : boost::static_visitor<std::ostream&>
  {
    Objects_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::ccid::ControlChannelIdCTypes& controlChannelId) const
    {
      m_os << controlChannelId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::msgid::MessageIdCTypes& messageId) const
    {
      m_os << messageId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::nodeid::NodeIdCTypes& nodeId) const
    {
      m_os << nodeId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::config::ConfigCTypes& config) const
    {
      m_os << config;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::hello::HelloCTypes& hello) const
    {
      m_os << hello;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::UnknownObjectClassData& unknownObject) const
    {
      m_os << unknownObject;
      return m_os;
    }
    std::ostream&   m_os;
  };
}

std::ostream& lmp::obj::operator<<(
  std::ostream&             os,
  const lmp::obj::Objects&  objects)
{
  boost::apply_visitor(Objects_Printer(os), objects);
  return os;
}
