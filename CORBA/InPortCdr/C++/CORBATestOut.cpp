#include <rtm/config_rtc.h>
#if RTM_MAJOR_VERSION == 2
#include <rtm/idl/DataPort_OpenRTMStub.h>
#else
#include <rtm/idl/DataPortStub.h>
#endif
#include <rtm/idl/InterfaceDataTypesSkel.h>
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

    OpenRTM::InPortCdr_var ipcref = OpenRTM::InPortCdr::_narrow(obj);
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
    OpenRTM::CdrData byte_data;


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
        data >>= cdr;
#endif

#ifdef ORB_IS_ORBEXPRESS
        unsigned long length = cdr.size_written();
#elif defined(ORB_IS_TAO)
        unsigned long length = static_cast<unsigned long>(cdr.total_length());
#else
        unsigned long length = cdr.bufSize();
#endif
        byte_data.length(length);
        if (length > 0)
        {
#ifdef ORB_IS_ORBEXPRESS
             memcpy(byte_data.get_buffer(), cdr.get_buffer(), length);
#elif defined(ORB_IS_TAO)
             memcpy(byte_data.get_buffer(), cdr.begin(), length);
#else
             memcpy(byte_data.get_buffer(), cdr.bufPtr(), length);
#endif

        }
        
        ipcref->put(byte_data);

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