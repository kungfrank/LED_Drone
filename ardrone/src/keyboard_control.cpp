#include <ros/ros.h>
#include <termios.h>
#include <signal.h>
#include <stdio.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <fstream>
//#include <linux/delay.h>
#define ABSOLUTE_PATH "/home/lixuesi/data/"

std_msgs::Empty emp_msg;

geometry_msgs::Twist fly_up;
geometry_msgs::Twist fly_down;
geometry_msgs::Twist fly_left;
geometry_msgs::Twist fly_right;
geometry_msgs::Twist fly_forward;
geometry_msgs::Twist fly_backward;
geometry_msgs::Twist fly_turn_right;
geometry_msgs::Twist fly_turn_left;
geometry_msgs::Twist fly_hover;

char getch()
{
    fd_set set;
    struct timeval timeout;
    int rv;
    char buff = 0;
    int len = 1;
    int filedesc = 0;
    FD_ZERO(&set);         
    FD_SET(filedesc, &set);
    
    timeout.tv_sec = 0;
    timeout.tv_usec = 10;

    rv = select(filedesc + 1, &set, NULL, NULL, &timeout);

    struct termios old = {0};
    if (tcgetattr(filedesc, &old) < 0)
        ROS_ERROR("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(filedesc, TCSANOW, &old) < 0)
        ROS_ERROR("tcsetattr ICANON");

    if(rv == -1)
        ROS_ERROR("select");
    else if(rv == 0)
        ROS_INFO("no_key_pressed");
    else
        read(filedesc, &buff, len );

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
        ROS_ERROR ("tcsetattr ~ICANON");


    return (buff);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "none");
    ros::NodeHandle node;
    ros::Rate loop_rate(10);
 
  ros::Publisher pub_land;
  pub_land = node.advertise<std_msgs::Empty>("/ardrone/land", 1); /* Message queue length is just 1 */

  ros::Publisher pub_reset;
  pub_reset = node.advertise<std_msgs::Empty>("/ardrone/reset", 1); /* Message queue length is just 1 */

  ros::Publisher pub_takeoff;
  pub_takeoff = node.advertise<std_msgs::Empty>("/ardrone/takeoff", 1); /* Message queue length is just 1 */
 
  ros::Publisher pub_control;
  pub_control = node.advertise<geometry_msgs::Twist>("/cmd_vel", 1); /* Message queue length is just 1 */

  ros::Publisher pub_empty;
  pub_empty = node.advertise<std_msgs::Empty>("/cmd_vel", 1);


  fly_up.linear.x = 0;
  fly_up.linear.y = 0;
  fly_up.linear.z = 0.3;
  fly_up.angular.x = 0;
  fly_up.angular.y = 0;
  fly_up.angular.z = 0;

  fly_down.linear.x = 0;
  fly_down.linear.y = 0;
  fly_down.linear.z = -0.3;
  fly_down.angular.x = 0;
  fly_down.angular.y = 0;
  fly_down.angular.z = 0;

  fly_left.linear.x = 0;
  fly_left.linear.y = 0.1;
  fly_left.linear.z = 0;
  fly_left.angular.x = 0;
  fly_left.angular.y = 0;
  fly_left.angular.z = 0;

  fly_right.linear.x = 0;
  fly_right.linear.y = -0.1;
  fly_right.linear.z = 0;
  fly_right.angular.x = 0;
  fly_right.angular.y = 0;
  fly_right.angular.z = 0;

  fly_forward.linear.x = 0.1;
  fly_forward.linear.y = 0;
  fly_forward.linear.z = 0;
  fly_forward.angular.x = 0;
  fly_forward.angular.y = 0;
  fly_forward.angular.z = 0;

  fly_backward.linear.x = -0.1;
  fly_backward.linear.y = 0;
  fly_backward.linear.z = 0;
  fly_backward.angular.x = 0;
  fly_backward.angular.y = 0;
  fly_backward.angular.z = 0;

  fly_turn_right.linear.x = 0;
  fly_turn_right.linear.y = 0;
  fly_turn_right.linear.z = 0;
  fly_turn_right.angular.x = 0;
  fly_turn_right.angular.y = 0;
  fly_turn_right.angular.z = -0.2;

  fly_turn_left.linear.x = 0;
  fly_turn_left.linear.y = 0;
  fly_turn_left.linear.z = 0;
  fly_turn_left.angular.x = 0;
  fly_turn_left.angular.y = 0;
  fly_turn_left.angular.z = 0.2;

  fly_hover.linear.x = 0;
  fly_hover.linear.y = 0;
  fly_hover.linear.z = 0;
  fly_hover.angular.x = 0;
  fly_hover.angular.y = 0;
  fly_hover.angular.z = 0;

    while (ros::ok())
    {
        int c = 0;
        c=getch();
                    if (c == 'w'){
                    pub_control.publish(fly_forward);
		    sleep(1);
		    pub_control.publish(fly_hover);
                    }
                    else if (c == 's'){
                    pub_control.publish(fly_backward);
		    sleep(1);
		    pub_control.publish(fly_hover);
                    }
                    else if (c == 'a'){
		    pub_control.publish(fly_left);
		    sleep(1);
		    pub_control.publish(fly_hover);
                    }
                    else if (c == 'd'){
                   pub_control.publish(fly_right);
		    sleep(1);
		    pub_control.publish(fly_hover);
                   }
                    else if (c == 'q'){
                   pub_control.publish(fly_turn_left);
		    sleep(1);
		    pub_control.publish(fly_hover);
                   }
                    else if (c == 'e'){
                   pub_control.publish(fly_turn_right);
		    sleep(1);
		    pub_control.publish(fly_hover);
                   }
                   else if (c == 'u'){
                   pub_control.publish(fly_up);
		    sleep(1);
		    pub_control.publish(fly_hover);
                   }
                   else if (c == 'j'){
                   pub_control.publish(fly_down);
		    sleep(1);
		    pub_control.publish(fly_hover);
                   }
                   else if (c == ' '){
                   pub_control.publish(fly_hover);
                   }
                    else if (c == 'o'){
                   pub_takeoff.publish(emp_msg);
                   }
                    else if (c == 'l'){
                   pub_land.publish(emp_msg);
                   }

        ROS_INFO("%c", c);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
