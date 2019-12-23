#include "InPortCdr_impl.h"
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
    
    PortableServer::Servant_var<InPortCdrSVC> icts = new InPortCdrSVC();
    
    PortableServer::ObjectId_var ucid = poa->activate_object(icts.in());
    CORBA::Object_var icobj = icts->_this();
    
    CORBA::String_var sior(orb->object_to_string(icobj));
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
    icts->save(0);

    return 0;
}