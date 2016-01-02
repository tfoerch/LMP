/*
 * IPCC_NetIFSocket.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "IPCC_NetIFSocket.hpp"
#include <boost/asio/ip/multicast.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>
#include <array>
#include <iostream>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <linux/if_link.h>

namespace lmp
{
  namespace cc
  {
    const boost::asio::ip::address  NetworkIFSocket::c_multicast_address = boost::asio::ip::address::from_string("224.0.0.1");;

    NetworkIFSocket::NetworkIFSocket(
      boost::asio::io_service&  io_service,
	  lmp::WORD                 port,
	  const std::string&        ifName,
	  IpccMsgReceiveIF&         ipccMsgHandler)
      : m_listen_endpoint(c_multicast_address, port),
        m_socket(io_service, m_listen_endpoint),
		m_ifName(ifName),
		m_sender_endpoint(),
		m_ipccMsgHandler(ipccMsgHandler)
    {
    	OptAddresses optAddr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
    	boost::asio::ip::address if_address =
    	  ( optAddr.first ?
    		*optAddr.first :
			( optAddr.second ?
			  *optAddr.second :
              boost::asio::ip::address::from_string("127.0.0.1") ) );
      // SO_BINDTODEVICE
      if ((::setsockopt(m_socket.native(), SOL_SOCKET, SO_BINDTODEVICE,
    	  ifName.c_str(), ifName.size() + 1) == -1))
      {
    	throw std::runtime_error("setsockopt() SO_BINDTODEVICE");
      }

      // bind
      m_socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));

      //m_socket.bind(listen_endpoint);

      // disable loopback (no copies of our packets)
      m_socket.set_option(boost::asio::ip::multicast::enable_loopback(false));

      // set oif - the socket will use this interface as outgoing interface
      m_socket.set_option(boost::asio::ip::multicast::outbound_interface(if_address.to_v4()));

      // set mcast group - join group
      m_socket.set_option(boost::asio::ip::multicast::join_group(c_multicast_address.to_v4(),
    					   	   	   	   	   	   	   	   	         if_address.to_v4()));
      m_socket.async_receive_from(boost::asio::buffer(m_buffer, max_buffer_length),
    		                      m_sender_endpoint,
								  boost::bind(&NetworkIFSocket::handle_received_msg,
										      this,
											  boost::asio::placeholders::error,
											  boost::asio::placeholders::bytes_transferred));
    }
    NetworkIFSocket::~NetworkIFSocket()
    {
    }
    void NetworkIFSocket::send(
      const char                             message[],
	  lmp::WORD                              length,
	  const boost::asio::ip::udp::endpoint&  destination_endpoint)
    {
      m_socket.async_send_to(boost::asio::buffer(message, length),
    			             destination_endpoint,
							 boost::bind(&NetworkIFSocket::handle_send_msg,
							             this,
										 boost::asio::placeholders::error,
										 boost::asio::placeholders::bytes_transferred));
    }
    NetworkIFSocket::OptAddresses NetworkIFSocket::getIfAddress(
      const std::string&        ifName)
    {
      OptAddresses result;
      struct ifaddrs *myaddrs;
      if(getifaddrs(&myaddrs) != 0)
      {
        perror("getifaddrs");
      }
      else
      {
    	for (struct ifaddrs* ifa = myaddrs;
    		 ifa != 0 &&
    		 ( !result.first || !result.second);
    		 ifa = ifa->ifa_next)
    	{
    	  // std::cout << ifa->ifa_name << std::endl;
    	  if (ifName.compare(ifa->ifa_name) == 0 &&
    		  ifa->ifa_addr &&
			  (ifa->ifa_flags & IFF_UP))
          {
            // std::cout << ifa->ifa_name << " found" << std::endl;
            switch (ifa->ifa_addr->sa_family)
            {
              case AF_INET:
                {
                  // std::cout << ifa->ifa_name << " has IP V4" << std::endl;
                  struct sockaddr_in* s4 = reinterpret_cast<struct sockaddr_in*>(ifa->ifa_addr);
                  result.first = boost::asio::ip::address_v4(ntohl(s4->sin_addr.s_addr));
                }
                break;
              case AF_PACKET:
                {
                  // std::cout << ifa->ifa_name << " has AF_PACKET" << std::endl;
//    		      if (ifa->ifa_data)
//    		      {
//    		        struct rtnl_link_stats* linkStat =
//       		    reinterpret_cast<struct rtnl_link_stats*>(ifa->ifa_data);
//      	      }
                }
                break;
              case AF_INET6:
                {
                  // std::cout << ifa->ifa_name << " has IP V6" << std::endl;
                  struct sockaddr_in6 *s6 = reinterpret_cast<struct sockaddr_in6*>(ifa->ifa_addr);
                  struct in6_addr& v6addr = s6->sin6_addr;
                  const std::array<unsigned char, 16ul> ipv6 =
                    { v6addr.__in6_u.__u6_addr8[0], v6addr.__in6_u.__u6_addr8[1],
                      v6addr.__in6_u.__u6_addr8[2], v6addr.__in6_u.__u6_addr8[3],
					  v6addr.__in6_u.__u6_addr8[4], v6addr.__in6_u.__u6_addr8[5],
					  v6addr.__in6_u.__u6_addr8[6], v6addr.__in6_u.__u6_addr8[7],
					  v6addr.__in6_u.__u6_addr8[8], v6addr.__in6_u.__u6_addr8[9],
					  v6addr.__in6_u.__u6_addr8[10], v6addr.__in6_u.__u6_addr8[11],
					  v6addr.__in6_u.__u6_addr8[12], v6addr.__in6_u.__u6_addr8[13],
					  v6addr.__in6_u.__u6_addr8[14], v6addr.__in6_u.__u6_addr8[15] };
                  result.second = boost::asio::ip::address_v6(ipv6, s6->sin6_scope_id);
                }
                break;
              default:
                {
                  // std::cout << ifa->ifa_name << " has address family " << ifa->ifa_addr->sa_family << std::endl;
                }
                break;
            }
          }
    	}
        freeifaddrs(myaddrs);
      }
      return result;
    }
    void NetworkIFSocket::handle_received_msg(
      const boost::system::error_code&  error,
      size_t                            bytes_recvd)
    {
    }
    void NetworkIFSocket::handle_send_msg(
  	  const boost::system::error_code&  error,
	  size_t                            bytes_sent)
    {
    }
  } // namespace cc
} // namespace lmp
