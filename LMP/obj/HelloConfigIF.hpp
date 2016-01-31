#ifndef LMP_OBJ_HELLOCONFIGIF_HPP_
#define LMP_OBJ_HELLOCONFIGIF_HPP_
/*
 * HelloConfigIF.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigData.hpp"

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace obj
  {
    class HelloConfigIF
    {
    public:
      inline lmp::WORD getHelloIntv() const { return do_getData().getHelloIntv(); }
      inline lmp::WORD getHelloDeadIntv() const { return do_getData().getHelloDeadIntv(); }
      virtual ~HelloConfigIF(){}
    private:
      virtual const HelloConfigData& do_getData() const = 0;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIGIF_HPP_ */
