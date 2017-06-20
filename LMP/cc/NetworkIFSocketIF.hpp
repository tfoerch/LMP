#ifndef LMP_CC_NETWORKIF_SOCKETIF_HPP_
#define LMP_CC_NETWORKIF_SOCKETIF_HPP_
/*
 * UDP_Msg_ReceiveIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"             // for DWORD

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/buffer.hpp>

namespace lmp
{
  namespace cc
  {
    class NetworkIFSocketIF
    {
    public:
      inline lmp::DWORD getLocalCCId() const
      { return do_getLocalCCId(); }
      inline void enable()
      { do_enable(); }
      inline void disable()
      { do_disable(); }
      inline void send(
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        boost::asio::mutable_buffers_1&        messageBuffer)
      { do_send(destination_endpoint, messageBuffer); }
      virtual ~NetworkIFSocketIF(){}
    private:
      virtual lmp::DWORD do_getLocalCCId() const = 0;
      virtual void do_enable() = 0;
      virtual void do_disable() = 0;
      virtual void do_send(
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        boost::asio::mutable_buffers_1&        messageBuffer) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_NETWORKIF_SOCKETIF_HPP_ */
