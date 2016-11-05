/*
 * ObjUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeader.hpp"
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

BOOST_AUTO_TEST_CASE( obj_class_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] = { 0x01 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::parse::control_channel_id_object_class_grammar<BufIterType>  ccidGrammar;
   lmp::obj::ObjectClass  objClass;
   BOOST_CHECK(parse(begin,
		             last,
					 ccidGrammar,
					 objClass));
   BOOST_CHECK_EQUAL(objClass, lmp::obj::ObjectClass::ControlChannelID);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( local_control_channel_id_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x01, 0x01, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::ccid::parse::local_control_channel_id_grammar<BufIterType>  localCcIdGrammar;
   lmp::obj::ccid::LocalCCIdData  localCCId;
   BOOST_CHECK(parse(begin,
		             last,
					 localCcIdGrammar,
					 localCCId));
   BOOST_CHECK_EQUAL(localCCId.m_CCId, 0x1020008);
   BOOST_CHECK_EQUAL(localCCId.m_negotiable, false);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( remote_control_channel_id_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x02, 0x01, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::ccid::parse::remote_control_channel_id_grammar<BufIterType>  remoteCcIdGrammar;
   lmp::obj::ccid::RemoteCCIdData  remoteCCId;
   BOOST_CHECK(parse(begin,
		             last,
					 remoteCcIdGrammar,
					 remoteCCId));
   BOOST_CHECK_EQUAL(remoteCCId.m_CCId, 0x01130a03);
   BOOST_CHECK_EQUAL(remoteCCId.m_negotiable, false);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( unknown_control_channel_id_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x07, 0x01, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::ccid::parse::unknown_control_channel_id_grammar<BufIterType>  unknownCcIdGrammar;
   lmp::obj::ccid::UnknownCCIdCTypeData  unknownCCId;
   BOOST_CHECK(parse(begin,
		             last,
					 unknownCcIdGrammar,
					 unknownCCId));
   BOOST_CHECK_EQUAL(unknownCCId.m_header.m_class_type, 0x07);
   BOOST_CHECK_EQUAL(unknownCCId.m_header.m_negotiable, false);
   BOOST_CHECK_EQUAL(unknownCCId.m_header.m_length, 8);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( local_node_id_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x01, 0x02, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::nodeid::parse::local_node_id_grammar<BufIterType>  localNodeIdGrammar;
   lmp::obj::nodeid::LocalNodeIdData  localNodeId;
   BOOST_CHECK(parse(begin,
		             last,
					 localNodeIdGrammar,
					 localNodeId));
   BOOST_CHECK_EQUAL(localNodeId.m_nodeId, 0x1020008);
   BOOST_CHECK_EQUAL(localNodeId.m_negotiable, false);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( remote_node_id_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x02, 0x02, 0x00, 0x08,
       0x01, 0x13, 0x0a, 0x03 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::nodeid::parse::remote_node_id_grammar<BufIterType>  remoteNodeIdGrammar;
   lmp::obj::nodeid::RemoteNodeIdData  remoteNodeId;
   BOOST_CHECK(parse(begin,
		             last,
					 remoteNodeIdGrammar,
					 remoteNodeId));
   BOOST_CHECK_EQUAL(remoteNodeId.m_nodeId, 0x01130a03);
   BOOST_CHECK_EQUAL(remoteNodeId.m_negotiable, false);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( message_id_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x01, 0x05, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::msgid::parse::message_id_grammar<BufIterType>  messageIdGrammar;
   lmp::obj::msgid::MessageIdData  messageId;
   BOOST_CHECK(parse(begin,
		             last,
					 messageIdGrammar,
					 messageId));
   BOOST_CHECK_EQUAL(messageId.m_messageId, 0x1020008);
   BOOST_CHECK_EQUAL(messageId.m_negotiable, false);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( message_id_ack_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x02, 0x05, 0x00, 0x08,
       0x01, 0x02, 0x00, 0x08 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::msgid::parse::message_id_ack_grammar<BufIterType>  messageIdAckGrammar;
   lmp::obj::msgid::MessageIdAckData  messageIdAck;
   BOOST_CHECK(parse(begin,
		             last,
					 messageIdAckGrammar,
					 messageIdAck));
   BOOST_CHECK_EQUAL(messageIdAck.m_messageId, 0x1020008);
   BOOST_CHECK_EQUAL(messageIdAck.m_negotiable, false);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( hello_config_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x81, 0x06, 0x00, 0x08,
       0x00, 0x9A, 0x01, 0xCF };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::config::parse::hello_config_grammar<BufIterType>  helloConfigGrammar;
   lmp::obj::config::HelloConfigData  helloConfig;
   BOOST_CHECK(parse(begin,
		             last,
					 helloConfigGrammar,
					 helloConfig));
   BOOST_CHECK_EQUAL(helloConfig.m_helloIntv, 0x009A);
   BOOST_CHECK_EQUAL(helloConfig.m_helloDeadIntv, 0x01CF);
   BOOST_CHECK_EQUAL(helloConfig.m_negotiable, true);
   // std::cout << msgData << std::endl;
}

BOOST_AUTO_TEST_CASE( hello_decode_spirit )
{
   using boost::spirit::qi::parse;

   typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
   unsigned char message[] =
     { 0x01, 0x07, 0x00, 0x0C,
       0x00, 0x00, 0x00, 0x01,
       0x00, 0x00, 0x00, 0x00 };
   boost::asio::const_buffers_1 messageBuffer(message,
		                                      sizeof(message)/sizeof(unsigned char));
   BufIterType begin = boost::asio::buffers_begin(messageBuffer);
   BufIterType last = boost::asio::buffers_end(messageBuffer);
   lmp::obj::hello::parse::hello_grammar<BufIterType>  helloGrammar;
   lmp::obj::hello::HelloData  hello;
   BOOST_CHECK(parse(begin,
		             last,
					 helloGrammar,
					 hello));
   BOOST_CHECK_EQUAL(hello.m_txSeqNum, 0x00000001);
   BOOST_CHECK_EQUAL(hello.m_rcvSeqNum, 0x00000000);
   BOOST_CHECK_EQUAL(hello.m_negotiable, false);
   // std::cout << msgData << std::endl;
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
   BOOST_CHECK_EQUAL(unknownObjectClass.m_header.m_object_class, 9);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_header.m_class_type, 1);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_header.m_length, 12);
   BOOST_CHECK_EQUAL(unknownObjectClass.m_header.m_negotiable, false);
   // std::cout << msgData << std::endl;
}


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


BOOST_AUTO_TEST_SUITE_END()

