#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include <fstream>
#include <mutex>
#include <chrono>



std::vector<double> m_data;
std::vector<std::chrono::nanoseconds> m_times;
unsigned long m_datasize;
std::mutex m_mu;
std::ofstream m_file("listener.txt");

void save(unsigned long newsize)
{
    if(m_data.size() == 0)
    {
      m_datasize = newsize;
      return;
    }
    double avg = 0;
    for(const auto &data:m_data)
    {
      avg += data;
    }

    avg /= m_data.size();

    double throuput = 0;
    int count = 0;
    std::chrono::nanoseconds start;
    for(const auto &data:m_times)
    {
      if(count > 0)
      {
        double diff = std::chrono::duration<double>(data - start).count();
        throuput += static_cast<double>(m_datasize * 8) / diff;
      }
      count++;
      start = data;
    }
    throuput /= (m_times.size()-1);

    std::cout << newsize << "\t" << avg << "\t" << throuput << "\t" << m_data.size() << std::endl;
    m_file << m_datasize << "\t" << avg << "\t" << throuput << "\t" << m_data.size() << std::endl;

    m_data.clear();
    m_times.clear();
    m_datasize = newsize;
}
void chatterCallback(const sensor_msgs::Image::ConstPtr& msg)
{
    std::lock_guard<std::mutex> guard(m_mu);
    
    if(!m_data.empty() && m_datasize != msg->data.size())
    {
      save(msg->data.size());
    }

    auto end = std::chrono::system_clock::now().time_since_epoch();
    auto start = std::chrono::seconds(msg->header.stamp.sec) + std::chrono::nanoseconds(msg->header.stamp.nsec);
    double diff = std::chrono::duration<double>(end - start).count();
    m_data.push_back(diff);
    m_times.push_back(end);
    m_datasize = msg->data.size();
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::TransportHints hints = ros::TransportHints();
  //hints.tcpNoDelay(false);
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback, hints.tcpNoDelay(true));
  //ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  ros::spin();

  save(0);

  return 0;
}
