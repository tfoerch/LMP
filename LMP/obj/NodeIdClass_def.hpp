#ifndef LMP_OBJ_NODE_ID_CLASS_DEF_HPP_
#define LMP_OBJ_NODE_ID_CLASS_DEF_HPP_
/*
 * NodeIdClass_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdClass.hpp"
//#include "obj/ClassTypeAndNegotiableFlag_def.hpp"
#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::nodeid::NodeIdBody,
  (lmp::DWORD,       m_nodeId)
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
        node_id_body_grammar<Iterator>::node_id_body_grammar()
		: node_id_body_grammar::base_type(node_id_body_rule,
				                          "node_id")
        {
     	  using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          node_id_body_rule =
        		big_dword [ at_c<0>(_val) = _1 ]
				;

          node_id_body_rule.name("node_id");
        }
	  } // namespace parse
	  namespace generate
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        node_id_body_grammar<OutputIterator>::node_id_body_grammar()
		: node_id_body_grammar::base_type(node_id_body_rule, "node_id_body")
        {
          using qi::byte_;
          using qi::big_dword;
          using qi::eps;
          using phoenix::at_c;
          using namespace qi::labels;

          node_id_body_rule =
                big_dword [ _1 = at_c<0>(_val) ]
				;

          node_id_body_rule.name("node_id_body");
        }
      }
    } // namespace nodeid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CLASS_DEF_HPP_ */
