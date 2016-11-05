#ifndef LMP_OBJ_OBJECTCLASS_HPP_
#define LMP_OBJ_OBJECTCLASS_HPP_
/*
 * ObjectClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
    enum class ObjectClass : lmp::BYTE
	{
      ControlChannelID = 1,
      NodeID,
	  LinkID,
	  InterfaceID,
	  MessageID,
	  Config,
	  Hello
	};
    std::ostream& operator<<(
      std::ostream&       os,
	  const ObjectClass&  objClass);
	const lmp::WORD objHeaderLength = 4;
    namespace parse
    {
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      struct control_channel_id_object_class_grammar : qi::grammar<Iterator, ObjectClass()>
      {
    	control_channel_id_object_class_grammar();

    	qi::rule<Iterator, ObjectClass()>  control_channel_id_object_class_rule;
      };
      template <typename Iterator>
      struct node_id_object_class_grammar : qi::grammar<Iterator, ObjectClass()>
      {
    	node_id_object_class_grammar();

    	qi::rule<Iterator, ObjectClass()>  node_id_object_class_rule;
      };
      template <typename Iterator>
      struct link_id_object_class_grammar : qi::grammar<Iterator, ObjectClass()>
      {
    	link_id_object_class_grammar();

    	qi::rule<Iterator, ObjectClass()>  link_id_object_class_rule;
      };
      template <typename Iterator>
      struct interface_id_object_class_grammar : qi::grammar<Iterator, ObjectClass()>
      {
    	interface_id_object_class_grammar();

    	qi::rule<Iterator, ObjectClass()>  interface_id_object_class_rule;
      };
      template <typename Iterator>
      struct message_id_object_class_grammar : qi::grammar<Iterator, ObjectClass()>
      {
    	message_id_object_class_grammar();

    	qi::rule<Iterator, ObjectClass()>  message_id_object_class_rule;
      };
      template <typename Iterator>
      struct config_object_class_grammar : qi::grammar<Iterator, ObjectClass()>
      {
    	config_object_class_grammar();

    	qi::rule<Iterator, ObjectClass()>  config_object_class_rule;
      };
      template <typename Iterator>
      struct hello_object_class_grammar : qi::grammar<Iterator, ObjectClass()>
      {
    	hello_object_class_grammar();

    	qi::rule<Iterator, ObjectClass()>  hello_object_class_rule;
      };
    } // namespace parse
    namespace otype
    {
      enum ObjectClass
	  {
    	ControlChannelID = 1,
		NodeID,
		LinkID,
		InterfaceID,
		MessageID,
		Config,
		Hello
	  };
    } // namespace otype
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_HPP_ */
