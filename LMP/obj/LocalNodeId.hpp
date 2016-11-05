#ifndef LMP_OBJ_LOCAL_NODE_ID_HPP_
#define LMP_OBJ_LOCAL_NODE_ID_HPP_
/*
 * LocalNodeId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/NodeIdTypeTraits.hpp"
#include "obj/NodeIdIF.hpp"
#include "obj/NodeIdData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<nodeid::ClassType, nodeid::ClassType::LocalNodeId>  LocalNodeId;
	namespace nodeid
	{
	  struct LocalNodeIdData
	  {
	    bool        m_negotiable;
	    lmp::DWORD  m_nodeId;
	  };
	  std::ostream& operator<<(
		std::ostream&           os,
		const LocalNodeIdData&  nodeId);
	  const lmp::WORD localNodeIdLength = objHeaderLength + 4;
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
        struct local_node_id_grammar : qi::grammar<Iterator, LocalNodeIdData()>
        {
      	  local_node_id_grammar();

      	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
      	  qi::rule<Iterator, LocalNodeIdData()>                         local_node_id_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_NODE_ID_HPP_ */
