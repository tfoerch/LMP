#ifndef LMP_OBJ_OBJECTCLASS_DEF_HPP_
#define LMP_OBJ_OBJECTCLASS_DEF_HPP_
/*
 * ObjectClass_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

namespace lmp
{
  namespace obj
  {
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      control_channel_id_object_class_grammar<Iterator>::control_channel_id_object_class_grammar()
	  : control_channel_id_object_class_grammar::base_type(control_channel_id_object_class_rule, "control_channel_id_object_class")
      {
          using qi::byte_;
          using namespace qi::labels;

          control_channel_id_object_class_rule =
  				byte_(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::ControlChannelID))
  				[ _val = ObjectClass::ControlChannelID ]
				;

          control_channel_id_object_class_rule.name("control_channel_id_object_class");
      }

      template <typename Iterator>
      node_id_object_class_grammar<Iterator>::node_id_object_class_grammar()
	  : node_id_object_class_grammar::base_type(node_id_object_class_rule, "node_id_object_class")
      {
          using qi::byte_;
          using namespace qi::labels;

          node_id_object_class_rule =
  				byte_(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::NodeID))
  				[ _val = ObjectClass::NodeID ]
				;

          node_id_object_class_rule.name("node_id_object_class");
      }

      template <typename Iterator>
      link_id_object_class_grammar<Iterator>::link_id_object_class_grammar()
	  : link_id_object_class_grammar::base_type(link_id_object_class_rule, "link_id_object_class")
      {
          using qi::byte_;
          using namespace qi::labels;

          link_id_object_class_rule =
  				byte_(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::LinkID))
  				[ _val = ObjectClass::LinkID ]
				;

          link_id_object_class_rule.name("link_id_object_class");
      }

      template <typename Iterator>
      interface_id_object_class_grammar<Iterator>::interface_id_object_class_grammar()
	  : interface_id_object_class_grammar::base_type(interface_id_object_class_rule, "interface_id_object_class")
      {
          using qi::byte_;
          using namespace qi::labels;

          interface_id_object_class_rule =
  				byte_(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::InterfaceID))
  				[ _val = ObjectClass::InterfaceID ]
				;

          interface_id_object_class_rule.name("interface_id_object_class");
      }

      template <typename Iterator>
      message_id_object_class_grammar<Iterator>::message_id_object_class_grammar()
	  : message_id_object_class_grammar::base_type(message_id_object_class_rule, "message_id_object_class")
      {
          using qi::byte_;
          using namespace qi::labels;

          message_id_object_class_rule =
  				byte_(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::MessageID))
  				[ _val = ObjectClass::MessageID ]
				;

          message_id_object_class_rule.name("message_id_object_class");
      }

      template <typename Iterator>
      config_object_class_grammar<Iterator>::config_object_class_grammar()
	  : config_object_class_grammar::base_type(config_object_class_rule, "config_object_class")
      {
          using qi::byte_;
          using namespace qi::labels;

          config_object_class_rule =
  				byte_(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::Config))
  				[ _val = ObjectClass::Config ]
				;

          config_object_class_rule.name("config_object_class");
      }

      template <typename Iterator>
      hello_object_class_grammar<Iterator>::hello_object_class_grammar()
	  : hello_object_class_grammar::base_type(hello_object_class_rule, "hello_object_class")
      {
          using qi::byte_;
          using namespace qi::labels;

          hello_object_class_rule =
  				byte_(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::Hello))
  				[ _val = ObjectClass::Hello ]
				;

          hello_object_class_rule.name("hello_object_class");
      }

    } // namespace parse
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_DEF_HPP_ */
