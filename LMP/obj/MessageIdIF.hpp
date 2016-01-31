#ifndef LMP_OBJ_MESSAGE_ID_IF_HPP_
#define LMP_OBJ_MESSAGE_ID_IF_HPP_
/*
 * MessageIdIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdData.hpp"

namespace lmp
{
  namespace obj
  {
    class MessageIdIF
	{
	public:
      inline lmp::DWORD getMessageId() const { return do_getData().getMessageId(); }
      virtual ~MessageIdIF(){}
	private:
      virtual const MessageIdData& do_getData() const = 0;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_IF_HPP_ */
