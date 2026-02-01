#include <unitree/robot/g1/loco/g1_loco_api.hpp>
#include <unitree/robot/g1/loco/g1_loco_client.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

using namespace unitree::robot;

// 全局LocoClient对象
std::shared_ptr<g1::LocoClient> loco_client;

// cmd_vel回调函数
void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  // 提取线速度和角速度
  float vx = msg->linear.x;
  float vy = msg->linear.y;
  float vyaw = msg->angular.z;
  
  // 限制速度在允许范围内
  vx = std::max(-2.5f, std::min(3.8f, vx));
  vy = std::max(-1.0f, std::min(1.0f, vy));
  vyaw = std::max(-4.0f, std::min(4.0f, vyaw));
  
  // 调用LocoClient的Move函数控制机器人
  int32_t result = loco_client->Move(vx, vy, vyaw);
  
  // 输出控制信息和结果
  if (result == 0) {
    std::cout << "Move command sent: vx=" << vx 
              << ", vy=" << vy << ", vyaw=" << vyaw << std::endl;
  } else {
    std::cerr << "Move command failed with error code: " << result << std::endl;
  }
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " networkInterface" << std::endl;
    exit(-1);
  }
  
  // 初始化ROS节点
  ros::init(argc, argv, "unitree_ros_control");
  ros::NodeHandle nh;
  
  // 初始化sdk接口
  std::string networkInterface = argv[1];//机器人连接的网卡名称
  unitree::robot::ChannelFactory::Instance()->Init(0, networkInterface);

  // 创建LocoClient对象
  loco_client = std::make_shared<g1::LocoClient>();
  loco_client->SetTimeout(10.0f); // 设置超时时间
  loco_client->Init();
  
  // 创建ROS订阅者，订阅cmd_vel话题
  ros::Subscriber cmdVelSub = nh.subscribe("cmd_vel", 10, cmdVelCallback);
  
  // 设置ROS循环频率
  ros::Rate rate(50); // 50Hz
  
  // 主循环
  while (ros::ok()) {
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}
