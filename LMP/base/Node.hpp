#ifndef LIBS_Node_HPP_
#define LIBS_Node_HPP_
/*
 * IPCC_Impl.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "ProtocolTypes.hpp"                  // for DWORD
#include <boost/asio/ip/address.hpp>

namespace lmp
{
  namespace node
  {
    class Node
    {
    public:
      Node(
        lmp::DWORD                       nodeId,
		const boost::asio::ip::address&  loopbackAddress);
      virtual ~Node();
      void enable();
      void disable();
      lmp::DWORD  getNodeId() const;
    private:
      lmp::DWORD                  m_nodeId;
      boost::asio::ip::address    m_loopbackAddress;
    };
  } // namespace node
} // namespace lmp

#endif /* LIBS_Node_HPP_ */
