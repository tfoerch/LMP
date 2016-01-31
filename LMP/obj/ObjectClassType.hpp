#ifndef LMP_OBJ_OBJECT_CLASS_TYPE_HPP_
#define LMP_OBJ_OBJECT_CLASS_TYPE_HPP_
/*
 * ObjectClassTypeTraits.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/ObjectClassIF.hpp"
#include "obj/ObjectClassTypeTraits.hpp"

namespace lmp
{
  namespace obj
  {
    template <typename   ClassType,
	          ClassType  ctype>
    class ObjectClassType : public ObjectClassIF<ClassType>,
                            public ObjectClassCTypeTraits<ClassType, ctype>::object_ctype_if_type
	{
	public:
      typedef ObjectClassCTypeTraits<ClassType, ctype>         obj_class_ctype_traits_type;
      typedef typename obj_class_ctype_traits_type::data_type  data_type;
      ObjectClassType(
    	const data_type& data)
      : m_data(data)
      {}
      virtual ~ObjectClassType(){}
    private:
      virtual const data_type& do_getData() const { return m_data; }
      virtual ClassType do_getClassType() const { return ctype; }
      virtual lmp::WORD do_getContentsLength() const { return m_data.getContentsLength(); }
      virtual ObjectHeader::OptEncError do_encodeContents(
    	boost::asio::mutable_buffer&  buffer) const { return m_data.encode(buffer); }
      data_type m_data;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECT_CLASS_TYPE_HPP_ */
