#ifndef LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_HPP_
#define LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_HPP_
/*
 * ControlChannelIdClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      enum class ClassType : lmp::BYTE
      {
        LocalCCId = 1,
        RemoteCCId
      };
      std::ostream& operator<<(
        std::ostream&     os,
        const ClassType&  cType);
      struct ControlChannelIdBody
      {
        lmp::DWORD  m_CCId;
      };
      std::ostream& operator<<(
        std::ostream&                os,
        const ControlChannelIdBody&  controlChannelIdBody);
      struct IsEqualFtor
      {
        bool operator()(
          const ControlChannelIdBody& first,
          const ControlChannelIdBody& second) const;
      };
      struct GetLengthFtor
      {
        lmp::WORD operator()(
          const ControlChannelIdBody& controlChannelIdBody) const;
        static const lmp::WORD c_length;
      };
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct control_channel_id_body_grammar : qi::grammar<Iterator, ControlChannelIdBody()>
        {
          control_channel_id_body_grammar();

          qi::rule<Iterator, ControlChannelIdBody()>  control_channel_id_body_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct control_channel_id_body_grammar : karma::grammar<OutputIterator, ControlChannelIdBody()>
        {
          control_channel_id_body_grammar();

          karma::rule<OutputIterator, ControlChannelIdBody()>                  control_channel_id_body_rule;
        };
      }
    }
    template <>
    struct ObjectClassTypeConst<ccid::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::ControlChannelID;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_HPP_ */
