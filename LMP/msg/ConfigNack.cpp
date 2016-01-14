/*
 * ConfigNack.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigNack.hpp"

namespace lmp
{
  namespace msg
  {
    ConfigNack::ConfigNack(
      lmp::DWORD                    localNodeId,
	  lmp::DWORD                    localCCId,
	  const lmp::obj::HelloConfig&  helloConfig)
    : theLocalNodeId(localNodeId),
	  theLocalCCId(localCCId),
	  theHelloConfig(helloConfig)
    {}
  } // namespace msg
} // namespace lmp
