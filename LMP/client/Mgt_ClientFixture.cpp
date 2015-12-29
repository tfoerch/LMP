
#include <Mgt_ClientFixture.hpp>
#include <Mgt_NodeRegistry.hpp>
#include <omniORB4/CORBA.h>
#include <omniORB4/poa.h>                         // for POA_var, POA, etc
#include <omniORB4/templatedecls.h>
#include <omniORB4/templatedefns.h>
#include <omniORB4/userexception.h>               // for TRANSIENT

#include <boost/test/unit_test_suite.hpp>
// #include <boost/test/included/unit_test.hpp>

#include <boost/chrono/duration.hpp>              // for duration, etc
#include <boost/chrono/io_v1/chrono_io.hpp>       // for operator<<
#include <boost/chrono/system_clocks.hpp>         // for steady_clock, etc
#include <boost/chrono/time_point.hpp>            // for operator+, etc
// #include <boost/chrono/chrono_io.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>                               // for execve, fork
#include <sys/wait.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <net/if.h>
// #include <ifaddrs.h>
// #include <errno.h>

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
	  std::ostringstream registryURIStream;
	  registryURIStream << x << std::ends;

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
		std::cout << boost::chrono::steady_clock::now() << ": enter while" << std::endl;
		while (boost::chrono::steady_clock::now() < expireTime)
		{
		  // std::cout << boost::chrono::steady_clock::now() << ": checking work_pending()" << std::endl;
		  if (orb->work_pending())
		  {
			std::cout << boost::chrono::steady_clock::now() << ": enter perform_work()" << std::endl;
            orb->perform_work();
            std::cout << boost::chrono::steady_clock::now() << ": leaving perform_work()" << std::endl;
		  };
		}
		std::cout << boost::chrono::steady_clock::now() << ": leaving while" << std::endl;
		//theNodeRegistry->isNodeRegistered(theNodeId);

	  }
	  else
	  {
		// we are the child
		const char serverPath[] = "/home/tom/build/LMP/server/LMPServer_T";
		const char nodeIdOptStr[] = "--node-id";
		const char nodeRegistryOptStr[] = "--node-registry";
		std::ostringstream nodeIdStream;
		nodeIdStream << theNodeId << std::ends;
		const char* newargv[] =
          { serverPath,
            serverPath,
			nodeIdOptStr,
			nodeIdStream.str().c_str(),
			nodeRegistryOptStr,
			registryURIStream.str().c_str(),
			NULL
          };
//      std::cout << newargv[0] << " "
//    	   << newargv[1] << " "
//    	   << newargv[2] << " "
//    	   << newargv[3] << " "
//    	   << newargv[4] << " "
//    	   << newargv[5] << std::endl;
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
    std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << std::endl;
  }
  catch(CORBA::SystemException& ex)
  {
    std::cerr << "Caught a CORBA::" << ex._name() << std::endl;
  }
  catch(CORBA::Exception& ex)
  {
    std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
  }
  catch(omniORB::fatalException& fe)
  {
    std::cerr << "Caught omniORB::fatalException:" << std::endl;
    std::cerr << "  file: " << fe.file() << std::endl;
    std::cerr << "  line: " << fe.line() << std::endl;
    std::cerr << "  mesg: " << fe.errmsg() << std::endl;
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

