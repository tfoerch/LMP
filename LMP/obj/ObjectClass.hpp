#ifndef LMP_OBJ_OBJECTCLASS_HPP_
#define LMP_OBJ_OBJECTCLASS_HPP_
/*
 * ObjectClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

namespace lmp
{
  namespace obj
  {
    namespace otype
    {
      enum ObjectClass
	  {
    	ControlChannelID = 1,
		NodeID,
		LinkID,
		InterfaceID,
		MessageID,
		Config,
		Hello
	  };
    } // namespace otype
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_HPP_ */
