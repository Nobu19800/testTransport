#include "CORBASVC.h"
#include <fstream>
#include <iostream>
#include <coil/Task.h>


class Task : public coil::Task
{
public:
    Task(CORBA::ORB_ptr orb) {
        m_orb = CORBA::ORB::_duplicate(orb);
    }
    ~Task() {}
    int svc() override
    {
        std::cin.ignore();
        m_orb->shutdown(false);
        return 0;
    }
    CORBA::ORB_var m_orb;
};

int main(int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
    CORBA::Object_var       obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

    PortableServer::Servant_var<CORBASVC_impl> csts = new CORBASVC_impl();
    PortableServer::ObjectId_var myechoid = poa->activate_object(csts);
    CORBA::Object_var csobj = csts->_this();
    CORBA::String_var sior(orb->object_to_string(csobj));
    std::cout << sior << std::endl;

    std::ofstream ofs("ior.txt");
    if (!ofs)
    {
        return 1;
    }

    ofs << sior;
    ofs.close();

    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    Task t(orb);
    t.activate();
    orb->run();
    csts->save(0);

    return 0;
}