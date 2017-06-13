#ifndef Server_NetworkIFInDestructionFtorIF_HPP_
#define Server_NetworkIFInDestructionFtorIF_HPP_
/*
 * Mgt_NetworkIFInDestructionFtorIF.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD

namespace lmp_node
{

  class NetworkIFInDestructionFtorIF
  {
  public:
    inline void operator()(
      lmp::DWORD                   localCCId)
    { do_process(localCCId); }
    virtual ~NetworkIFInDestructionFtorIF(){}
  private:
    virtual void do_process(
      lmp::DWORD                   localCCId) = 0;
  };

} // end namespace lmp_node

#endif /* Server_NetworkIFInDestructionFtorIF_HPP_ */
