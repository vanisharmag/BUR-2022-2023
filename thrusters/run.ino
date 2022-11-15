/*
  from https://bluerobotics.com/learn/guide-for-controlling-the-basic-esc-with-a-potentiometer/
  and https://atadiat.com/en/e-rosserial-arduino-introduction/
*/
#include <Servo.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &handler);

byte servo_pins = 9; // signal pin for the ESC. needs 6 pins next to each other 
Servo servos[6];

// vectors for controlling linear movement ? but now im not sure how to go down 
float top_right = {-.25, 0, -.25}; // jank rn but can expiremtn 
float top_left = {-.25, 0, .25};
float bottom_right = {.25, 0, -.25};
float bottom_left = {.25, 0, .25};
float right = {0, .5, 0};
float left = {0, .5, 0};

// depends on how thrusters are plugged in 
float thrusters[] = {top_right, top_left, bottom_right, bottom_left, right, left};

void setup() {
  nh.initNode(); 
  nh.subscribe(sub); 

  for(int i = 0; i<6; i++){
    servos[i].attach(i+servo_pins); 
  }
  for(int i = 0; i<6; i++){
    servos[i].writeMicroseconds(1500); 
  }
  delay(7000); // delay to allow the ESC to recognize the stopped signal.
}

void loop(){
  nh.spinOnce();
}

void handler( const geometry_msgs::Twist& msg ) {
  int pwm_val = 0; 
  int thrust = 0; 
  for(int i = 0; i<6; i++){
    pwm_x = map((thrusters[i][0]*msg.linear.x), -1, 1, 1100, 1900)
    pwm_y = map((thrusters[i][1]*msg.linear.y), -1, 1, 1100, 1900)
    pwm_z = map((thrusters[i][2]*msg.linear.z), -1, 1, 1100, 1900)
    servos[i].writeMicroseconds(pwm_x + pwm_y + pwm_z); // Send signal to ESC.
  }
}

