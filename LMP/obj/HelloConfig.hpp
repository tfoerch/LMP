#ifndef LMP_OBJ_HELLOCONFIG_HPP_
#define LMP_OBJ_HELLOCONFIG_HPP_
/*
 * HelloConfig.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>                  // for WORD

namespace lmp
{
  namespace obj
  {
    class HelloConfig
	{
	public:
      HelloConfig(
    	lmp::WORD  helloIntv,
		lmp::WORD  helloDeadIntv);
  	  lmp::WORD  theHelloIntv;
      lmp::WORD  theHelloDeadIntv;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
