#include "CORBASVC.h"
#include <iostream>

CORBASVC_impl::CORBASVC_impl() : m_datasize(0)
{
    m_file.open("cameratestin.txt");
}

CORBASVC_impl::~CORBASVC_impl()
{
}

void CORBASVC_impl::put(const ::RTC::CameraImage& data)
{
    std::lock_guard<std::mutex> guard(m_mu);
    if (m_data.empty() || m_datasize == data.pixels.length())
    {
        auto end = std::chrono::system_clock::now().time_since_epoch();
        auto start = std::chrono::seconds(data.tm.sec) + std::chrono::nanoseconds(data.tm.nsec);
        double diff = std::chrono::duration<double>(end - start).count();
        m_data.push_back(diff);
    }
    else
    {
        save(data.pixels.length());
    }
}

void CORBASVC_impl::save(CORBA::ULong newsize)
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
    m_data.clear();
    std::cout << m_datasize << "\t" << avg << std::endl;
    m_file << m_datasize << "\t" << avg << std::endl;
    m_datasize = newsize;
}