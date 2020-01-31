#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

using namespace std::chrono_literals;

static double logmul[] = {2.0, 2.5, 2.0};
const int datacount = 500;
const int maxsize = 1200001;

class Publisher : public rclcpp::Node
{
public:
  Publisher()
  : Node("ros2_test_publisher"), count_(0)
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

    publisher_ = this->create_publisher<sensor_msgs::msg::Image>("topic", qos);
    timer_ = this->create_wall_timer(
      2ms, std::bind(&Publisher::timer_callback, this));

    datasize = 100;
    count = 0;
  
  
  }

private:
  void timer_callback()
  {
    if(datasize < maxsize)
    {
      auto msg = sensor_msgs::msg::Image();

      
      if(datasize < 300)
      {
          msg.height = 1;
      }
      else
      {
          msg.height = 100;
      }
      msg.width = datasize/msg.height/3;
      msg.data.resize(msg.height*msg.width*3);
      auto now = std::chrono::system_clock::now().time_since_epoch();
      auto sec = std::chrono::duration_cast<std::chrono::seconds>(now);
      auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now - sec);
      msg.header.stamp.sec  = static_cast<unsigned int>(sec.count());
      msg.header.stamp.nanosec = static_cast<unsigned int>(nsec.count());

      //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(msg);

      ++count;
      
      if(count%datacount == 0)
      {
        std::cout << msg.height*msg.width*3 << std::endl;
        datasize = static_cast<int>(static_cast<double>(datasize)*logmul[(count/datacount)%3]);
      }
    }
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  size_t count_;
  int datasize;
  int count;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Publisher>());
  rclcpp::shutdown();
  return 0;
}
