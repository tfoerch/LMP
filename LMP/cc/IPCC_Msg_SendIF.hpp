#ifndef LMP_CC_MSG_SENDIF_HPP_
#define LMP_CC_MSG_SENDIF_HPP_
/*
 * IPCC_Msg_SendIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/Message.hpp"

#include <boost/asio/ip/udp.hpp>

namespace lmp
{
  namespace cc
  {
    class IpccMsgSendIF
    {
    public:
      inline void sendMessage(
        lmp::DWORD                             localCCId,
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        const msg::Message&                    message)
      { do_sendMessage(localCCId, destination_endpoint, message); }
      virtual ~IpccMsgSendIF(){}
    private:
      virtual void do_sendMessage(
        lmp::DWORD                             localCCId,
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        const msg::Message&                    message) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_MSG_SENDIF_HPP_ */
