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
#define BOOST_TEST_MODULE LMPClient
#include <boost/test/included/unit_test.hpp>
#include <boost/chrono/chrono_io.hpp>

#include <lmp_mgtif_node_registry.hpp>
#include <lmp_mgtif_node.hpp>
#include <Mgt_NodeRegistry.hpp>

#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <errno.h>

struct MyConfig {
    MyConfig()   { std::cout << "global setup\n"; }
    ~MyConfig()  { std::cout << "global teardown\n"; }
};

//static CORBA::Object_ptr getObjectReference(CORBA::ORB_ptr orb);

//static void setupLMPNode(LMP::NodeFactory_ptr nodeFactory)
//{
//  if( CORBA::is_nil(nodeFactory) )
//  {
//    cerr << "setupLMPNode: The nodeFactory object reference is nil!\n" << endl;
//    return;
//  }
//  CORBA::Long nodeId = 123;
//  LMP::Node_ptr nodePtr = nodeFactory->createNode(nodeId);
//  if( CORBA::is_nil(nodePtr) )
//  {
//    cerr << "setupLMPNode: The node object reference is nil!\n" << endl;
//    return;
//  }
//  ::CORBA::Long            localCCId = 1;
//  ::CORBA::Long            localAddress = 2134532;
//  ::CORBA::Short           localPortNumber = 701;
//  LMP::IPCC_ptr ipccPtr = nodePtr->createIPCC(localCCId, localAddress, localPortNumber);
//  if( CORBA::is_nil(ipccPtr) )
//  {
//    cerr << "setupLMPNode: The node object reference is nil!\n" << endl;
//    return;
//  }
//
//}

//////////////////////////////////////////////////////////////////////

BOOST_GLOBAL_FIXTURE( MyConfig );

BOOST_AUTO_TEST_SUITE( LMPClient )

BOOST_AUTO_TEST_CASE( test_case1 )
{
  try
  {
	CORBA::ORB_var orb =
	  CORBA::ORB_init(boost::unit_test::framework::master_test_suite().argc,
			          boost::unit_test::framework::master_test_suite().argv);
	CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
	PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

	lmp_node_registry::NodeRegistry_i* myNodeRegistry = new lmp_node_registry::NodeRegistry_i(orb, poa);

    PortableServer::ObjectId_var myNodeRegistryId = poa->activate_object(myNodeRegistry);

    // Obtain a reference to the object, and register it in
    // the naming service.
    obj = myNodeRegistry->_this();

    CORBA::String_var x = orb->object_to_string(obj);
    ostringstream registryURIStream;
    registryURIStream << x << ends;

    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    if (orb->work_pending())
    {
      orb->perform_work();
    };

    const unsigned long nodeId = 10001;
    // pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1)
    {
        // error, failed to fork()
    }
    else if (pid > 0)
    {
      boost::chrono::steady_clock::time_point expireTime =
        boost::chrono::steady_clock::now() + boost::chrono::milliseconds(500);
      cout << boost::chrono::steady_clock::now() << ": enter while" << endl;
      while (boost::chrono::steady_clock::now() < expireTime)
      {
        // cout << boost::chrono::steady_clock::now() << ": checking work_pending()" << endl;
        if (orb->work_pending())
        {
          cout << boost::chrono::steady_clock::now() << ": enter perform_work()" << endl;
          orb->perform_work();
          cout << boost::chrono::steady_clock::now() << ": leaving perform_work()" << endl;
        };
      }
      cout << boost::chrono::steady_clock::now() << ": leaving while" << endl;
      BOOST_CHECK(myNodeRegistry->isNodeRegistered(nodeId));

      int status;
      waitpid(pid, &status, 0);
    }
    else
    {
      // we are the child
      const char serverPath[] = "/home/tom/workspace/LMPServer/Debug/LMPServer";
      const char nodeIdOptStr[] = "--node-id";
      const char nodeRegistryOptStr[] = "--node-registry";
      ostringstream nodeIdStream;
      nodeIdStream << nodeId << ends;
      const char* newargv[] =
        { serverPath,
          serverPath,
          nodeIdOptStr,
          nodeIdStream.str().c_str(),
          nodeRegistryOptStr,
          registryURIStream.str().c_str(),
          NULL
        };
//      cout << newargv[0] << " "
//    	   << newargv[1] << " "
//    	   << newargv[2] << " "
//    	   << newargv[3] << " "
//    	   << newargv[4] << " "
//    	   << newargv[5] << endl;
      char* newenviron[] = { NULL };
//      newargv[3] = nodeIdStream.str().c_str();
//      newargv[5] = registryURIStream.str().c_str();
      execve(newargv[0], const_cast<char* const*>(newargv), newenviron);
      perror("execve");   /* execve() only returns on error */
      exit(EXIT_FAILURE);   // exec never returns
    }

    // orb->run();
  }
  catch(CORBA::TRANSIENT&)
  {
    cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << endl;
  }
  catch(CORBA::SystemException& ex)
  {
    cerr << "Caught a CORBA::" << ex._name() << endl;
  }
  catch(CORBA::Exception& ex)
  {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  }
  catch(omniORB::fatalException& fe)
  {
    cerr << "Caught omniORB::fatalException:" << endl;
    cerr << "  file: " << fe.file() << endl;
    cerr << "  line: " << fe.line() << endl;
    cerr << "  mesg: " << fe.errmsg() << endl;
  }
}

BOOST_AUTO_TEST_SUITE_END()

//int
//main (int argc, char **argv)
//{
//  try {
//    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
//
//    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
//    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
//
//    LMP::NodeRegistry_i* myNodeRegistry = new LMP::NodeRegistry_i(orb, poa);
//
//    PortableServer::ObjectId_var myNodeRegistryId = poa->activate_object(myNodeRegistry);
//
//    // Obtain a reference to the object, and register it in
//    // the naming service.
//    obj = myNodeRegistry->_this();
//
//    CORBA::String_var x;
//    x = orb->object_to_string(obj);
//    cout << x << endl;
//
//    orb->destroy();
//  }
//  catch(CORBA::TRANSIENT&) {
//    cerr << "Caught system exception TRANSIENT -- unable to contact the "
//         << "server." << endl;
//  }
//  catch(CORBA::SystemException& ex) {
//    cerr << "Caught a CORBA::" << ex._name() << endl;
//  }
//  catch(CORBA::Exception& ex) {
//    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
//  }
//  catch(omniORB::fatalException& fe) {
//    cerr << "Caught omniORB::fatalException:" << endl;
//    cerr << "  file: " << fe.file() << endl;
//    cerr << "  line: " << fe.line() << endl;
//    cerr << "  mesg: " << fe.errmsg() << endl;
//  }
//  return 0;
//}

//////////////////////////////////////////////////////////////////////

//static CORBA::Object_ptr
//getObjectReference(CORBA::ORB_ptr orb)
//{
//  CosNaming::NamingContext_var rootContext;
//
//  try {
//    // Obtain a reference to the root context of the Name service:
//    CORBA::Object_var obj;
//    obj = orb->resolve_initial_references("NameService");
//
//    // Narrow the reference returned.
//    rootContext = CosNaming::NamingContext::_narrow(obj);
//    if( CORBA::is_nil(rootContext) ) {
//      cerr << "Failed to narrow the root naming context." << endl;
//      return CORBA::Object::_nil();
//    }
//  }
//  catch (CORBA::NO_RESOURCES&) {
//    cerr << "Caught NO_RESOURCES exception. You must configure omniORB "
//	 << "with the location" << endl
//	 << "of the naming service." << endl;
//    return 0;
//  }
//  catch(CORBA::ORB::InvalidName& ex) {
//    // This should not happen!
//    cerr << "Service required is invalid [does not exist]." << endl;
//    return CORBA::Object::_nil();
//  }
//
//  // Create a name object, containing the name test/context:
//  CosNaming::Name name;
//  name.length(2);
//
//  name[0].id   = (const char*) "test";       // string copied
//  name[0].kind = (const char*) "my_context"; // string copied
//  name[1].id   = (const char*) "NodeFactory";
//  name[1].kind = (const char*) "Object";
//  // Note on kind: The kind field is used to indicate the type
//  // of the object. This is to avoid conventions such as that used
//  // by files (name.type -- e.g. test.ps = postscript etc.)
//
//  try {
//    // Resolve the name to an object reference.
//    return rootContext->resolve(name);
//  }
//  catch(CosNaming::NamingContext::NotFound& ex) {
//    // This exception is thrown if any of the components of the
//    // path [contexts or the object] aren't found:
//    cerr << "Context not found." << endl;
//  }
//  catch(CORBA::TRANSIENT& ex) {
//    cerr << "Caught system exception TRANSIENT -- unable to contact the "
//         << "naming service." << endl
//	 << "Make sure the naming server is running and that omniORB is "
//	 << "configured correctly." << endl;
//
//  }
//  catch(CORBA::SystemException& ex) {
//    cerr << "Caught a CORBA::" << ex._name()
//	 << " while using the naming service." << endl;
//    return 0;
//  }
//
//  return CORBA::Object::_nil();
//}
