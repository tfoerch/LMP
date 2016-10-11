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
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

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


namespace lmp
{
  namespace parse
  {
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;
    namespace qi = boost::spirit::qi;
    enum class MsgType : lmp::BYTE { Config = 1, ConfigAck = 2, ConfigNack = 3 };
    struct Objects
    {
    };
    struct LocalCCIdValues
    {
	  bool        m_negotiatable;
	  lmp::DWORD  m_CCId;
    };
    std::ostream& operator<<(std::ostream& os, const LocalCCIdValues& localCCId)
    {
      os << localCCId.m_CCId;
      return os;
    }
    struct RemoteCCIdValues
    {
	  bool        m_negotiatable;
	  lmp::DWORD  m_CCId;
    };
    std::ostream& operator<<(std::ostream& os, const RemoteCCIdValues& remoteCCId)
    {
      os << remoteCCId.m_CCId;
      return os;
    }
   struct MessageIdValues
    {
      bool        m_negotiatable;
      lmp::DWORD  m_messageId;
    };
    std::ostream& operator<<(std::ostream& os, const MessageIdValues& messageId)
    {
      os << messageId.m_messageId;
      return os;
    }
    struct MessageIdAckValues
    {
      bool        m_negotiatable;
      lmp::DWORD  m_messageId;
    };
    std::ostream& operator<<(std::ostream& os, const MessageIdAckValues& messageAckId)
    {
      os << messageAckId.m_messageId;
      return os;
    }
    struct LocalNodeIdValues
    {
	   bool        m_negotiatable;
	   lmp::DWORD  m_nodeId;
    };
    std::ostream& operator<<(std::ostream& os, const LocalNodeIdValues& nodeId)
    {
      os << nodeId.m_nodeId;
      return os;
    }
    struct RemoteNodeIdValues
    {
	   bool        m_negotiatable;
	   lmp::DWORD  m_nodeId;
    };
    std::ostream& operator<<(std::ostream& os, const RemoteNodeIdValues& nodeId)
    {
      os << nodeId.m_nodeId;
      return os;
    }
    struct HelloConfig
    {
	   bool        m_negotiatable;
	   lmp::WORD   m_helloIntv;
	   lmp::WORD   m_helloDeadIntv;
    };
    std::ostream& operator<<(std::ostream& os, const HelloConfig& helloConfig)
    {
      os << helloConfig.m_helloIntv << ", " << helloConfig.m_helloDeadIntv;
      return os;
    }
    struct ConfigMsgValues
	{
      LocalCCIdValues    m_localCCId;
      MessageIdValues    m_messageId;
      LocalNodeIdValues  m_localNodeId;
      HelloConfig        m_helloConfig;
	};
    std::ostream& operator<<(
      std::ostream&          os,
	  const ConfigMsgValues& config)
    {
      std::cout << "ConfigMsg(" << config.m_localCCId
    			<< ", " << config.m_messageId
				<< ", " << config.m_localNodeId
				<< ", " << config.m_helloConfig
				<< ")";
      return os;
    }
    struct ConfigAckMsgValues
	{
      LocalCCIdValues     m_localCCId;
      LocalNodeIdValues   m_localNodeId;
      RemoteCCIdValues    m_remoteCCId;
      MessageIdAckValues  m_messageId;
      RemoteNodeIdValues  m_remoteNodeId;
	};
    std::ostream& operator<<(
      std::ostream&             os,
	  const ConfigAckMsgValues& configAck)
    {
      std::cout << "ConfigAckMsg(" << configAck.m_localCCId
				<< ", " << configAck.m_localNodeId
				<< ", " << configAck.m_remoteCCId
  			    << ", " << configAck.m_messageId
				<< ", " << configAck.m_remoteNodeId
				<< ")";
      return os;
    }
    struct ConfigNackMsgValues
	{
      LocalCCIdValues     m_localCCId;
      LocalNodeIdValues   m_localNodeId;
      RemoteCCIdValues    m_remoteCCId;
      MessageIdAckValues  m_messageId;
      RemoteNodeIdValues  m_remoteNodeId;
      HelloConfig         m_helloConfig;
	};
    std::ostream& operator<<(
      std::ostream&          os,
	  const ConfigNackMsgValues& configNack)
    {
      std::cout << "ConfigNackMsg(" << configNack.m_localCCId
				<< ", " << configNack.m_localNodeId
				<< ", " << configNack.m_remoteCCId
			    << ", " << configNack.m_messageId
				<< ", " << configNack.m_remoteNodeId
				<< ", " << configNack.m_helloConfig
				<< ")";
      return os;
    }
    typedef
      boost::variant<ConfigMsgValues,
					 ConfigAckMsgValues,
					 ConfigNackMsgValues>
    MsgVariants;
    struct MsgValues
    {
      lmp::BYTE             m_flags;
      MsgVariants           m_message;
    };
  }
}

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::LocalCCIdValues,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_CCId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::RemoteCCIdValues,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_CCId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::MessageIdValues,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_messageId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::MessageIdAckValues,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_messageId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::LocalNodeIdValues,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_nodeId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::RemoteNodeIdValues,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_nodeId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::HelloConfig,
  (bool,       m_negotiatable)
  (lmp::WORD,  m_helloIntv)
  (lmp::WORD,  m_helloDeadIntv)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::ConfigMsgValues,
  (lmp::parse::LocalCCIdValues,       m_localCCId)
  (lmp::parse::MessageIdValues,       m_messageId)
  (lmp::parse::LocalNodeIdValues,     m_localNodeId)
  (lmp::parse::HelloConfig,           m_helloConfig)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::ConfigAckMsgValues,
  (lmp::parse::LocalCCIdValues,       m_localCCId)
  (lmp::parse::LocalNodeIdValues,     m_localNodeId)
  (lmp::parse::RemoteCCIdValues,      m_remoteCCId)
  (lmp::parse::MessageIdAckValues,    m_messageId)
  (lmp::parse::RemoteNodeIdValues,    m_remoteNodeId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::ConfigNackMsgValues,
  (lmp::parse::LocalCCIdValues,       m_localCCId)
  (lmp::parse::LocalNodeIdValues,     m_localNodeId)
  (lmp::parse::RemoteCCIdValues,      m_remoteCCId)
  (lmp::parse::MessageIdAckValues,    m_messageId)
  (lmp::parse::RemoteNodeIdValues,    m_remoteNodeId)
  (lmp::parse::HelloConfig,           m_helloConfig)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::parse::MsgValues,
  (lmp::BYTE,                         m_flags)
  (lmp::parse::MsgVariants,           m_message)
)

namespace lmp
{
  namespace parse
  {
    struct msg_variants_printer : boost::static_visitor<>
    {
      void operator()(const ConfigMsgValues& config) const
      {
    	std::cout << config << std::endl;
      }
      void operator()(const ConfigAckMsgValues& configAck) const
      {
    	std::cout << configAck << std::endl;
      }
      void operator()(const ConfigNackMsgValues& configNack) const
      {
    	std::cout << configNack << std::endl;
      }
    };
    struct msg_values_printer
    {
      void operator()(const MsgValues& msgValues) const
      {
    	boost::apply_visitor(msg_variants_printer(), msgValues.m_message);
      }
    };
    struct print_action
    {
        void operator()(lmp::DWORD const& i, qi::unused_type, qi::unused_type) const
        {
            std::cout << i << std::endl;
        }
    };
    template <typename Iterator>
    struct message_grammar : qi::grammar<Iterator, MsgValues()>
    {
      message_grammar() : message_grammar::base_type(message)
      {
    	using qi::big_word;
    	using qi::big_dword;
    	using qi::byte_;
        using qi::lazy;
        using qi::_a;
        using qi::_1;
    	using phoenix::at_c;
    	using namespace qi::labels;
       // 0x10, 0x00, 0x00, 0x01, // <Common Header>
        // 0x00, 0x28, 0x00, 0x00,


    	vers_flags =
    			   byte_(0x10) // version
	    		>> byte_ [_val = _1]
	            >> byte_; // reserved

    	msg_length =
				   big_word [_val = _1]
				>> big_word;  // reserved

		local_ccid =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(0x01) // class
				>> big_word // length
		        >> big_dword [ at_c<1>(_val) = _1 ];

		remote_ccid =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(0x01) // class
				>> big_word // length
		        >> big_dword [ at_c<1>(_val) = _1 ];

	    message_id =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(0x05) // class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

	    message_id_ack =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(0x05) // class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

		local_node_id =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(0x02) // class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

		remote_node_id =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(0x02) // class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

		hello_config =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(0x06) // class
				>> big_word // length
				>> big_word [ at_c<1>(_val) = _1 ]
				>> big_word [ at_c<2>(_val) = _1 ];

   	    config_body %=
   	    		local_ccid
				>> message_id
				>> local_node_id
				>> hello_config;
//   	    config_body =
//   	    		local_ccid [ at_c<0>(_val) = _1 ]
//				>> message_id [ at_c<1>(_val) = _1 ]
//				>> local_node_id [ at_c<2>(_val) = _1 ]
//				>> hello_config [ at_c<3>(_val) = _1 ];

    	config_ack_body %=
   	    		local_ccid
				>> local_node_id
				>> remote_ccid
				>> message_id_ack
				>> remote_node_id;

    	config_nack_body %=
   	    		local_ccid
				>> local_node_id
				>> remote_ccid
    			>> message_id_ack
				>> remote_node_id
				>> hello_config;

    	config_msg =
    			byte_(0x01)
				>> msg_length [_a = _1]
				>> config_body(_a) [ _val = _1 ]; //[ std::cout << _1 << std::endl ];

    	config_ack_msg =
    			byte_(0x02)
				>> msg_length [_a = _1]
			    >> config_ack_body(_a) [ _val = _1 ];
    	config_nack_msg =
    			byte_(0x03)
				>> msg_length [_a = _1]
			    >> config_nack_body(_a) [ _val = _1 ];

	    msg_type_and_bodies %=
	    	    config_msg |
	    	    config_ack_msg |
				config_nack_msg;

        message %=
        		vers_flags
				>> msg_type_and_bodies;
      }
      qi::rule<Iterator, lmp::BYTE()> vers_flags;
      qi::rule<Iterator, lmp::WORD()> msg_length;
      qi::rule<Iterator, LocalCCIdValues()>     local_ccid;
      qi::rule<Iterator, RemoteCCIdValues()>    remote_ccid;
      qi::rule<Iterator, MessageIdValues()>     message_id;
      qi::rule<Iterator, MessageIdAckValues()>  message_id_ack;
      qi::rule<Iterator, LocalNodeIdValues()>   local_node_id;
      qi::rule<Iterator, RemoteNodeIdValues()>  remote_node_id;
      qi::rule<Iterator, HelloConfig()>         hello_config;
      qi::rule<Iterator, ConfigMsgValues(lmp::WORD)>      config_body;
      qi::rule<Iterator, ConfigAckMsgValues(lmp::WORD)>   config_ack_body;
      qi::rule<Iterator, ConfigNackMsgValues(lmp::WORD)>  config_nack_body;
      qi::rule<Iterator, ConfigMsgValues(),     qi::locals<lmp::WORD>>  config_msg;
      qi::rule<Iterator, ConfigAckMsgValues(),  qi::locals<lmp::WORD>>  config_ack_msg;
      qi::rule<Iterator, ConfigNackMsgValues(), qi::locals<lmp::WORD>>  config_nack_msg;
      qi::rule<Iterator, MsgVariants()>   msg_type_and_bodies;
      qi::rule<Iterator, MsgValues()>     message;
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
	lmp::parse::message_grammar<BufIterType>  msgGrammar;
	lmp::parse::MsgValues msgValues;
	BOOST_CHECK(parse(begin,
		              last,
					  msgGrammar,
					  msgValues));
	lmp::parse::msg_values_printer  printer;
	printer(msgValues);
	// BOOST_CHECK_EQUAL(msgValues.m_type, lmp::parse::MsgType::Config);
	// std::cout << static_cast<lmp::WORD>(msgValues.m_type) << std::endl;
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
	lmp::parse::MsgValues msgValues;
	BOOST_CHECK(!parse(begin,
			           last,
					   msgGrammar,
					   msgValues));

  }
}

BOOST_AUTO_TEST_SUITE_END()

