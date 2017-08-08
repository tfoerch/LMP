/*
 * HelloClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloClass.hpp"

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      std::ostream& operator<<(
          std::ostream&     os,
          const ClassType&  cType)
      {
        switch(cType)
        {
          case ClassType::Hello:
            os << "Hello";
            break;
        }
        return os;
      }
    }
  } // namespace obj
} // namespace lmp

