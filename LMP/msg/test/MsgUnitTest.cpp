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
#include "msg/MsgParseGrammar.hpp"
#include "msg/Message.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffers_iterator.hpp>

#include <type_traits>
#include <iomanip>

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

#if 0
namespace lmp
{
  namespace msg
  {
    namespace parse
	{
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;
    namespace qi = boost::spirit::qi;
    template <typename Iterator>
    struct object_grammar : qi::grammar<Iterator, UnknownObject()>
    {
      object_grammar() : object_grammar::base_type(unknown_object, "unknown_object")
      {
    	using qi::big_word;
    	using qi::big_dword;
    	using qi::byte_;
    	using qi::repeat;
        using qi::eps;
        using qi::lazy;
        using qi::_a;
        using qi::_1;
    	using phoenix::at_c;
        using phoenix::push_back;
    	using namespace qi::labels;


        control_channel_object_class =
				byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::ControlChannelID));

        unknown_ccid_ctype =
				byte_  [ at_c<1>(_val) = _1 ] // c-type
				>> control_channel_object_class
				>> big_word [ at_c<2>(_val) = _1 ] // length
				>> byte_sequence( at_c<2>(_val) - 4 ) [ at_c<3>(_val) = _1 ];

        local_ccid =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> control_channel_object_class
				>> big_word   // length
		        >> big_dword [ at_c<1>(_val) = _1 ];

        remote_ccid =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> control_channel_object_class
				>> big_word // length
		        >> big_dword [ at_c<1>(_val) = _1 ];

        control_channel_id_object %=
    			local_ccid |
				remote_ccid |
				unknown_ccid_ctype;

        message_id_object_class =
				byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::MessageID));

	    message_id =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> message_id_object_class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

	    message_id_ack =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> message_id_object_class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

        unknown_message_id_ctype =
				byte_  [ at_c<1>(_val) = _1 ] // c-type
				>> message_id_object_class
				>> big_word [ at_c<2>(_val) = _1 ] // length
				>> byte_sequence( at_c<2>(_val) - 4 ) [ at_c<3>(_val) = _1 ];

        message_id_object %=
      		    message_id |
				message_id_ack|
				unknown_message_id_ctype;

        node_id_object_class =
				byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::NodeID));

		local_node_id =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> node_id_object_class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

		remote_node_id =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> node_id_object_class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

        unknown_node_id_ctype =
				byte_ [ at_c<1>(_val) = _1 ] // c-type
				>> node_id_object_class
				>> big_word [ at_c<2>(_val) = _1 ] // length
				>> byte_sequence( at_c<2>(_val) - 4 ) [ at_c<3>(_val) = _1 ];

        node_id_object %=
      		    local_node_id |
				remote_node_id |
				unknown_node_id_ctype;

        config_object_class =
			    byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::Config));

		hello_config =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> config_object_class
				>> big_word // length
				>> big_word [ at_c<1>(_val) = _1 ]
				>> big_word [ at_c<2>(_val) = _1 ];

        unknown_config_ctype =
				byte_ [ at_c<1>(_val) = _1 ] // c-type
				>> config_object_class
				>> big_word [ at_c<2>(_val) = _1 ] // length
				>> byte_sequence( at_c<2>(_val) - 4 ) [ at_c<3>(_val) = _1 ];

        config_object %=
      		hello_config |
				unknown_config_ctype;

		byte_sequence =
				( eps(_r1 > 1) [ std::cout << _r1 << std::endl ]
				  >> byte_sequence(_r1 - 1) [ _val = _1 ]
				  >> byte_ [ push_back(_val, _1) ] ) |
				byte_ [ push_back(_val, _1) ];

		unknown_object =
				byte_  [ at_c<1>(_val) = _1 ] // c-type
				>> byte_ [ at_c<2>(_val) = _1 ] // object class
				>> big_word [ at_c<3>(_val) = _1 ] // length
				>> byte_sequence( (at_c<3>(_val) - 4) ) [ at_c<4>(_val) = _1 ];
				// >> repeat(4)[byte_] [ at_c<4>(_val) = _1 ]; //[ push_back(at_c<4>(_val), phoenix::static_cast_<lmp::BYTE>(_1)) ]; // [ Sniffer() ];

    	objects %=
    			control_channel_id_object |
				message_id_object |
				node_id_object |
				config_object |
				( unknown_object [ std::cout << _1 << std::endl ] );


        local_ccid.name("local_ccid_object");
        remote_ccid.name("remote_ccid_object");
        message_id.name("message_id_object");
        message_id_ack.name("message_id_ack_object");
        local_node_id.name("local_node_id_object");
        remote_node_id.name("remote_node_id_object");
        hello_config.name("hello_config_object");
      }
      qi::rule<Iterator> control_channel_object_class;
      qi::rule<Iterator, LocalCCIdData()>     local_ccid;
      qi::rule<Iterator, RemoteCCIdData()>    remote_ccid;
      qi::rule<Iterator, UnknownCCIdCTypeData()>      unknown_ccid_ctype;
      qi::rule<Iterator, ControlChannelIdVariants()>  control_channel_id_object;
      qi::rule<Iterator> message_id_object_class;
      qi::rule<Iterator, MessageIdData()>     message_id;
      qi::rule<Iterator, MessageIdAckData()>  message_id_ack;
      qi::rule<Iterator, UnknownMessageIdCTypeData()>  unknown_message_id_ctype;
      qi::rule<Iterator, MessageIdVariants()>        message_id_object;
      qi::rule<Iterator> node_id_object_class;
      qi::rule<Iterator, LocalNodeIdData()>         local_node_id;
      qi::rule<Iterator, RemoteNodeIdData()>        remote_node_id;
      qi::rule<Iterator, UnknownNodeIdCTypeData()>  unknown_node_id_ctype;
      qi::rule<Iterator, NodeIdVariants()>          node_id_object;
      qi::rule<Iterator> config_object_class;
      qi::rule<Iterator, HelloConfig()>       hello_config;
      qi::rule<Iterator, UnknownConfigCTypeData()>  unknown_config_ctype;
      qi::rule<Iterator, ConfigVariants()>          config_object;
      qi::rule<Iterator, std::vector<lmp::BYTE>(lmp::WORD)>  byte_sequence;
      qi::rule<Iterator, UnknownObject()>     unknown_object;
      qi::rule<Iterator, ObjectVariants()>    objects;
    };
    } // namespace parse
  } // namespace msg
} // namespace lmp
#endif

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

BOOST_AUTO_TEST_CASE( config_message_spirit )
{
  {
    using boost::spirit::qi::parse;

    typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
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
	boost::asio::const_buffers_1 messageBuffer(message,
                                               sizeof(message)/sizeof(unsigned char));
	BufIterType begin = boost::asio::buffers_begin(messageBuffer);
	BufIterType last = boost::asio::buffers_end(messageBuffer);
	lmp::msg::parse::message_grammar<BufIterType>  msgGrammar;
	lmp::msg::parse::MsgData msgData;
	BOOST_CHECK(parse(begin,
		              last,
					  msgGrammar,
					  msgData));
	std::cout << msgData << std::endl;
	// BOOST_CHECK_EQUAL(msgData.m_type, lmp::msg::parse::MsgType::Config);
	// std::cout << static_cast<lmp::WORD>(msgData.m_type) << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( unknown_message_spirit )
{
  {
    using boost::spirit::qi::parse;

    typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
	unsigned char message[] =
    { 0x10, 0x00, 0x00, 0x04, // <Common Header>
      0x00, 0x28, 0x00, 0x00,
	  0x01, 0x01, 0x00, 0x08, // <LOCAL_CCID>
      0x01, 0x02, 0x00, 0x08,
	  0x01, 0x05, 0x00, 0x08, // <MESSAGE_ID>
      0x01, 0x02, 0x05, 0x08,
	  0x01, 0x02, 0x00, 0x08, // <LOCAL_NODE_ID>
	  0x01, 0x02, 0x05, 0x08,
	  0x81, 0x08, 0x00, 0x08, // <CONFIG> = HelloConfig
	  0x01, 0x9A, 0x03, 0xCF };
	boost::asio::const_buffers_1 messageBuffer(message,
                                               sizeof(message)/sizeof(unsigned char));
	BufIterType begin = boost::asio::buffers_begin(messageBuffer);
	BufIterType last = boost::asio::buffers_end(messageBuffer);
	lmp::msg::parse::message_grammar<BufIterType>  msgGrammar;
	lmp::msg::parse::MsgData msgData;
	BOOST_CHECK(parse(begin,
		              last,
					  msgGrammar,
					  msgData));
	std::cout << msgData << std::endl;
	// BOOST_CHECK_EQUAL(msgData.m_type, lmp::msg::parse::MsgType::Config);
	// std::cout << static_cast<lmp::WORD>(msgData.m_type) << std::endl;
  }
}

#if 0
BOOST_AUTO_TEST_CASE( unknown_object_spirit )
{
  {
    using boost::spirit::qi::parse;

    typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
	unsigned char message[] =
    { 0x81, 0x08, 0x00, 0x08, // <CONFIG> = HelloConfig
	  0x00, 0x9A, 0x01, 0xCF };
	boost::asio::const_buffers_1 messageBuffer(message,
                                               sizeof(message)/sizeof(unsigned char));
	BufIterType begin = boost::asio::buffers_begin(messageBuffer);
	BufIterType last = boost::asio::buffers_end(messageBuffer);
	lmp::msg::parse::object_grammar<BufIterType>  objGrammar;
	lmp::msg::parse::UnknownObject objData;
	BOOST_CHECK(parse(begin,
		              last,
					  objGrammar,
					  objData));
	std::cout << objData << std::endl;
	// BOOST_CHECK_EQUAL(msgData.m_type, lmp::msg::parse::MsgType::Config);
	// std::cout << static_cast<lmp::WORD>(msgData.m_type) << std::endl;
  }
}
#endif

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
	lmp::msg::parse::message_grammar<BufIterType>  msgGrammar;
	lmp::msg::parse::MsgData msgData;
	BOOST_CHECK(!parse(begin,
			           last,
					   msgGrammar,
					   msgData));

  }
}

BOOST_AUTO_TEST_SUITE_END()

