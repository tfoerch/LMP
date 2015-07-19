// eg3_clt.cc - This is the source code of example 3 used in Chapter 2
//              "The Basics" of the omniORB user guide.
//
//              This is the client. It uses the COSS naming service
//              to obtain the object reference.
//
// Usage: eg3_clt
//
//
//        On startup, the client lookup the object reference from the
//        COS naming service.
//
//        The name which the object is bound to is as follows:
//              root  [context]
//               |
//              text  [context] kind [my_context]
//               |
//              Echo  [object]  kind [Object]
//
#include <Mgt_ClientFixture.hpp>
#include <Mgt_NodeRegistry.hpp>

#define BOOST_TEST_MODULE LMPClient
#include <boost/test/included/unit_test.hpp>


struct MyConfig {
    MyConfig()   { std::cout << "global setup\n"; }
    ~MyConfig()  { std::cout << "global teardown\n"; }
};


BOOST_GLOBAL_FIXTURE( MyConfig );

BOOST_AUTO_TEST_SUITE( LMPClient )

BOOST_FIXTURE_TEST_CASE ( test_case1, LaunchServer )
{
  std::cout << "running test case 1\n";
}

BOOST_AUTO_TEST_SUITE_END()

