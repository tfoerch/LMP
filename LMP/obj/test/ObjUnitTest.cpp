/*
 * ObjUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeader.hpp"
#include "obj/LocalCCId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteNodeId.hpp"
#include "obj/MessageId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/HelloConfig.hpp"
#include "obj/Hello.hpp"
#include <boost/asio/buffer.hpp>
#include <iostream>


#define BOOST_TEST_MODULE LMP
#include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( obj )

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
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::ccid::LocalCCId);
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
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::ccid::RemoteCCId);
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
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::nodeid::LocalNodeId);
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
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::nodeid::RemoteNodeId);
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
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::msgid::MessageId);
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
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::msgid::MessageIdAck);
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
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::config::HelloConfig);
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
    	BOOST_CHECK_EQUAL(*optCType, lmp::obj::hello::Hello);
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

