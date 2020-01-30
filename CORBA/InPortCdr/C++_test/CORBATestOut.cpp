#include "testDataPortSkel.h"
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include <iostream>
#include <rtm/OutPort.h>
#include <fstream>
#include <thread>
#include <random>


int main(int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
    std::ifstream ifs("ior.txt");
    std::random_device rnd;
    if (!ifs)
    {
        return 1;
    }

    std::string ior;
    std::getline(ifs, ior);

    CORBA::Object_var obj = orb->string_to_object(ior.c_str());

    testOpenRTM::InPortCdr_var ipcref = testOpenRTM::InPortCdr::_narrow(obj);
    if (CORBA::is_nil(ipcref)) {
        return 1;
    }

    

    CORBA::ULong datasize = 100;
    int count = 0;

    bool Flag = true;

    RTC::CameraImage data;


#ifdef ORB_IS_ORBEXPRESS
    CORBA::Stream cdr;
#elif defined(ORB_IS_TAO)
    TAO_OutputCDR cdr;
#else
    cdrMemoryStream cdr;
#endif
    testOpenRTM::CdrData byte_data;


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
        data.width = static_cast<CORBA::UShort>(datasize / data.height / 3);
        data.format = CORBA::string_dup("rgb8");
        data.pixels.length(data.height*data.width * 3);


        setTimestamp(data);

#ifdef ORB_IS_ORBEXPRESS
        cdr.rewind();
        cdr.is_little_endian(true);
        cdr << data;
#elif defined(ORB_IS_TAO)
        cdr.reset();
        cdr << data;
#else
        cdr.rewindPtrs();
        cdr.setByteSwapFlag(true);
        CORBA::ULong bufsize = 0;

        bufsize >>= cdr;
        data >>= cdr;

        cdrMemoryStream cdr2;
        bufsize = cdr.bufSize();
        bufsize >>= cdr2;
        memcpy(cdr.bufPtr(), cdr2.bufPtr(), 4);
        
#endif

        ipcref->put(cdr);

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