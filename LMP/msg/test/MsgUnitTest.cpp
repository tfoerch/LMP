/*
 * ObjUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "msg/CommonHeader.hpp"
#include "msg/Config.hpp"
#include "msg/ConfigAck.hpp"
#include "msg/ConfigNack.hpp"
#include "msg/Hello.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#define BOOST_TEST_MODULE LMP
#include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>


template <typename ConstBuffers>
size_t parseDocument(ConstBuffers const& buffers, int &data)
{
  boost::asio::buffers_iterator<ConstBuffers> begin = boost::asio::buffers_begin(buffers);
  boost::asio::buffers_iterator<ConstBuffers> last = boost::asio::buffers_end(buffers);
  boost::asio::buffers_iterator<ConstBuffers> first = begin;

  lmp::BYTE  versByte;
  lmp::BYTE  msgTypeByte;
  lmp::WORD  msgLength;

  using boost::spirit::qi::big_word;
  using boost::spirit::qi::big_dword;
  using boost::spirit::qi::byte_;
  using boost::spirit::qi::_1;
  using boost::spirit::qi::parse;
  using boost::phoenix::ref;
  return
	( parse(first,
			last,
			//  Begin grammar
			(
			     byte_[ref(versByte) = _1]
	          >> byte_[ref(msgTypeByte) = _1]
              >> big_word[ref(msgLength) = _1]
			),
			//  End grammar
			data) ?
      (first - begin) :
	  0 ); // only optionally consume
}

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    ///////////////////////////////////////////////////////////////////////////////
    //  Our nabialek_trick grammar
    ///////////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    struct nabialek_trick : qi::grammar<
        Iterator, ascii::space_type, qi::locals<qi::rule<Iterator, ascii::space_type>*> >
    {
        nabialek_trick() : nabialek_trick::base_type(start)
        {
            using ascii::alnum;
            using qi::lexeme;
            using qi::lazy;
            using qi::_a;
            using qi::_1;

            id = lexeme[*(ascii::alnum | '_')];
            one = id;
            two = id >> ',' >> id;

            keyword.add
                ("one", &one)
                ("two", &two)
                ;

            start = *(keyword[_a = _1] >> lazy(*_a));
        }

        qi::rule<Iterator, ascii::space_type> id, one, two;
        qi::rule<Iterator, ascii::space_type, qi::locals<qi::rule<Iterator, ascii::space_type>*> > start;
        qi::symbols<char, qi::rule<Iterator, ascii::space_type>*> keyword;
    };
}

namespace lmp
{
  namespace parse
  {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    template <typename Iterator>
    struct message_grammar : qi::grammar<Iterator>
    {
      message_grammar() : message_grammar::base_type(start)
      {
    	using qi::big_word;
    	using qi::big_dword;
    	using qi::byte_;
        using ascii::alnum;
        using qi::lexeme;
        using qi::lazy;
        using qi::_a;
        using qi::_1;
        // 0x10, 0x00, 0x00, 0x01, // <Common Header>
        // 0x00, 0x28, 0x00, 0x00,

	    config_msg =  '\x10' >> byte_ >> byte_ >> '\x01' >> big_word >> byte_ >> byte_;

        start = config_msg;
      }
      qi::rule<Iterator> config_msg;
      qi::rule<Iterator> start;
    };
  } // namespace parse
} // namespace lmp


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

BOOST_AUTO_TEST_CASE( config )
{
  {
	unsigned char message[] =
      { 0x10, 0x00, 0x00, 0x01, // <Common Header>
        0x00, 0x28, 0x00, 0x00,
	    0x01, 0x01, 0x00, 0x08, // <LOCAL_CCID>
        0x01, 0x02, 0x00, 0x08,
		0x01, 0x05, 0x00, 0x08, // <MESSAGE_ID>
        0x01, 0x02, 0x05, 0x08,
		0x01, 0x02, 0x00, 0x08, // <LOCAL_NODE_ID>
		0x01, 0x02, 0x05, 0x08,
		0x81, 0x06, 0x00, 0x08, // <CONFIG> = HelloConfig
		0x00, 0x9A, 0x01, 0xCF };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
	boost::asio::streambuf strbuf;
	boost::asio::streambuf::mutable_buffers_type bufs = strbuf.prepare(1024);
	size_t numBytes = boost::asio::buffer_copy(bufs, messageBuffer);
	strbuf.commit(numBytes);
    lmp::msg::CommonHeader::DecodingResult headerDecodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(headerDecodingResult.first);
    BOOST_CHECK(!headerDecodingResult.second);
    if (headerDecodingResult.first)
    {
	  const lmp::msg::CommonHeader& header = *headerDecodingResult.first;
	  BOOST_CHECK_EQUAL(header.getVersion(), static_cast<lmp::BYTE>(1));
	  BOOST_CHECK_EQUAL(header.isControlChannelDown(), false);
	  BOOST_CHECK_EQUAL(header.isLmpRestart(), false);
	  BOOST_CHECK_EQUAL(header.getMsgType(), lmp::msg::mtype::Config);
	  BOOST_CHECK_EQUAL(header.getLmpLength(), 0x28);
	  lmp::msg::Config::DecodingResult decodingResult =
	    lmp::msg::Config::decode(header, messageBuffer);
	  BOOST_CHECK(decodingResult.first);
	  BOOST_CHECK(!decodingResult.second);
	  if (decodingResult.first)
	  {
		const lmp::msg::Config& configMsg = *decodingResult.first;
		BOOST_CHECK_EQUAL(configMsg.getLocalCCId().getControlChannelId(), 0x1020008);
		BOOST_CHECK_EQUAL(configMsg.getMessageId().getMessageId(), 0x1020508);
		BOOST_CHECK_EQUAL(configMsg.getLocalNodeId().getNodeId(), 0x1020508);
		BOOST_CHECK_EQUAL(configMsg.getHelloConfig().getHelloIntv(), 0x009A);
		BOOST_CHECK_EQUAL(configMsg.getHelloConfig().getHelloDeadIntv(), 0x01CF);
	  }
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

BOOST_AUTO_TEST_CASE( config_header_spirit )
{
  {
    using boost::spirit::qi::parse;

    typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
	unsigned char message[] =
      { 0x10, 0x00, 0x00, 0x01, // <Common Header>
        0x00, 0x28, 0x00, 0x00 };
	boost::asio::const_buffers_1 messageBuffer(message,
                                               sizeof(message)/sizeof(unsigned char));
	BufIterType begin = boost::asio::buffers_begin(messageBuffer);
	BufIterType last = boost::asio::buffers_end(messageBuffer);
	lmp::parse::message_grammar<BufIterType>  msgGrammar;
	BOOST_CHECK(parse(begin,
		              last,
					  msgGrammar));

  }
}

BOOST_AUTO_TEST_CASE( unknown_msg_type_header_spirit )
{
  {
    using boost::spirit::qi::parse;

    typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
	unsigned char message[] =
      { 0x10, 0x00, 0x00, 0x45, // <Common Header>
        0x00, 0x28, 0x00, 0x00 };
	boost::asio::const_buffers_1 messageBuffer(message,
                                               sizeof(message)/sizeof(unsigned char));
	BufIterType begin = boost::asio::buffers_begin(messageBuffer);
	BufIterType last = boost::asio::buffers_end(messageBuffer);
	lmp::parse::message_grammar<BufIterType>  msgGrammar;
	BOOST_CHECK(!parse(begin,
			           last,
					   msgGrammar));

  }
}

BOOST_AUTO_TEST_SUITE_END()

