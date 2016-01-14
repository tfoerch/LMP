/*
 * HelloConfig.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "HelloConfig.hpp"

namespace lmp
{
  namespace obj
  {
    HelloConfig::HelloConfig(
      lmp::WORD  helloIntv,
	  lmp::WORD  helloDeadIntv)
    : theHelloIntv(helloIntv),
	  theHelloDeadIntv(helloDeadIntv)
    {}
  } // namespace obj
} // namespace lmp
