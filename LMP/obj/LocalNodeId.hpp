#ifndef LMP_OBJ_LOCAL_NODE_ID_HPP_
#define LMP_OBJ_LOCAL_NODE_ID_HPP_
/*
 * LocalNodeId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/NodeIdClass.hpp"

namespace lmp
{
  namespace obj
  {
    template <>
    struct ObjectClassTypeTraits<nodeid::ClassType, nodeid::ClassType::LocalNodeId>
    {
      typedef nodeid::ClassType   ctype_type;
      static const ctype_type     ctype = nodeid::ClassType::LocalNodeId;
      typedef nodeid::NodeIdBody  data_type;
    };
    template <typename Iterator>
    struct ObjectClassTypeParseTraits<Iterator, nodeid::ClassType, nodeid::ClassType::LocalNodeId>
    {
      typedef nodeid::parse::node_id_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct ObjectClassTypeGenerateTraits<OutputIterator, nodeid::ClassType, nodeid::ClassType::LocalNodeId>
	{
      typedef nodeid::generate::node_id_body_grammar<OutputIterator>  grammar_type;
	};
	namespace nodeid
	{
	  typedef ObjectClassTypeData<ObjectClassTypeTraits<nodeid::ClassType,
			                                            nodeid::ClassType::LocalNodeId>>  LocalNodeIdData;
	  const lmp::WORD localNodeIdLength = c_objHeaderLength + 4;
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_NODE_ID_HPP_ */
