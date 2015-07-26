
#include <Mgt_ClientFixture.hpp>
#include <lmp_mgtif_node_registry.hpp>
#include <lmp_mgtif_node.hpp>
#include <Mgt_NodeRegistry.hpp>

#include <boost/test/unit_test_suite.hpp>
// #include <boost/test/included/unit_test.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <errno.h>

LaunchServer::LaunchServer()
  : theNodeRegistry(0),
	theOrb(),
	theNodeId(10001),
	theChildPid(0)
{
  std::cout << "launch server setup\n";
  try
  {
	theOrb =
	  CORBA::ORB_init(boost::unit_test::framework::master_test_suite().argc,
			          boost::unit_test::framework::master_test_suite().argv);
	if (theOrb)
	{
	  CORBA::ORB_var orb = *theOrb;
	  CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
	  PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

	  theNodeRegistry = new lmp_node_registry::NodeRegistry_i(orb, poa);

	  PortableServer::ObjectId_var myNodeRegistryId = poa->activate_object(theNodeRegistry);

	  // Obtain a reference to the object, and register it in
	  // the naming service.
	  obj = theNodeRegistry->_this();

	  CORBA::String_var x = orb->object_to_string(obj);
	  ostringstream registryURIStream;
	  registryURIStream << x << ends;

	  PortableServer::POAManager_var pman = poa->the_POAManager();
	  pman->activate();

	  if (orb->work_pending())
	  {
		orb->perform_work();
	  };

	  // pid_t parent = getpid();
	  theChildPid = fork();

	  if (theChildPid == -1)
	  {
        // error, failed to fork()
	  }
	  else if (theChildPid > 0)
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
		//theNodeRegistry->isNodeRegistered(theNodeId);

	  }
	  else
	  {
		// we are the child
		const char serverPath[] = "/home/tom/build/LMP/server/LMPServer_T";
		const char nodeIdOptStr[] = "--node-id";
		const char nodeRegistryOptStr[] = "--node-registry";
		ostringstream nodeIdStream;
		nodeIdStream << theNodeId << ends;
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

LaunchServer::~LaunchServer()
{
  std::cout << "launch server teardown\n";
  if (theNodeRegistry)
  {
	std::cout << "calling shutdown" << std::endl;
	theNodeRegistry->shutdown();
  }
  int status;
  waitpid(theChildPid, &status, 0);
}

