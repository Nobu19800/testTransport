#include "testServiceStub.h"
#include <iostream>
#include <rtm/OutPort.h>
#include <fstream>
#include <thread>


int main(int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
    std::ifstream ifs("ior.txt");
    if (!ifs)
    {
        return 1;
    }

    std::string ior;
    std::getline(ifs, ior);

    CORBA::Object_var obj = orb->string_to_object(ior.c_str());

    testOpenRTM::testService_var tsref = testOpenRTM::testService::_narrow(obj);
    if (CORBA::is_nil(tsref)) {
        return 1;
    }

    

    CORBA::ULong datasize = 100;
    int count = 0;

    bool Flag = true;

    RTC::CameraImage data;


    

    while (Flag)
    {
        static const int maxsize = 1200001;
        const int datacount = 50;
        if (datasize > maxsize)
        {
            std::cout << "finish" << std::endl;
            Flag = false;
            return 0;
        }
        data.height = 100;
        data.width = datasize / data.height / 3;
        data.format = CORBA::string_dup("rgb8");
        data.pixels.length(data.height*data.width * 3);
        setTimestamp(data);
        tsref->put(data);

        static double logmul[] = { 2.0, 2.5, 2.0 };

        ++count;

        if (count%datacount == 0)
        {
            std::cout << data.height*data.width * 3 << std::endl;
            datasize = static_cast<int>(static_cast<double>(datasize)*logmul[(count / datacount) % 3]);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(10000));
    }
    

    return 0;


}