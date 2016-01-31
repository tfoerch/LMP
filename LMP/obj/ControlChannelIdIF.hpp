#ifndef LMP_OBJ_CONTROL_CHANNEL_ID_IF_HPP_
#define LMP_OBJ_CONTROL_CHANNEL_ID_IF_HPP_
/*
 * ControlChannelIdIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdData.hpp"

namespace lmp
{
  namespace obj
  {
    class ControlChannelIdIF
	{
	public:
      inline lmp::DWORD getControlChannelId() const { return do_getData().getControlChannelId(); }
      virtual ~ControlChannelIdIF(){}
	private:
      virtual const ControlChannelIdData& do_getData() const = 0;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONTROL_CHANNEL_ID_IF_HPP_ */
