#include <memory>
#include <fstream>
#include <mutex>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
using std::placeholders::_1;

std::vector<double> m_data;
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
    m_data.clear();

    std::cout << newsize << "\t" << avg << "\t" << m_data.size() << std::endl;
    m_file << m_datasize << "\t" << avg << "\t" << m_data.size() << std::endl;

    m_datasize = newsize;
}

class Subscriber : public rclcpp::Node
{
public:
  Subscriber()
  : Node("ros2_test_subscriber")
  {
    //RMW_QOS_POLICY_RELIABILITY_RELIABLE : RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT
  rmw_qos_reliability_policy_t reliability_policy_ = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
  //RMW_QOS_POLICY_HISTORY_KEEP_ALL : RMW_QOS_POLICY_HISTORY_KEEP_LAST
  rmw_qos_history_policy_t history_policy_ = RMW_QOS_POLICY_HISTORY_KEEP_ALL;
  size_t depth_ = 10;
  auto qos = rclcpp::QoS(
    rclcpp::QoSInitialization(
      history_policy_,
      depth_
  ));
  qos.reliability(reliability_policy_);

    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
      "topic", qos, std::bind(&Subscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const sensor_msgs::msg::Image::SharedPtr msg) const
  {
    std::lock_guard<std::mutex> guard(m_mu);
    
    if(!m_data.empty() && m_datasize != msg->data.size())
    {
      save(msg->data.size());
    }

    auto end = std::chrono::system_clock::now().time_since_epoch();
    auto start = std::chrono::seconds(msg->header.stamp.sec) + std::chrono::nanoseconds(msg->header.stamp.nanosec);
    double diff = std::chrono::duration<double>(end - start).count();
    m_data.push_back(diff);
    m_datasize = msg->data.size();
  }
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  
  

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Subscriber>());
  rclcpp::shutdown();
  save(0);
  
  return 0;
}
