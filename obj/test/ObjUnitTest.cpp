/*
 * ObjUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#if 0
#include "obj/ByteSequence.hpp"
#include "obj/LocalCCId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/UnknownCCIdCType.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteNodeId.hpp"
#include "obj/UnknownNodeIdCType.hpp"
#include "obj/MessageId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/UnknownMessageIdCType.hpp"
#include "obj/HelloConfig.hpp"
#include "obj/UnknownConfigCType.hpp"
#include "obj/Hello.hpp"
#include "obj/UnknownHelloCType.hpp"
#endif
#include "obj/LocalCCIdParser.hpp"
#include "obj/LocalCCIdGenerator.hpp"
#include "obj/LocalCCIdAst.hpp"
#include "obj/RemoteCCIdParser.hpp"
#include "obj/RemoteCCIdGenerator.hpp"
#include "obj/RemoteCCIdAst.hpp"
#include "obj/UnknownCCIdCTypeAst.hpp"
#include "obj/UnknownCCIdCTypeParser.hpp"
#include "obj/LocalNodeIdParser.hpp"
#include "obj/LocalNodeIdGenerator.hpp"
#include "obj/LocalNodeIdAst.hpp"
#include "obj/RemoteNodeIdParser.hpp"
#include "obj/RemoteNodeIdGenerator.hpp"
#include "obj/RemoteNodeIdAst.hpp"
#include "obj/UnknownNodeIdCTypeAst.hpp"
#include "obj/UnknownNodeIdCTypeParser.hpp"
#include "obj/UnknownObjectClassParser.hpp"
#include "obj/UnknownObjectClassGenerator.hpp"
//#include "obj/ObjectClassUnknownCTypeParser.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator.hpp"
#if 0
#include "obj/ConfigObjectSequence.hpp"
#endif
#include "obj/LMPParseConfig.hpp"
#include <boost/spirit/home/x3/core/parse.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE LMP
// #include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>

namespace lmp
{
  namespace obj
  {
    typedef std::vector<lmp::BYTE>  ByteSequence;
    namespace hex_stream
    {
      std::ostream& operator<<(
        std::ostream&        os,
        const ByteSequence&  byteSequence);
    }
  }
}

namespace boost
{
  namespace test_tools
  {
    namespace tt_detail
    {
      template<>
      struct print_log_value<std::vector<lmp::BYTE>>
      {
        void operator()(
          std::ostream& os,
          const std::vector<lmp::BYTE>& byteSequence)
        {
          lmp::obj::hex_stream::operator <<(os, byteSequence);
        }
      };
    }
  }
}

BOOST_AUTO_TEST_SUITE( obj )

#if 0
#include <string>
#include <iostream>
#include <iomanip>

#include <boost/spirit/home/x3.hpp>

int main() {
    for (std::string const input : {
            "3 1 2 3", // correct
            "4 1 2 3", // too few
            "2 1 2 3", // too many
            //
            "   3 1 2 3   ",
        })
    {
        std::cout << "\nParsing " << std::left << std::setw(20) << ("'" + input + "':");

        std::vector<int> v;

        bool ok;
        {
            using namespace boost::spirit::x3;

            unsigned n;
            struct _n{};

            auto number = [](auto &ctx) { get<_n>(ctx).get() = _attr(ctx); };
            auto more   = [](auto &ctx) { _pass(ctx) = get<_n>(ctx) >  _val(ctx).size(); };
            auto done   = [](auto &ctx) { _pass(ctx) = get<_n>(ctx) == _val(ctx).size(); };

            auto r = rule<struct _r, std::vector<int> > {}
                  %= with<_n>(std::ref(n))
                        [ omit[uint_[number] ] >> *(eps [more] >> int_) >> eps [done] ];

            ok = phrase_parse(input.begin(), input.end(), r >> eoi, space, v);
        }

        if (ok) {
            std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout << v.size() << " elements: ", " "));
        } else {
            std::cout << "Parse failed";
        }
    }
}

BOOST_AUTO_TEST_CASE( byte_sequence_decode_spirit )
{
   using boost::spirit::qi::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x01, 0x01, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::byte_sequence_grammar<BufIterType>  byteSequenceGrammar;
   lmp::obj::ByteSequence  byteSequence;
   lmp::obj::ByteSequence  expectedByteSequence =
   { 0x01, 0x01, 0x00, 0x08,
     0x01, 0x02, 0x00, 0x08 };
   BOOST_CHECK(parse(begin,
                     last,
                     byteSequenceGrammar(msgLength),
                     byteSequence));
   BOOST_CHECK_EQUAL(byteSequence, expectedByteSequence);
   BOOST_CHECK_EQUAL(byteSequence.size(), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::byte_sequence_grammar<BufOutIterType> byteSequenceGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        byteSequenceGenerateGrammar,
                        byteSequence));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}
#endif

BOOST_AUTO_TEST_CASE( local_control_channel_id_decode_spirit )
{
   using boost::spirit::x3::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x01, 0x01, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::ccid::ast::LocalCCId  localCCId;
   std::stringstream out;
   using boost::spirit::x3::with;
   using lmp::obj::parser::error_handler_type;
   using lmp::obj::parser::error_handler_tag;
   error_handler_type error_handler(begin, last, out); // Our error handler

   // Our parser
   auto const parser =
     // we pass our error handler to the parser so we can access
     // it later on in our on_error and on_sucess handlers
     with<error_handler_tag>(std::ref(error_handler))
     [
       lmp::obj::local_cc_id()
     ];
   BOOST_CHECK(parse(begin,
                     last,
                     parser,
                     localCCId));
   BOOST_CHECK_EQUAL(localCCId.m_ccId, 0x1020008);
   BOOST_CHECK_EQUAL(localCCId.m_header.m_negotiable, false);
//   BOOST_CHECK_EQUAL(localCCId.m_header.ctype, lmp::obj::ccid::ClassType::LocalCCId);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generator::local_cc_id_grammar<BufOutIterType> localCCIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        localCCIdGenerateGrammar,
                        localCCId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( local_control_channel_id_decode_spirit_wrong_length )
{
   using boost::spirit::x3::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x01, 0x01, 0x00, 0x18,
       0x01, 0x02, 0x00, 0x08 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::ccid::ast::LocalCCId  localCCId;
   std::stringstream out;
   using boost::spirit::x3::with;
   using lmp::obj::parser::error_handler_type;
   using lmp::obj::parser::error_handler_tag;
   error_handler_type error_handler(begin, last, out); // Our error handler

   // Our parser
   auto const parser =
     // we pass our error handler to the parser so we can access
     // it later on in our on_error and on_sucess handlers
     with<error_handler_tag>(std::ref(error_handler))
     [
       lmp::obj::local_cc_id()
     ];
   try
   {
     BOOST_CHECK(!parse(begin,
                        last,
                        parser,
                        localCCId));
   }
   catch(boost::spirit::x3::expectation_failure<BufIterType>const& e)
   {
     std::cout << "Expected: " << e.which() << " at '" /*<< std::string(e.where(), str.end())*/ << "'\n";
   }
   // BOOST_CHECK_EQUAL(localCCId.m_ccId, 0x1020008);
   // BOOST_CHECK_EQUAL(localCCId.m_header.m_negotiable, false);
   std::cout << out.str() << std::endl;
}

BOOST_AUTO_TEST_CASE( remote_control_channel_id_decode_spirit )
{
  using boost::spirit::x3::parse;
  using boost::spirit::karma::generate;

  typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
  unsigned char message[] =
    { 0x02, 0x01, 0x00, 0x08,
      0x01, 0x13, 0x0a, 0x03 };
  const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
  boost::asio::const_buffers_1 messageBuffer(message, msgLength);
  BufIterType begin = boost::asio::buffers_begin(messageBuffer);
  BufIterType last = boost::asio::buffers_end(messageBuffer);
  lmp::obj::ccid::ast::RemoteCCId  remoteCCId;
  std::stringstream out;
  using boost::spirit::x3::with;
  using lmp::obj::parser::error_handler_type;
  using lmp::obj::parser::error_handler_tag;
  error_handler_type error_handler(begin, last, out); // Our error handler

  // Our parser
  auto const parser =
    // we pass our error handler to the parser so we can access
    // it later on in our on_error and on_sucess handlers
    with<error_handler_tag>(std::ref(error_handler))
    [
      lmp::obj::remote_cc_id()
    ];
  BOOST_CHECK(parse(begin,
                    last,
                    parser,
                    remoteCCId));
  BOOST_CHECK_EQUAL(remoteCCId.m_ccId, 0x01130a03);
  BOOST_CHECK_EQUAL(remoteCCId.m_header.m_negotiable, false);
//  lmp::obj::ccid::RemoteCCIdData  expectedRemoteCCId = { false, { 0x01130a03 } };
//  BOOST_CHECK_EQUAL(remoteCCId, expectedRemoteCCId);
   // std::cout << msgData << std::endl;
//  BOOST_CHECK_EQUAL(lmp::obj::getLength(remoteCCId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generator::remote_cc_id_grammar<BufOutIterType> remoteCCIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        remoteCCIdGenerateGrammar,
                        remoteCCId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( unknown_control_channel_id_decode_spirit )
{
   using boost::spirit::x3::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x07, 0x01, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::ccid::ast::UnknownCCIdCType  unknownCCIdCType;
   std::stringstream out;
   using boost::spirit::x3::with;
   using lmp::obj::parser::error_handler_type;
   using lmp::obj::parser::error_handler_tag;
   error_handler_type error_handler(begin, last, out); // Our error handler

   // Our parser
   auto const parser =
     // we pass our error handler to the parser so we can access
     // it later on in our on_error and on_sucess handlers
     with<error_handler_tag>(std::ref(error_handler))
     [
       lmp::obj::unknown_cc_id_ctype()
     ];
   BOOST_CHECK(parse(begin,
                     last,
                     parser,
                     unknownCCIdCType));
//   lmp::obj::ccid::ast::UnknownCCIdCType  expectedUnknownCCIdCTypeData =
//     { { 0x07, false }, { 0x01, 0x13, 0x0a, 0x03 } };
   BOOST_CHECK_EQUAL(unknownCCIdCType.m_data.size(), 4);
   BOOST_CHECK_EQUAL(unknownCCIdCType.m_header.m_class_type, 7);
   BOOST_CHECK_EQUAL(unknownCCIdCType.m_header.m_negotiable, false);
   // BOOST_CHECK_EQUAL(unknownCCIdCType, expectedUnknownCCIdCTypeData);
   // BOOST_CHECK_EQUAL(lmp::obj::getLength(unknownCCIdCType), msgLength);
//   std::cout << unknownCCId << std::endl;
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generator::object_class_unknown_ctype_grammar<BufOutIterType,
                                                           lmp::obj::ObjectClass::ControlChannelID>  unknownCcIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        unknownCcIdGenerateGrammar,
                        unknownCCIdCType));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( local_node_id_decode_spirit )
{
  using boost::spirit::x3::parse;
  using boost::spirit::karma::generate;

  typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
  unsigned char message[] =
     { 0x01, 0x02, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
  const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
  boost::asio::const_buffers_1 messageBuffer(message, msgLength);
  BufIterType begin = boost::asio::buffers_begin(messageBuffer);
  BufIterType last = boost::asio::buffers_end(messageBuffer);
  lmp::obj::nodeid::ast::LocalNodeId  localNodeId;
  std::stringstream out;
  using boost::spirit::x3::with;
  using lmp::obj::parser::error_handler_type;
  using lmp::obj::parser::error_handler_tag;
  error_handler_type error_handler(begin, last, out); // Our error handler

  // Our parser
  auto const parser =
    // we pass our error handler to the parser so we can access
    // it later on in our on_error and on_sucess handlers
     with<error_handler_tag>(std::ref(error_handler))
     [
       lmp::obj::local_node_id()
     ];
   BOOST_CHECK(parse(begin,
                     last,
                     parser,
                     localNodeId));
   BOOST_CHECK_EQUAL(localNodeId.m_nodeId, 0x1020008);
   BOOST_CHECK_EQUAL(localNodeId.m_header.m_negotiable, false);
   // std::cout << msgData << std::endl;
   //BOOST_CHECK_EQUAL(lmp::obj::getLength(localNodeId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generator::local_node_id_grammar<BufOutIterType> localNodeIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        localNodeIdGenerateGrammar,
                        localNodeId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( remote_node_id_decode_spirit )
{
  using boost::spirit::x3::parse;
  using boost::spirit::karma::generate;

  typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x02, 0x02, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::nodeid::ast::RemoteNodeId  remoteNodeId;
   std::stringstream out;
   using boost::spirit::x3::with;
   using lmp::obj::parser::error_handler_type;
   using lmp::obj::parser::error_handler_tag;
   error_handler_type error_handler(begin, last, out); // Our error handler

   // Our parser
   auto const parser =
     // we pass our error handler to the parser so we can access
     // it later on in our on_error and on_sucess handlers
     with<error_handler_tag>(std::ref(error_handler))
     [
       lmp::obj::remote_node_id()
     ];
   BOOST_CHECK(parse(begin,
                     last,
                     parser,
                     remoteNodeId));
   BOOST_CHECK_EQUAL(remoteNodeId.m_nodeId, 0x01130a03);
   BOOST_CHECK_EQUAL(remoteNodeId.m_header.m_negotiable, false);
   // std::cout << msgData << std::endl;
   //BOOST_CHECK_EQUAL(lmp::obj::getLength(remoteNodeId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generator::remote_node_id_grammar<BufOutIterType> remoteNodeIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        remoteNodeIdGenerateGrammar,
                        remoteNodeId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( unknown_node_id_decode_spirit )
{
   using boost::spirit::x3::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x0a, 0x02, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::nodeid::ast::UnknownNodeIdCType  unknownNodeIdCType;
   std::stringstream out;
   using boost::spirit::x3::with;
   using lmp::obj::parser::error_handler_type;
   using lmp::obj::parser::error_handler_tag;
   error_handler_type error_handler(begin, last, out); // Our error handler

   // Our parser
   auto const parser =
     // we pass our error handler to the parser so we can access
     // it later on in our on_error and on_sucess handlers
     with<error_handler_tag>(std::ref(error_handler))
     [
       lmp::obj::unknown_node_id_ctype()
     ];
   BOOST_CHECK(parse(begin,
                     last,
                     parser,
                     unknownNodeIdCType));
//   lmp::obj::ccid::ast::UnknownCCIdCType  expectedUnknownCCIdCTypeData =
//     { { 0x07, false }, { 0x01, 0x13, 0x0a, 0x03 } };
   BOOST_CHECK_EQUAL(unknownNodeIdCType.m_data.size(), 4);
   BOOST_CHECK_EQUAL(unknownNodeIdCType.m_header.m_class_type, 0xa);
   BOOST_CHECK_EQUAL(unknownNodeIdCType.m_header.m_negotiable, false);
//   std::cout << unknownCCId << std::endl;
   //BOOST_CHECK_EQUAL(lmp::obj::getLength(unknownNodeId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generator::object_class_unknown_ctype_grammar<BufOutIterType,
                                                          lmp::obj::ObjectClass::NodeID>  unknownNodeIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        unknownNodeIdGenerateGrammar,
                        unknownNodeIdCType));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

#if 0

BOOST_AUTO_TEST_CASE( message_id_decode_spirit )
{
  using boost::spirit::qi::parse;
  using boost::spirit::karma::generate;

  typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
  unsigned char message[] =
     { 0x01, 0x05, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
  const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
  boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::object_class_grammar<BufIterType,
                                         lmp::obj::msgid::ClassType,
                                         lmp::obj::msgid::ClassType::MessageId>  messageIdGrammar;
   lmp::obj::msgid::MessageIdData  messageId;
   lmp::obj::msgid::MessageIdData  expectedMessageId = { false, { 0x1020008 } };
   BOOST_CHECK(parse(begin,
                     last,
                     messageIdGrammar,
                     messageId));
   BOOST_CHECK_EQUAL(messageId, expectedMessageId);
   // std::cout << msgData << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(messageId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_grammar<BufOutIterType,
                                            lmp::obj::msgid::ClassType,
                                            lmp::obj::msgid::ClassType::MessageId> messageIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        messageIdGenerateGrammar,
                        messageId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( message_id_ack_decode_spirit )
{
  using boost::spirit::qi::parse;
  using boost::spirit::karma::generate;

  typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x02, 0x05, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::object_class_grammar<BufIterType,
                                         lmp::obj::msgid::ClassType,
                                         lmp::obj::msgid::ClassType::MessageIdAck>  messageIdAckGrammar;
   lmp::obj::msgid::MessageIdAckData  messageIdAck;
   lmp::obj::msgid::MessageIdAckData  expectedMessageIdAck = { false, { 0x1020008 } };
   BOOST_CHECK(parse(begin,
                     last,
                     messageIdAckGrammar,
                     messageIdAck));
   BOOST_CHECK_EQUAL(messageIdAck, expectedMessageIdAck);
   // std::cout << msgData << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(messageIdAck), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_grammar<BufOutIterType,
                                            lmp::obj::msgid::ClassType,
                                            lmp::obj::msgid::ClassType::MessageIdAck> messageIdAckGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        messageIdAckGenerateGrammar,
                        messageIdAck));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( unknown_message_id_decode_spirit )
{
   using boost::spirit::qi::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x07, 0x05, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::object_class_unknown_ctype_grammar<BufIterType,
                                                       lmp::obj::ObjectClass::MessageID>  unknownMessageIdGrammar;
   lmp::obj::msgid::UnknownMessageIdCTypeData  unknownMessageId;
   lmp::obj::msgid::UnknownMessageIdCTypeData  expectedUnknownMessageId = { 0x07, false, { 0x01, 0x13, 0x0a, 0x03 } };
   BOOST_CHECK(parse(begin,
                     last,
                     unknownMessageIdGrammar,
                     unknownMessageId));
   BOOST_CHECK_EQUAL(unknownMessageId, expectedUnknownMessageId);
//   std::cout << unknownMessageId << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(unknownMessageId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_unknown_ctype_grammar<BufOutIterType,
                                                          lmp::obj::ObjectClass::MessageID>  unknownMessageIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        unknownMessageIdGenerateGrammar,
                        unknownMessageId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( hello_config_decode_spirit )
{
  using boost::spirit::qi::parse;
  using boost::spirit::karma::generate;

  typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
  unsigned char message[] =
     { 0x81, 0x06, 0x00, 0x08,
       0x00, 0x9A, 0x01, 0xCF };
  const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
  boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::object_class_grammar<BufIterType,
                                         lmp::obj::config::ClassType,
                                         lmp::obj::config::ClassType::HelloConfig>  helloConfigGrammar;
   lmp::obj::config::HelloConfigData  helloConfig;
   lmp::obj::config::HelloConfigData  expectedHelloConfig = { true, { 0x009A, 0x01CF } };
   BOOST_CHECK(parse(begin,
                     last,
                     helloConfigGrammar,
                     helloConfig));
   BOOST_CHECK_EQUAL(helloConfig, expectedHelloConfig);
   // std::cout << msgData << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(helloConfig), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_grammar<BufOutIterType,
                                            lmp::obj::config::ClassType,
                                            lmp::obj::config::ClassType::HelloConfig> helloConfigGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        helloConfigGenerateGrammar,
                        helloConfig));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( unknown_config_decode_spirit )
{
   using boost::spirit::qi::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x87, 0x06, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::object_class_unknown_ctype_grammar<BufIterType,
                                                       lmp::obj::ObjectClass::Config>  unknownConfigGrammar;
   lmp::obj::config::UnknownConfigCTypeData  unknownConfig;
   lmp::obj::config::UnknownConfigCTypeData  expectedUnknownConfig = { 0x07, true, { 0x01, 0x13, 0x0a, 0x03 } };
   BOOST_CHECK(parse(begin,
                     last,
                     unknownConfigGrammar,
                     unknownConfig));
   BOOST_CHECK_EQUAL(unknownConfig, expectedUnknownConfig);
//   std::cout << unknownConfig << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(unknownConfig), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_unknown_ctype_grammar<BufOutIterType,
                                                          lmp::obj::ObjectClass::Config>  unknownConfigGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        unknownConfigGenerateGrammar,
                        unknownConfig));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( hello_decode_spirit )
{
  using boost::spirit::qi::parse;
  using boost::spirit::karma::generate;

  typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
  unsigned char message[] =
     { 0x01, 0x07, 0x00, 0x0C,
       0x00, 0x00, 0x00, 0x01,
       0x00, 0x00, 0x00, 0x00 };
  const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
  boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::object_class_grammar<BufIterType,
                                         lmp::obj::hello::ClassType,
                                         lmp::obj::hello::ClassType::Hello>  helloGrammar;
   lmp::obj::hello::HelloData  hello;
   lmp::obj::hello::HelloData  expectedHello = { false, { 0x00000001, 0x00000000 } };
   BOOST_CHECK(parse(begin,
                     last,
                     helloGrammar,
                     hello));
   BOOST_CHECK_EQUAL(hello, expectedHello);
   // std::cout << msgData << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(hello), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_grammar<BufOutIterType,
                                            lmp::obj::hello::ClassType,
                                            lmp::obj::hello::ClassType::Hello> helloGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        helloGenerateGrammar,
                        hello));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( unknown_hello_decode_spirit )
{
   using boost::spirit::qi::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x07, 0x07, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::object_class_unknown_ctype_grammar<BufIterType,
                                                       lmp::obj::ObjectClass::Hello>  unknownHelloGrammar;
   lmp::obj::hello::UnknownHelloCTypeData  unknownHello;
   lmp::obj::hello::UnknownHelloCTypeData  expectedUnknownHello = { 0x07, false, { 0x01, 0x13, 0x0a, 0x03 } };
   BOOST_CHECK(parse(begin,
                     last,
                     unknownHelloGrammar,
                     unknownHello));
   BOOST_CHECK_EQUAL(unknownHello, expectedUnknownHello);
//   std::cout << unknownHello << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(unknownHello), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_unknown_ctype_grammar<BufOutIterType,
                                                          lmp::obj::ObjectClass::Hello>  unknownHelloGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        unknownHelloGenerateGrammar,
                        unknownHello));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

#endif

BOOST_AUTO_TEST_CASE( unknown_object_class_decode_spirit )
{
   using boost::spirit::x3::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x01, 0x09, 0x00, 0x0C,
       0x00, 0x00, 0x00, 0x01,
       0x00, 0x00, 0x00, 0x00 };
   const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
   boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::ast::UnknownObjectClass  unknownObjectClass;
   std::stringstream out;
   using boost::spirit::x3::with;
   using lmp::obj::parser::error_handler_type;
   using lmp::obj::parser::error_handler_tag;
   error_handler_type error_handler(begin, last, out); // Our error handler

   // Our parser
   auto const parser =
       // we pass our error handler to the parser so we can access
       // it later on in our on_error and on_sucess handlers
       with<error_handler_tag>(std::ref(error_handler))
       [
         lmp::obj::unknown_object_class()
       ];
   BOOST_CHECK(parse(begin,
		     last,
		     parser,
		     unknownObjectClass));
//   lmp::obj::ast::UnknownObjectClass  expectedUnknownObjectClass =
//     { { 0x09, 0x01, false }, { 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 } };
   BOOST_CHECK_EQUAL(unknownObjectClass.m_data.size(), 8);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_header.m_object_class, 9);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_header.m_class_type, 1);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_header.m_negotiable, false);
   // BOOST_CHECK_EQUAL(unknownObjectClass, expectedUnknownObjectClass);
   BOOST_CHECK_EQUAL(lmp::obj::getLength(unknownObjectClass), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generator::unknown_object_class_grammar<BufOutIterType>  unknownObjectClassGeneratorGrammar;
   BOOST_CHECK(generate(gen_begin,
                        unknownObjectClassGeneratorGrammar,
                        unknownObjectClass));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

#if 0
BOOST_AUTO_TEST_CASE( config_object_sequence_decode_spirit )
{
  using boost::spirit::qi::parse;
  using boost::spirit::karma::generate;

  typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
  unsigned char message[] =
     { 0x81, 0x06, 0x00, 0x08,
       0x00, 0x9A, 0x01, 0xCF,
       0x87, 0x06, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
  const lmp::WORD msgLength = sizeof(message)/sizeof(unsigned char);
  boost::asio::const_buffers_1 messageBuffer(message, msgLength);
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::config::parse::config_object_sequence_grammar<BufIterType>  configObjectSequenceGrammar;
   lmp::obj::config::ConfigObjectSequence  configObjectSequence;
   lmp::obj::config::ConfigObjectSequence  expectedConfigObjectSequence;
   {
     lmp::obj::config::HelloConfigData  expectedHelloConfig = { true, { 0x009A, 0x01CF } };
     expectedConfigObjectSequence.push_back(lmp::obj::config::ConfigCTypes(expectedHelloConfig));
     lmp::obj::config::UnknownConfigCTypeData  expectedUnknownConfig = { 0x07, true, { 0x01, 0x13, 0x0a, 0x03 } };
     expectedConfigObjectSequence.push_back(lmp::obj::config::ConfigCTypes(expectedUnknownConfig));
   }
   BOOST_CHECK(parse(begin,
                     last,
                     configObjectSequenceGrammar(msgLength),
                     configObjectSequence));
   BOOST_CHECK_EQUAL(configObjectSequence, expectedConfigObjectSequence);
   BOOST_CHECK_EQUAL(lmp::obj::config::getLength(configObjectSequence), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::config::generate::config_object_sequence_grammar<BufOutIterType>  configObjectSequenceGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        configObjectSequenceGenerateGrammar,
                        configObjectSequence));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}
#endif

#if 0
BOOST_AUTO_TEST_CASE( obj_header_decode )
{
  {
	unsigned char message[] =
      { 0x01, 0x01, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult decodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::obj::ObjectHeader::invalid_length);
    }
  }
  {
	unsigned char message[] =
    { 0x01, 0x27, 0x00, 0x08,
      0x01, 0x02, 0x00, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult decodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::obj::ObjectHeader::not_supported_object_class);
    }
  }
  {
	unsigned char message[] =
      { 0x01, 0x01, 0x00, 0x08,
        0x01, 0x02, 0x00, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult decodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(decodingResult.first);
    BOOST_CHECK(!decodingResult.second);
    if (decodingResult.first)
    {
	  const lmp::obj::ObjectHeader& header = *decodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::ControlChannelID);
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  unsigned char emptySpace[lmp::obj::ObjectHeader::c_headerLength];
	  boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                          sizeof(message)/sizeof(unsigned char));
	  lmp::obj::ObjectHeader::OptEncError optEncError = header.encode(emptyBuffer);
	  BOOST_CHECK(!optEncError);
	  BOOST_CHECK_EQUAL_COLLECTIONS(message, message + lmp::obj::ObjectHeader::c_headerLength,
			                        emptySpace, emptySpace + lmp::obj::ObjectHeader::c_headerLength);
    }
  }
}

BOOST_AUTO_TEST_CASE( localCCId )
{
  {
	unsigned char message[] =
      { 0x01, 0x01, 0x00, 0x08,
        0x01, 0x02, 0x00, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(headerDecodingResult.first);
    BOOST_CHECK(!headerDecodingResult.second);
    if (headerDecodingResult.first)
    {
	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::ControlChannelID);
	  BOOST_CHECK_EQUAL(header.getClassType(), 0x01);
	  lmp::obj::ObjectClassIF<lmp::obj::ccid::ClassType>::OptClassType optCType =
	    lmp::obj::ObjectClassIF<lmp::obj::ccid::ClassType>::classType_cast(header.getClassType());
	  BOOST_CHECK(optCType);
      if (optCType)
      {
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::ccid::ClassType::LocalCCId);
      }
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  lmp::obj::LocalCCId::DecodingResult decodingResult =
		lmp::obj::LocalCCId::decode(header, messageBuffer);
	  if (decodingResult.first)
	  {
		const lmp::obj::LocalCCId& localCCId = *decodingResult.first;
		BOOST_CHECK_EQUAL(localCCId.getControlChannelId(), 0x1020008);
        const lmp::WORD msgLength =
          lmp::obj::ObjectHeader::c_headerLength +
		  lmp::obj::ControlChannelIdData::getContentsLength();
        unsigned char emptySpace[msgLength];
        boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                            sizeof(message)/sizeof(unsigned char));
        lmp::obj::ObjectHeader::OptEncError optEncError = localCCId.encode(emptyBuffer);
        BOOST_CHECK(!optEncError);
//        for (int i = 0; i < msgLength; ++i)
//        {
//        	std::cout << std::hex << static_cast<lmp::WORD>(emptySpace[i]) << std::endl;
//        }
        BOOST_CHECK_EQUAL_COLLECTIONS(message,
    		                          message + msgLength,
 		                              emptySpace, emptySpace + msgLength);
	  }
    }
  }
}

BOOST_AUTO_TEST_CASE( remoteCCId )
{
  {
	unsigned char message[] =
	  { 0x02, 0x01, 0x00, 0x08,
	    0x01, 0x02, 0x00, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
			                                sizeof(message)/sizeof(unsigned char));
	lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
	  lmp::obj::ObjectHeader::decode(messageBuffer);
	BOOST_CHECK(headerDecodingResult.first);
	BOOST_CHECK(!headerDecodingResult.second);
	if (headerDecodingResult.first)
	{
	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::ControlChannelID);
	  BOOST_CHECK_EQUAL(header.getClassType(), 0x02);
	  lmp::obj::ObjectClassIF<lmp::obj::ccid::ClassType>::OptClassType optCType =
	    lmp::obj::ObjectClassIF<lmp::obj::ccid::ClassType>::classType_cast(header.getClassType());
	  BOOST_CHECK(optCType);
      if (optCType)
      {
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::ccid::ClassType::RemoteCCId);
      }
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  lmp::obj::RemoteCCId::DecodingResult decodingResult =
	    lmp::obj::RemoteCCId::decode(header, messageBuffer);
	  if (decodingResult.first)
	  {
		const lmp::obj::RemoteCCId& remoteCCId = *decodingResult.first;
		BOOST_CHECK_EQUAL(remoteCCId.getControlChannelId(), 0x1020008);
        const lmp::WORD msgLength =
          lmp::obj::ObjectHeader::c_headerLength +
		  lmp::obj::ControlChannelIdData::getContentsLength();
        unsigned char emptySpace[msgLength];
        boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                            sizeof(message)/sizeof(unsigned char));
        lmp::obj::ObjectHeader::OptEncError optEncError = remoteCCId.encode(emptyBuffer);
        BOOST_CHECK(!optEncError);
        BOOST_CHECK_EQUAL_COLLECTIONS(message,
    		                          message + msgLength,
 		                              emptySpace, emptySpace + msgLength);
	  }
    }
  }
}

BOOST_AUTO_TEST_CASE( localNodeId )
{
  {
	unsigned char message[] =
      { 0x01, 0x02, 0x00, 0x08,
        0x01, 0x02, 0x05, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(headerDecodingResult.first);
    BOOST_CHECK(!headerDecodingResult.second);
    if (headerDecodingResult.first)
    {
	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::NodeID);
	  BOOST_CHECK_EQUAL(header.getClassType(), 0x01);
	  lmp::obj::ObjectClassIF<lmp::obj::nodeid::ClassType>::OptClassType optCType =
	    lmp::obj::ObjectClassIF<lmp::obj::nodeid::ClassType>::classType_cast(header.getClassType());
	  BOOST_CHECK(optCType);
      if (optCType)
      {
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::nodeid::ClassType::LocalNodeId);
      }
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  lmp::obj::LocalNodeId::DecodingResult decodingResult =
		lmp::obj::LocalNodeId::decode(header, messageBuffer);
	  if (decodingResult.first)
	  {
		const lmp::obj::LocalNodeId& localNodeId = *decodingResult.first;
		BOOST_CHECK_EQUAL(localNodeId.getNodeId(), 0x1020508);
        const lmp::WORD msgLength =
          lmp::obj::ObjectHeader::c_headerLength +
		  lmp::obj::NodeIdData::getContentsLength();
        unsigned char emptySpace[msgLength];
        boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                            sizeof(message)/sizeof(unsigned char));
        lmp::obj::ObjectHeader::OptEncError optEncError = localNodeId.encode(emptyBuffer);
        BOOST_CHECK(!optEncError);
//        for (int i = 0; i < msgLength; ++i)
//        {
//        	std::cout << std::hex << static_cast<lmp::WORD>(emptySpace[i]) << std::endl;
//        }
        BOOST_CHECK_EQUAL_COLLECTIONS(message,
    		                          message + msgLength,
 		                              emptySpace, emptySpace + msgLength);
	  }
    }
  }
}

BOOST_AUTO_TEST_CASE( remoteNodeId )
{
  {
	unsigned char message[] =
	  { 0x02, 0x02, 0x00, 0x08,
	    0x01, 0x02, 0x05, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
			                                sizeof(message)/sizeof(unsigned char));
	lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
	  lmp::obj::ObjectHeader::decode(messageBuffer);
	BOOST_CHECK(headerDecodingResult.first);
	BOOST_CHECK(!headerDecodingResult.second);
	if (headerDecodingResult.first)
	{
	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::NodeID);
	  BOOST_CHECK_EQUAL(header.getClassType(), 0x02);
	  lmp::obj::ObjectClassIF<lmp::obj::nodeid::ClassType>::OptClassType optCType =
	    lmp::obj::ObjectClassIF<lmp::obj::nodeid::ClassType>::classType_cast(header.getClassType());
	  BOOST_CHECK(optCType);
      if (optCType)
      {
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::nodeid::ClassType::RemoteNodeId);
      }
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  lmp::obj::RemoteNodeId::DecodingResult decodingResult =
	    lmp::obj::RemoteNodeId::decode(header, messageBuffer);
	  if (decodingResult.first)
	  {
		const lmp::obj::RemoteNodeId& remoteNodeId = *decodingResult.first;
		BOOST_CHECK_EQUAL(remoteNodeId.getNodeId(), 0x1020508);
        const lmp::WORD msgLength =
          lmp::obj::ObjectHeader::c_headerLength +
		  lmp::obj::NodeIdData::getContentsLength();
        unsigned char emptySpace[msgLength];
        boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                            sizeof(message)/sizeof(unsigned char));
        lmp::obj::ObjectHeader::OptEncError optEncError = remoteNodeId.encode(emptyBuffer);
        BOOST_CHECK(!optEncError);
        BOOST_CHECK_EQUAL_COLLECTIONS(message,
    		                          message + msgLength,
 		                              emptySpace, emptySpace + msgLength);
	  }
    }
  }
}

BOOST_AUTO_TEST_CASE( messageId )
{
  {
	unsigned char message[] =
      { 0x01, 0x05, 0x00, 0x08,
        0x01, 0x02, 0x05, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(headerDecodingResult.first);
    BOOST_CHECK(!headerDecodingResult.second);
    if (headerDecodingResult.first)
    {
	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::MessageID);
	  BOOST_CHECK_EQUAL(header.getClassType(), 0x01);
	  lmp::obj::ObjectClassIF<lmp::obj::msgid::ClassType>::OptClassType optCType =
	    lmp::obj::ObjectClassIF<lmp::obj::msgid::ClassType>::classType_cast(header.getClassType());
	  BOOST_CHECK(optCType);
      if (optCType)
      {
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::msgid::ClassType::MessageId);
      }
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  lmp::obj::MessageId::DecodingResult decodingResult =
		lmp::obj::MessageId::decode(header, messageBuffer);
	  if (decodingResult.first)
	  {
		const lmp::obj::MessageId& messageId = *decodingResult.first;
		BOOST_CHECK_EQUAL(messageId.getMessageId(), 0x1020508);
        const lmp::WORD msgLength =
          lmp::obj::ObjectHeader::c_headerLength +
		  lmp::obj::MessageIdData::getContentsLength();
        unsigned char emptySpace[msgLength];
        boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                            sizeof(message)/sizeof(unsigned char));
        lmp::obj::ObjectHeader::OptEncError optEncError = messageId.encode(emptyBuffer);
        BOOST_CHECK(!optEncError);
//        for (int i = 0; i < msgLength; ++i)
//        {
//        	std::cout << std::hex << static_cast<lmp::WORD>(emptySpace[i]) << std::endl;
//        }
        BOOST_CHECK_EQUAL_COLLECTIONS(message,
    		                          message + msgLength,
 		                              emptySpace, emptySpace + msgLength);
	  }
    }
  }
}

BOOST_AUTO_TEST_CASE( messageIdAck )
{
  {
	unsigned char message[] =
	  { 0x02, 0x05, 0x00, 0x08,
	    0x01, 0x02, 0x05, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
			                                sizeof(message)/sizeof(unsigned char));
	lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
	  lmp::obj::ObjectHeader::decode(messageBuffer);
	BOOST_CHECK(headerDecodingResult.first);
	BOOST_CHECK(!headerDecodingResult.second);
	if (headerDecodingResult.first)
	{
	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::MessageID);
	  BOOST_CHECK_EQUAL(header.getClassType(), 0x02);
	  lmp::obj::ObjectClassIF<lmp::obj::msgid::ClassType>::OptClassType optCType =
	    lmp::obj::ObjectClassIF<lmp::obj::msgid::ClassType>::classType_cast(header.getClassType());
	  BOOST_CHECK(optCType);
      if (optCType)
      {
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::msgid::ClassType::MessageIdAck);
      }
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  lmp::obj::MessageIdAck::DecodingResult decodingResult =
	    lmp::obj::MessageIdAck::decode(header, messageBuffer);
	  if (decodingResult.first)
	  {
		const lmp::obj::MessageIdAck& messageIdAck = *decodingResult.first;
		BOOST_CHECK_EQUAL(messageIdAck.getMessageId(), 0x1020508);
        const lmp::WORD msgLength =
          lmp::obj::ObjectHeader::c_headerLength +
		  lmp::obj::MessageIdData::getContentsLength();
        unsigned char emptySpace[msgLength];
        boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                            sizeof(message)/sizeof(unsigned char));
        lmp::obj::ObjectHeader::OptEncError optEncError = messageIdAck.encode(emptyBuffer);
        BOOST_CHECK(!optEncError);
        BOOST_CHECK_EQUAL_COLLECTIONS(message,
    		                          message + msgLength,
 		                              emptySpace, emptySpace + msgLength);
	  }
    }
  }
}

BOOST_AUTO_TEST_CASE( helloConfig )
{
  {
	unsigned char message[] =
      { 0x81, 0x06, 0x00, 0x08,
        0x00, 0x9A, 0x01, 0xCF };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(headerDecodingResult.first);
    BOOST_CHECK(!headerDecodingResult.second);
    if (headerDecodingResult.first)
    {
	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), true);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::Config);
	  BOOST_CHECK_EQUAL(header.getClassType(), 0x01);
	  lmp::obj::ObjectClassIF<lmp::obj::config::ClassType>::OptClassType optCType =
	    lmp::obj::ObjectClassIF<lmp::obj::config::ClassType>::classType_cast(header.getClassType());
	  BOOST_CHECK(optCType);
      if (optCType)
      {
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::config::ClassType::HelloConfig);
      }
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  lmp::obj::HelloConfig::DecodingResult decodingResult =
		lmp::obj::HelloConfig::decode(header, messageBuffer);
	  if (decodingResult.first)
	  {
		const lmp::obj::HelloConfig& helloConfig = *decodingResult.first;
		BOOST_CHECK_EQUAL(helloConfig.getHelloIntv(), 0x009A);
		BOOST_CHECK_EQUAL(helloConfig.getHelloDeadIntv(), 0x01CF);
        const lmp::WORD msgLength =
          lmp::obj::ObjectHeader::c_headerLength +
		  lmp::obj::HelloConfigData::getContentsLength();
        unsigned char emptySpace[msgLength];
        boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                            sizeof(message)/sizeof(unsigned char));
        lmp::obj::ObjectHeader::OptEncError optEncError = helloConfig.encode(emptyBuffer);
        BOOST_CHECK(!optEncError);
//        for (int i = 0; i < msgLength; ++i)
//        {
//        	std::cout << std::hex << static_cast<lmp::WORD>(emptySpace[i]) << std::endl;
//        }
        BOOST_CHECK_EQUAL_COLLECTIONS(message,
    		                          message + msgLength,
 		                              emptySpace, emptySpace + msgLength);
	  }
    }
  }
}

BOOST_AUTO_TEST_CASE( hello )
{
  {
	unsigned char message[] =
      { 0x01, 0x07, 0x00, 0x0C,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult headerDecodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(headerDecodingResult.first);
    BOOST_CHECK(!headerDecodingResult.second);
    if (headerDecodingResult.first)
    {
	  const lmp::obj::ObjectHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::Hello);
	  BOOST_CHECK_EQUAL(header.getClassType(), 0x01);
	  lmp::obj::ObjectClassIF<lmp::obj::hello::ClassType>::OptClassType optCType =
	    lmp::obj::ObjectClassIF<lmp::obj::hello::ClassType>::classType_cast(header.getClassType());
	  BOOST_CHECK(optCType);
      if (optCType)
      {
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::hello::ClassType::Hello);
      }
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x0C);
	  lmp::obj::Hello::DecodingResult decodingResult =
		lmp::obj::Hello::decode(header, messageBuffer);
	  if (decodingResult.first)
	  {
		const lmp::obj::Hello& hello = *decodingResult.first;
		BOOST_CHECK_EQUAL(hello.getTxSeqNum(), 0x00000001);
		BOOST_CHECK_EQUAL(hello.getRcvSeqNum(), 0x00000000);
        const lmp::WORD msgLength =
          lmp::obj::ObjectHeader::c_headerLength +
		  lmp::obj::HelloData::getContentsLength();
        unsigned char emptySpace[msgLength];
        boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                            sizeof(message)/sizeof(unsigned char));
        lmp::obj::ObjectHeader::OptEncError optEncError = hello.encode(emptyBuffer);
        BOOST_CHECK(!optEncError);
//        for (int i = 0; i < msgLength; ++i)
//        {
//        	std::cout << std::hex << static_cast<lmp::WORD>(emptySpace[i]) << std::endl;
//        }
        BOOST_CHECK_EQUAL_COLLECTIONS(message,
    		                          message + msgLength,
 		                              emptySpace, emptySpace + msgLength);
	  }
    }
  }
}
#endif

BOOST_AUTO_TEST_SUITE_END()

