#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>




#define LMOTORN 11
#define LMOTORP 8
#define LMOTORPWM 9

#define RMOTORN 13
#define RMOTORP 12
#define RMOTORPWM 10

#define LENCODER 2
#define RENCODER 3
#define R 10.8

#define WHEEL_BASE 42 //42cm
#define CLICKS_PER_ROTATION 30 
#define LEFT_CLICKS_PER_CM CLICKS_PER_ROTATION/2*PI*R //Divide by circumfrence of the wheel
#define RIGHT_CLICKS_PER_CM CLICKS_PER_ROTATION/2*PI*R



ros::NodeHandle nh;

geometry_msgs::PoseStamped robotpose;

ros::Publisher odom("odominfo", &robotpose);

//geometry_msgs::TransformStamped t;

//tf::TransformBroadcaster broadcaster;

long R_ticks, L_ticks;
float left_distance, right_distance;
float lsamp, rsamp;
float left_cm, right_cm, cm;
float last_left,last_right;
char base_link[] = "/base_link";
char odom_frame[] = "/odom";


void setup()
{

  pinMode(LENCODER, INPUT);
  pinMode(RENCODER, INPUT);
  pinMode(LMOTORP,OUTPUT);	  
  pinMode(LMOTORN,OUTPUT);
  pinMode(LMOTORPWM,OUTPUT);
  pinMode(RMOTORP,OUTPUT);
  pinMode(RMOTORN,OUTPUT);
  pinMode(RMOTORPWM,OUTPUT);

  attachInterrupt(0, lincr, RISING);
  attachInterrupt(1, rincr, RISING);
  nh.initNode();
  nh.advertise(odom);  
  //broadcaster.init(nh);
  
}
void rincr()
{
  right_distance++;
  //Serial.print("Right");
  //Serial.println(right_distance);
}

void lincr()
{
  left_distance++;
  //Serial.print("Left");
  //Serial.println(left_distance);
}

void loop()
{
  sense();
  move();
  delay(1000);
}
/*
Publishes Odometry values on topic /odominfo
 */
void sense(){
  /* sample the left and right encoder counts as close together */
  /* in time as possible */
  lsamp = left_distance;
  rsamp = right_distance; 

  /* determine how many ticks since our last sampling? */
  L_ticks = lsamp - last_left; 	
  R_ticks = rsamp - last_right;

  /* and update last sampling for next time */
  last_left = lsamp; 
  last_right = rsamp; 

  /* convert longs to floats and ticks to inches */
  left_cm = (float)L_ticks/LEFT_CLICKS_PER_CM;
  right_cm = (float)R_ticks/RIGHT_CLICKS_PER_CM;

  /* calculate distance we have traveled since last sampling */
  cm = (left_cm + right_cm) / 2.0;

  /* accumulate total rotation around our center */
  robotpose.pose.orientation.z += (left_cm - right_cm) / WHEEL_BASE;

  /* and clip the rotation to plus or minus 360 degrees */
  robotpose.pose.orientation.z -= (float)((int)(robotpose.pose.orientation.z/(2*PI)))*2*PI;
  robotpose.pose.orientation.w=1.0;

  /* now calculate and accumulate our position in inches */
  robotpose.pose.position.x += cm * cos(robotpose.pose.orientation.z); 
  robotpose.pose.position.y += cm * sin(robotpose.pose.orientation.z); 

  /* and suspend ourself in the multi-tasking queue for 1000 ms */
  /* giving other tasks a chance to run */
  robotpose.header.stamp=nh.now();
  robotpose.header.frame_id=odom_frame;  
  odom.publish( &robotpose );
  nh.spinOnce();  
}

void move(){
  MotorCommands(0,0,1,50);
  MotorCommands(1,50,0,0);
}

void MotorCommands(float L_command,int L_speed,int R_command, int R_speed){
  analogWrite(LMOTORPWM,L_speed);
  analogWrite(RMOTORPWM,R_speed);
  boolean l_move,r_move;
  if(L_command==1){
    l_move=HIGH;
    if(R_command==1){
      r_move=HIGH;      
    }
    else r_move=LOW;
  }
  else{
    l_move=LOW;
    if(R_command==1){
      r_move=HIGH;      
    }
    else r_move=LOW;  
  }
  digitalWrite(LMOTORP,l_move);
  digitalWrite(LMOTORN,!l_move);
  digitalWrite(RMOTORP,r_move);
  digitalWrite(RMOTORN,!r_move);
  delay(500);
  digitalWrite(LMOTORP,LOW);
  digitalWrite(LMOTORN,LOW);
  digitalWrite(RMOTORP,LOW);
  digitalWrite(RMOTORN,LOW);
}

