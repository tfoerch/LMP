/*
 * ControlChannelIdCTypes.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypes_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::ccid::parse::control_channel_id_ctypes_grammar<BufIterType>;

namespace
{
  struct ControlChannelIdCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    ControlChannelIdCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::ccid::LocalCCIdData& localCCId) const
    {
      m_os << localCCId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::ccid::RemoteCCIdData& remoteCCId) const
    {
      m_os << remoteCCId;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::ccid::UnknownCCIdCTypeData& unknownCCId) const
    {
      m_os << unknownCCId;
      return m_os;
    }
    std::ostream&   m_os;
  };
}

std::ostream& lmp::obj::ccid::operator<<(
  std::ostream&                                  os,
  const lmp::obj::ccid::ControlChannelIdCTypes&  controlChannelIdCTypes)
{
  boost::apply_visitor(ControlChannelIdCTypes_Printer(os), controlChannelIdCTypes);
  return os;
}
