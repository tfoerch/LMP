#ifndef LMP_OBJ_REMOTE_CC_ID_HPP_
#define LMP_OBJ_REMOTE_CC_ID_HPP_
/*
 * RemoteCCId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/ControlChannelIdClass.hpp"

namespace lmp
{
  namespace obj
  {
    template <>
    struct ObjectClassTypeTraits<ccid::ClassType, ccid::ClassType::RemoteCCId>
    {
      typedef ccid::ClassType             ctype_type;
      static const ctype_type             ctype = ccid::ClassType::RemoteCCId;
      typedef ccid::ControlChannelIdBody  data_type;
    };
    template <typename Iterator>
    struct ObjectClassTypeParseTraits<Iterator, ccid::ClassType, ccid::ClassType::RemoteCCId>
    {
      typedef ccid::parse::control_channel_id_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct ObjectClassTypeGenerateTraits<OutputIterator, ccid::ClassType, ccid::ClassType::RemoteCCId>
	{
      typedef ccid::generate::control_channel_id_body_grammar<OutputIterator>  grammar_type;
	};
	namespace ccid
	{
	  typedef ObjectClassTypeData<ObjectClassTypeTraits<ccid::ClassType,
			                                            ccid::ClassType::RemoteCCId>>  RemoteCCIdData;
	  const lmp::DWORD remoteCCIdLength = c_objHeaderLength + 4;
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_CC_ID_HPP_ */
