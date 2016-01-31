#ifndef LMP_OBJ_HELLOIF_HPP_
#define LMP_OBJ_HELLOIF_HPP_
/*
 * HelloIF.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "obj/HelloData.hpp"

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace obj
  {
    class HelloIF
    {
    public:
      inline lmp::DWORD getTxSeqNum() const { return do_getData().getTxSeqNum(); }
      inline lmp::DWORD getRcvSeqNum() const { return do_getData().getRcvSeqNum(); }
      virtual ~HelloIF(){}
    private:
      virtual const HelloData& do_getData() const = 0;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOIF_HPP_ */
