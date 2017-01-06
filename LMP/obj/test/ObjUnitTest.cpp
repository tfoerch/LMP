/*
 * ObjUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "obj/LocalCCId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/UnknownCCIdCType.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteNodeId.hpp"
#include "obj/MessageId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/HelloConfig.hpp"
#include "obj/Hello.hpp"
#include "obj/UnknownObjectClass.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>


#define BOOST_TEST_MODULE LMP
#include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( obj )



BOOST_AUTO_TEST_CASE( local_control_channel_id_decode_spirit )
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
   lmp::obj::parse::object_class_grammar<BufIterType,
                                         lmp::obj::ccid::ClassType,
                                         lmp::obj::ccid::ClassType::LocalCCId>  localCcIdGrammar;
   lmp::obj::ccid::LocalCCIdData  localCCId;
   lmp::obj::ccid::LocalCCIdData  expectedLocalCCId = { false, { 0x1020008 } };
   BOOST_CHECK(parse(begin,
                     last,
                     localCcIdGrammar,
                     localCCId));
   BOOST_CHECK_EQUAL(localCCId, expectedLocalCCId);
   // std::cout << msgData << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(localCCId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_grammar<BufOutIterType,
                                            lmp::obj::ccid::ClassType,
                                            lmp::obj::ccid::ClassType::LocalCCId> localCCIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        localCCIdGenerateGrammar,
                        localCCId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( remote_control_channel_id_decode_spirit )
{
   using boost::spirit::qi::parse;
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
   lmp::obj::parse::object_class_grammar<BufIterType,
                                         lmp::obj::ccid::ClassType,
                                         lmp::obj::ccid::ClassType::RemoteCCId>  remoteCcIdGrammar;
   lmp::obj::ccid::RemoteCCIdData  remoteCCId;
   lmp::obj::ccid::RemoteCCIdData  expectedRemoteCCId = { false, { 0x01130a03 } };
   BOOST_CHECK(parse(begin,
                     last,
                     remoteCcIdGrammar,
                     remoteCCId));
   BOOST_CHECK_EQUAL(remoteCCId, expectedRemoteCCId);
   // std::cout << msgData << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(remoteCCId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_grammar<BufOutIterType,
                                            lmp::obj::ccid::ClassType,
                                            lmp::obj::ccid::ClassType::RemoteCCId> remoteCcIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        remoteCcIdGenerateGrammar,
                        remoteCCId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( unknown_control_channel_id_decode_spirit )
{
   using boost::spirit::qi::parse;
   using boost::spirit::karma::generate;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
   unsigned char message[] =
     { 0x07, 0x01, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   boost::asio::const_buffers_1 messageBuffer(message,
                                              sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::object_class_unknown_ctype_grammar<BufIterType,
                                                       lmp::obj::ObjectClass::ControlChannelID>  unknownCcIdGrammar;
   lmp::obj::ccid::UnknownCCIdCTypeData  unknownCCId;
   BOOST_CHECK(parse(begin,
                     last,
                     unknownCcIdGrammar,
                     unknownCCId));
   BOOST_CHECK_EQUAL(unknownCCId.m_class_type, 0x07);
   BOOST_CHECK_EQUAL(unknownCCId.m_negotiable, false);
   BOOST_CHECK_EQUAL(unknownCCId.m_length, 8);
   BOOST_CHECK_EQUAL(unknownCCId.m_data.size(), 4);
   std::cout << unknownCCId << std::endl;
   const lmp::WORD msgLength = unknownCCId.m_length;
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace,
                                              sizeof(emptySpace)/sizeof(unsigned char));
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
//   lmp::obj::ccid::generate::local_control_channel_id_grammar<BufOutIterType> remoteCcIdGenerateGrammar;
   lmp::obj::generate::object_class_unknown_ctype_grammar<BufOutIterType,
                                                          lmp::obj::ObjectClass::ControlChannelID>  unknownCcIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        unknownCcIdGenerateGrammar,
                        unknownCCId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( local_node_id_decode_spirit )
{
  using boost::spirit::qi::parse;
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
   lmp::obj::parse::object_class_grammar<BufIterType,
                                         lmp::obj::nodeid::ClassType,
                                         lmp::obj::nodeid::ClassType::LocalNodeId>    localNodeIdGrammar;
   lmp::obj::nodeid::LocalNodeIdData  localNodeId;
   lmp::obj::nodeid::LocalNodeIdData  expectedLocalNodeId = { false, { 0x1020008 } };
   BOOST_CHECK(parse(begin,
                     last,
                     localNodeIdGrammar,
                     localNodeId));
   BOOST_CHECK_EQUAL(localNodeId, expectedLocalNodeId);
   // std::cout << msgData << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(localNodeId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_grammar<BufOutIterType,
                                            lmp::obj::nodeid::ClassType,
                                            lmp::obj::nodeid::ClassType::LocalNodeId> localNodeIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        localNodeIdGenerateGrammar,
                        localNodeId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

BOOST_AUTO_TEST_CASE( remote_node_id_decode_spirit )
{
  using boost::spirit::qi::parse;
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
   lmp::obj::parse::object_class_grammar<BufIterType,
   		                         lmp::obj::nodeid::ClassType,
   		                         lmp::obj::nodeid::ClassType::RemoteNodeId>  remoteNodeIdGrammar;
   lmp::obj::nodeid::RemoteNodeIdData  remoteNodeId;
   lmp::obj::nodeid::RemoteNodeIdData  expectedRemoteNodeId = { false, { 0x01130a03 } };
   BOOST_CHECK(parse(begin,
                     last,
                     remoteNodeIdGrammar,
                     remoteNodeId));
   BOOST_CHECK_EQUAL(remoteNodeId, expectedRemoteNodeId);
   // std::cout << msgData << std::endl;
   BOOST_CHECK_EQUAL(lmp::obj::getLength(remoteNodeId), msgLength);
   unsigned char emptySpace[msgLength];
   boost::asio::mutable_buffers_1 emptyBuffer(emptySpace, msgLength);
   BufOutIterType  gen_begin = boost::asio::buffers_begin(emptyBuffer);
   BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
   lmp::obj::generate::object_class_grammar<BufOutIterType,
                                            lmp::obj::nodeid::ClassType,
                                            lmp::obj::nodeid::ClassType::RemoteNodeId> remoteNodeIdGenerateGrammar;
   BOOST_CHECK(generate(gen_begin,
                        remoteNodeIdGenerateGrammar,
                        remoteNodeId));
   BOOST_CHECK_EQUAL_COLLECTIONS(message, message + msgLength,
                                 emptySpace, emptySpace + msgLength);
}

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

BOOST_AUTO_TEST_CASE( unknown_object_class_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x01, 0x09, 0x00, 0x0C,
       0x00, 0x00, 0x00, 0x01,
       0x00, 0x00, 0x00, 0x00 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::unknown_object_class_grammar<BufIterType>  unknownObjectClassGrammar;
   lmp::obj::UnknownObjectClassData  unknownObjectClass;
   BOOST_CHECK(parse(begin,
		             last,
					 unknownObjectClassGrammar,
					 unknownObjectClass));
   BOOST_CHECK_EQUAL(unknownObjectClass.m_data.size(), 8);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_object_class, 9);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_class_type, 1);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_length, 12);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_negotiable, false);
   // std::cout << msgData << std::endl;
}

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

