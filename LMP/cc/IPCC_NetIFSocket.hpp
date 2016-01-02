#ifndef LIBS_IPCC_NETIFSOCKET_HPP_
#define LIBS_IPCC_NETIFSOCKET_HPP_
/*
 * IPCC_NetIFSocket.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "ProtocolTypes.hpp"                  // for DWORD
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional/optional.hpp>        // for optional
#include <string>

namespace boost { namespace asio { class io_service; } }

namespace lmp
{
  namespace cc
  {
    class IpccMsgReceiveIF;

    class NetworkIFSocket
    {
    public:
      NetworkIFSocket(
    	boost::asio::io_service&  io_service,
        lmp::WORD                 port,
        const std::string&        ifName,
		IpccMsgReceiveIF&         ipccMsgHandler);
      ~NetworkIFSocket();
      void send(
        const char                             message[],
		lmp::WORD                              length,
		const boost::asio::ip::udp::endpoint&  destination_endpoint);
      typedef boost::optional<boost::asio::ip::address_v4> OptAddressV4;
      typedef boost::optional<boost::asio::ip::address_v6> OptAddressV6;
      typedef std::pair<OptAddressV4, OptAddressV6>        OptAddresses;
      static OptAddresses getIfAddress(
        const std::string&        ifName);
    private:
      void handle_received_msg(
    	const boost::system::error_code&  error,
        size_t                            bytes_recvd);
      void handle_send_msg(
    	const boost::system::error_code&  error,
		size_t                            bytes_sent);
      static const boost::asio::ip::address  c_multicast_address;
      boost::asio::ip::udp::endpoint         m_listen_endpoint;
      boost::asio::ip::udp::socket           m_socket;
      std::string                            m_ifName;
      boost::asio::ip::udp::endpoint         m_sender_endpoint;
      IpccMsgReceiveIF&                      m_ipccMsgHandler;
      enum { max_buffer_length = 4096 };
      char                                   m_buffer[max_buffer_length];
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_NETIFSOCKET_HPP_ */
