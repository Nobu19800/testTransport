#include "InPortCdr_impl.h"
#include <iostream>
#include <random>

unsigned char* data1 = new unsigned char[1000000];
unsigned char* data2 = new unsigned char[1000000];
CORBA::Octet* data3 = new CORBA::Octet[1000000];
std::random_device rnd;




InPortCdrSVC::InPortCdrSVC() : m_datasize(0)
{
    m_file.open("cameratestin.txt");
}

InPortCdrSVC::~InPortCdrSVC()
{
}

bool flag = false;

testOpenRTM::PortStatus InPortCdrSVC::put(const ::testOpenRTM::CdrData& data)
{
    std::lock_guard<std::mutex> guard(m_mu);
    
    //auto time1 = std::chrono::system_clock::now().time_since_epoch();
    
#ifdef ORB_IS_ORBEXPRESS
    m_cdr.rewind();
    m_cdr.is_little_endian(true);
#elif defined(ORB_IS_TAO)
    m_cdr.reset();
#else
    if(!flag)
    {
        m_cdr.rewindPtrs();
        m_cdr.setByteSwapFlag(true);
        flag = true;
    }
    
#endif

    
    //auto start = std::chrono::system_clock::now().time_since_epoch();
#ifdef ORB_IS_ORBEXPRESS
    m_cdr.write_array_1(data.get_buffer(), data.length());
#elif defined(ORB_IS_TAO)
    m_cdr.write_octet_array((const unsigned char*)data.get_buffer(), data.length());
#else
    m_cdr.put_octet_array(data.get_buffer(), data.length());
#endif
    //auto end = std::chrono::system_clock::now().time_since_epoch();

    

    RTC::CameraImage image_data;

#ifdef ORB_IS_ORBEXPRESS
    m_cdr >> m_image_data;
#elif defined(ORB_IS_TAO)
    TAO_InputCDR tao_cdr = TAO_InputCDR(m_cdr);
    tao_cdr >> m_image_data;
#else
    m_image_data <<= m_cdr;
#endif

    

    
    if (!m_data.empty() && m_datasize != m_image_data.pixels.length())
    {
        save(m_image_data.pixels.length());
    }

    auto start = std::chrono::seconds(m_image_data.tm.sec) + std::chrono::nanoseconds(m_image_data.tm.nsec);
    auto end = std::chrono::system_clock::now().time_since_epoch();
    double diff = std::chrono::duration<double>(end - start).count();
    m_data.push_back(diff);
    m_datasize = m_image_data.pixels.length();

    return testOpenRTM::PortStatus::PORT_OK;
}

testOpenRTM::PortStatus InPortCdrSVC::put(cdrMemoryStream& data)
{
    std::lock_guard<std::mutex> guard(m_mu);

    RTC::CameraImage image_data;


#ifdef ORB_IS_ORBEXPRESS
    data >> m_image_data;
#elif defined(ORB_IS_TAO)
    TAO_InputCDR tao_cdr = TAO_InputCDR(data);
    tao_cdr >> m_image_data;
#else
    CORBA::ULong bufsize;
    bufsize <<= data;
    m_image_data <<= data;
#endif

    

    
    if (!m_data.empty() && m_datasize != m_image_data.pixels.length())
    {
        save(m_image_data.pixels.length());
    }

    auto start = std::chrono::seconds(m_image_data.tm.sec) + std::chrono::nanoseconds(m_image_data.tm.nsec);
    auto end = std::chrono::system_clock::now().time_since_epoch();
    double diff = std::chrono::duration<double>(end - start).count();
    m_data.push_back(diff);
    m_datasize = m_image_data.pixels.length();

    return testOpenRTM::PortStatus::PORT_OK;
}


testOpenRTM::PortStatus InPortCdrSVC::put(cdrStream& data)
{
    std::lock_guard<std::mutex> guard(m_mu);

    RTC::CameraImage image_data;



#ifdef ORB_IS_ORBEXPRESS
    data >> m_image_data;
#elif defined(ORB_IS_TAO)
    TAO_InputCDR tao_cdr = TAO_InputCDR(data);
    tao_cdr >> m_image_data;
#else
    m_image_data <<= data;
#endif

    

    
    if (!m_data.empty() && m_datasize != m_image_data.pixels.length())
    {
        save(m_image_data.pixels.length());
    }

    auto start = std::chrono::seconds(m_image_data.tm.sec) + std::chrono::nanoseconds(m_image_data.tm.nsec);
    auto end = std::chrono::system_clock::now().time_since_epoch();
    double diff = std::chrono::duration<double>(end - start).count();
    m_data.push_back(diff);
    m_datasize = m_image_data.pixels.length();

    return testOpenRTM::PortStatus::PORT_OK;
}


void InPortCdrSVC::save(CORBA::ULong newsize)
{
    if (m_data.size() == 0)
    {
        m_datasize = newsize;
        return;
    }
    double avg = 0;
    for (const auto &data : m_data)
    {
        avg += data;
    }
    avg /= m_data.size();
    std::cout << m_datasize << "\t" << avg << "\t" << m_data.size() << std::endl;
    m_file << m_datasize << "\t" << avg << "\t" << m_data.size() << std::endl;
    m_data.clear();
    m_datasize = newsize;
}