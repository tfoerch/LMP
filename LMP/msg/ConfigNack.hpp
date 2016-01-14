#ifndef LMP_MSG_CONFIGNACK_HPP_
#define LMP_MSG_CONFIGNACK_HPP_
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
    class ConfigNack
	{
	public:
      ConfigNack(
        lmp::DWORD                    localNodeId,
		lmp::DWORD                    localCCId,
		const lmp::obj::HelloConfig&  helloConfig);
	  lmp::DWORD             theLocalNodeId;
	  lmp::DWORD             theLocalCCId;
	  lmp::obj::HelloConfig  theHelloConfig;
	};
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGNACK_HPP_ */
