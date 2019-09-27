#include "ros/ros.h"

#include "sensor_msgs/Image.h"


#include <chrono>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<sensor_msgs::Image>("chatter", 1000);

  ros::Rate loop_rate(20);

  static double logmul[] = {2.0, 2.5, 2.0};
  int datasize = 100;
  const int maxsize = 1200001;
  int count = 0;
  const int datacount = 500;
  while (ros::ok() && datasize < maxsize)
  {
    
    sensor_msgs::Image msg;

    //std::stringstream ss;
    //ss << "hello world " << count;
    //msg.data = ss.str();

    //ROS_INFO("%s", msg.data.c_str());

    msg.height = 100;
    msg.width = datasize/msg.height/3;
    msg.data.resize(msg.height*msg.width*3);
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(now);
    auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now - sec);
    msg.header.stamp.sec  = static_cast<unsigned int>(sec.count());
    msg.header.stamp.nsec = static_cast<unsigned int>(nsec.count());


    chatter_pub.publish(msg);

    


    loop_rate.sleep();
    //if(count%30 == 29)
    // datasize += 5000;
    ++count;
    
    if(count%datacount == 0)
    {
      std::cout << msg.height*msg.width*3 << std::endl;
      datasize = static_cast<int>(static_cast<double>(datasize)*logmul[(count/datacount)%3]);
    }
    
  }
  std::cout << "finish" << std::endl;
  while (ros::ok())
  {
    loop_rate.sleep();
  }


  return 0;
}
