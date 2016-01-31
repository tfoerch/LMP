/*
 * ObjUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "msg/CommonHeader.hpp"
#include <boost/asio/buffer.hpp>


#define BOOST_TEST_MODULE LMP
#include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( msg )

BOOST_AUTO_TEST_CASE( msg_header_decode )
{
  {
	unsigned char message[] =
      { 0x10, 0x00, 0x00, 0x01 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::msg::CommonHeader::DecodingResult decodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::msg::CommonHeader::invalid_length);
    }
  }
  {
	unsigned char message[] =
    { 0x20, 0x00, 0x00, 0x01,
      0x00, 0x20, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::msg::CommonHeader::DecodingResult decodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::msg::CommonHeader::not_supported_version);
    }
  }
  {
	unsigned char message[] =
    { 0x10, 0x00, 0x00, 0x38,
      0x00, 0x20, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::msg::CommonHeader::DecodingResult decodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::msg::CommonHeader::not_supported_msgType);
    }
  }
  {
	unsigned char message[] =
      { 0x10, 0x00, 0x00, 0x01,
        0x00, 0x20, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::msg::CommonHeader::DecodingResult decodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(decodingResult.first);
    BOOST_CHECK(!decodingResult.second);
    if (decodingResult.first)
    {
	  const lmp::msg::CommonHeader& header = *decodingResult.first;
	  BOOST_CHECK_EQUAL(header.getVersion(), static_cast<lmp::BYTE>(1));
	  BOOST_CHECK_EQUAL(header.isControlChannelDown(), false);
	  BOOST_CHECK_EQUAL(header.isLmpRestart(), false);
	  BOOST_CHECK_EQUAL(header.getMsgType(), lmp::msg::mtype::Config);
	  BOOST_CHECK_EQUAL(header.getLmpLength(), 0x20);
	  unsigned char emptySpace[lmp::msg::CommonHeader::c_headerLength];
	  boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                          sizeof(message)/sizeof(unsigned char));
	  lmp::msg::CommonHeader::OptEncError optEncError = header.encode(emptyBuffer);
	  BOOST_CHECK(!optEncError);
	  BOOST_CHECK_EQUAL_COLLECTIONS(message, message + lmp::msg::CommonHeader::c_headerLength,
			                        emptySpace, emptySpace + lmp::msg::CommonHeader::c_headerLength);
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

