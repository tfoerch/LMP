/*
 * Config.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Config.hpp"

namespace lmp
{
  namespace msg
  {
    Config::Config(
      lmp::DWORD                    localNodeId,
	  lmp::DWORD                    localCCId,
	  const lmp::obj::HelloConfig&  helloConfig)
    : theLocalNodeId(localNodeId),
	  theLocalCCId(localCCId),
	  theHelloConfig(helloConfig)
    {}
  } // namespace msg
} // namespace lmp
