#ifndef LMP_OBJ_REMOTE_NODE_ID_DEF_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_DEF_HPP_
/*
 * RemoteNodeId_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeId.hpp"
#include "obj/ObjectHeader_def.hpp"
#include "obj/ControlChannelIdClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::nodeid::RemoteNodeIdData,
  (bool,            m_negotiable)
  (lmp::DWORD,      m_nodeId)
)

namespace lmp
{
  namespace obj
  {
	namespace nodeid
	{
      namespace parse
	  {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        remote_node_id_grammar<Iterator>::remote_node_id_grammar()
		: remote_node_id_grammar::base_type(remote_node_id_rule,
				                            "remote_node_id"),
	      object_header_input(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::NodeID),
							  static_cast<std::underlying_type<lmp::obj::nodeid::ClassType>::type>(lmp::obj::nodeid::ClassType::RemoteNodeId),
							  remoteNodeIdLength)

        {
     	  using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          remote_node_id_rule =
          		object_header(phoenix::cref(object_header_input))  [ at_c<0>(_val) = _1 ]
  		        >> big_dword [ at_c<1>(_val) = _1 ]
				;

          remote_node_id_rule.name("remote_node_id");
        }

	  } // namespace parse
	} // namespace nodeid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_DEF_HPP_ */
