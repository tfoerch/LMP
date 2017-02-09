#ifndef LIBS_IPCC_NETIFSOCKET_HPP_
#define LIBS_IPCC_NETIFSOCKET_HPP_
/*
 * IPCC_NetIFSocket.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "NetworkIFSocketIF.hpp"

#include "base/ProtocolTypes.hpp"             // for DWORD
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional/optional.hpp>        // for optional
#include <string>

namespace boost { namespace asio { class io_service; } }

namespace lmp
{
  namespace cc
  {
    class UDPMsgReceiveIF;

    class NetworkIFSocket : public NetworkIFSocketIF
    {
    public:
      NetworkIFSocket(
    	boost::asio::io_service&          io_service,
    	lmp::DWORD                        localCCId,
        const std::string&                ifName,
        lmp::WORD                         port,
        UDPMsgReceiveIF&                  udpMsgHandler); // bind socket to interface device
      NetworkIFSocket(
    	boost::asio::io_service&          io_service,
    	lmp::DWORD                        localCCId,
    	boost::asio::ip::udp::endpoint&   listen_endpoint,
    	UDPMsgReceiveIF&                  udpMsgHandler); // bind socket to local listen_endpoint
      virtual ~NetworkIFSocket();
      typedef boost::optional<boost::asio::ip::address_v4> OptAddressV4;
      typedef boost::optional<boost::asio::ip::address_v6> OptAddressV6;
      typedef std::pair<OptAddressV4, OptAddressV6>        OptAddresses;
      static OptAddresses getIfAddress(
        const std::string&                ifName);
    private:
      NetworkIFSocket(
        NetworkIFSocket&&  other) = default;
      // implement NetworkIFSocketIF
      virtual lmp::DWORD do_getLocalCCId() const;
      virtual void do_send(
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        boost::asio::mutable_buffers_1&        messageBuffer);
      void handle_received_msg(
    	const boost::system::error_code&  error,
        size_t                            bytes_recvd);
      void handle_send_msg(
    	const boost::system::error_code&  error,
    	size_t                            bytes_sent);
      lmp::DWORD                             m_localCCId;
      UDPMsgReceiveIF&                       m_udpMsgHandler;
      boost::asio::ip::udp::endpoint         m_listen_endpoint;
      boost::asio::ip::udp::socket           m_socket;
      boost::asio::ip::udp::endpoint         m_sender_endpoint;
      enum { max_buffer_length = 4096 };
      char                                   m_buffer[max_buffer_length];
      static const boost::asio::ip::address  c_multicast_address;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_NETIFSOCKET_HPP_ */
