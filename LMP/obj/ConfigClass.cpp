/*
 * ConfigClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigClass.hpp"

namespace lmp
{
  namespace obj
  {
	namespace config
	{
	  std::ostream& operator<<(
	    std::ostream&     os,
		const ClassType&  cType)
	  {
		switch(cType)
		{
		  case ClassType::HelloConfig:
			os << "HelloConfig";
			break;
		}
		return os;
	  }
	}
  } // namespace obj
} // namespace lmp

