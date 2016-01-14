#ifndef LMP_MSG_CONFIG_HPP_
#define LMP_MSG_CONFIG_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>                  // for DWORD
#include <HelloConfig.hpp>

namespace lmp
{
  namespace msg
  {
    class Config
	{
	public:
      Config(
        lmp::DWORD                    localNodeId,
		lmp::DWORD                    localCCId,
		const lmp::obj::HelloConfig&  helloConfig);
	  lmp::DWORD             theLocalNodeId;
	  lmp::DWORD             theLocalCCId;
	  lmp::obj::HelloConfig  theHelloConfig;
	};
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_HPP_ */
