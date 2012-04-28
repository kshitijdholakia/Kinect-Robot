BE_Project_2012: 
================
## Title: Localization and Mapping with a Mobile Robot and Kinect ##


Group Info:
------------
### College: Fr. Conceicao Rodrigues College of Engineering, University of Mumbai ###

+   Ashish Belokar 
+   Kshitij Dholakia 
+   Swapnil Kate 



Extension Of
------------

[Implementation of slam_gmapping](http://ros.org/wiki/slam_gmapping) 



Project Description
-------------------

The project involves the development of a mobile robotic platform, equipped with wheel encoders and Kinect sensor and using it to carry out Localization and Mapping in indoor environments. 

Key implementation points in the project are:
*		Developing mobile robot
*		Converting encoder data to pose estimates (x, y, theta)
*		Identifying Coordinate frames of the robot, and implementing Coordinate frame Transformations
*		Set up the Kinect to stream Laser Scan data from it's depth camera
*		Perform slam_gmapping
*		Visualize the entire process



Technologies Used
-------------------

+		Robot Operating System
+		Kinect
+		Arduino
+		Custom-made Robot:    
 			*	Differential (rear-wheel) drive with a front castor-wheel   
   		* Laptop-mountable Chasis



Installation Instructions
=========================

1. Install Robot Operating System on Ubuntu 11.10
[ROS Electric](http://www.ros.org/wiki/electric/Installation/Ubuntu)   
```sudo apt-get install ros-electric-desktop-full```

2. Install OpenNI, the Kinect driver, as a ROS Stack 
[OpenNI](http://www.ros.org/wiki/openni_kinect)   
```sudo apt-get install ros-electric-openni-kinect```

3. Download the Arduino IDE, for programming the Arduino microcontroller 
[Arduino IDE](http://arduino.cc/en/Main/Software)   
```sudo apt-get install arduino```

4. Set up Arduino to run as a ROS node using rosserial 
[rosserial](http://www.ros.org/wiki/rosserial_arduino)   
```hg clone https://kforge.ros.org/rosserial/hg```

5. Set up pointcloud_to_laserscan ROS package
[pointcloud_to_laserscan](http://www.ros.org/wiki/pointcloud_to_laserscan)   
```hg clone https://kforge.ros.org/turtlebot/turtlebot```



References
===========

+ [Robot Operating System Tutorials](http://www.ros.org/wiki/ROS/Tutorials)

+ [Arduino Tutorials](http://arduino.cc/en/Tutorial/HomePage)

+	[rosserial Tutorials](http://www.ros.org/wiki/rosserial_arduino/Tutorials)

+ [Coordinate Frames Transformation](http://www.ros.org/wiki/tf)

+ [OpenNI Reference](http://www.openni.org/)

+ [Turtlebot Demos](http://ros.org/wiki/turtlebot_apps)

+	[slam_gmapping](http://www.ros.org/wiki/gmapping)

+ SLAM References (Analytical)
	1. [OpenSLAM](http://openslam.org), a collection of open source SLAM algorithms
	2. [SLAM for dummies](http://ocw.mit.edu/courses/aeronautics-and-astronautics/16-412j-cognitive-robotics-spring-2005/projects/1aslam_blas_repo.pdf), an introduction to SLAM
	











