# Robotics-ND-Project-6
This is my repository for the final project of the Udacity Robotics Software Engineer Nanodegree Program. The goal of this project is to program a robot that can automatically map the environment and navigate to pick-up and drop-off virtual objects.
## Project set up and launch instructions
1. Before diving into implemening the project, let's create and build a catkin workspace. Open a terminal and type the following:
```
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/
$ catkin_make
```
2. Content of the `src` folder are shared in this repository. Clone and build the workspace using the following command:
```
$ git clone https://github.com/ygsingh/Robotics-ND-Project-6
$ cd ~/catkin_ws/
$ catkin_make
$ source devel/setup.bash
```
3. You should be able to run/launch the project files using the shell scripts described later. For example:
```
$ cd ~/catkin_ws/src/scripts/
$ ./test_slam.sh
```
Below is a short description of packages and scripts used in this project.
## ROS Packages
To build the home service robot, different ROS packages are needed. Some of these packages are official ROS packages and others are created from scratch.
### Official ROS packages
Following official ROS packages are imported and installed in the `scc` directory of the `catkin workspace`. Be sure to clone the full GitHub directory and not just the package itself.
1. [gmapping](http://wiki.ros.org/gmapping): With the __gmapping_demo.launch__ file, you can easily perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras.
2. [turtlebot_teleop](http://wiki.ros.org/turtlebot_teleop): With the __keyboard_teleop.launch__ file, you can manually control a robot using keyboard commands.
3. [turtlebot_rviz_launchers](http://wiki.ros.org/turtlebot_rviz_launchers): With the __view_navigation.launch__ file, you can load a preconfigured rviz workspace. You’ll save a lot of time by launching this file, because it will automatically load the robot model, trajectories, and map for you.
4. [turtlebot_gazebo](http://wiki.ros.org/turtlebot_gazebo): With the __turtlebot_world.launch__ you can deploy a turtlebot in a gazebo environment by linking the world file to it.

### Other ROS packages
1. __pick_objects:__ Here is the [tutorial](http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals) about creating C++ node which send a single goal for the robot ro reach. One task of the project is to modifiy the tutorial script and include an extra goal position and orientation for the robot to reach. The first goal should be the desired pick-up goal and the second goal should be the desired drop-off goal.
The robot has to travel to the desired pick-up, display a message that it reached its destination, wait 5 seconds, travel to the desired drop-off zone, and display a message that it reached the drop off zone.
2. __add_markers:__ The final task of the project is to model a virtual object with markers in rviz. The virtual object is the one being picked and delivered by the robot, thus it should appear in its pick-up zone, and then in its drop-off zone once the robot reaches it. I referred to  [this tutorial](http://wiki.ros.org/rviz/Tutorials/Markers%3A%20Basic%20Shapes) on ROS wiki page to model a virtual object with markers in rviz.
## Shell scripts

### SLAM Testing
First exercise of the project is to write a shell script that will deploy a turtlebot inside the gazebo environment, control it with a SLAM package, and visualize the map in `rviz`. `test_slam.sh ` launches __turtlebot__,__gmapping__,__rviz__, and __teleop__ node.
### Localization and Navigation
Second task of the project is to pick two different goals and test the robot to reach them.
`test_navigation.sh` launches __turtlebot__,__AMCL__ and __rviz__ node. Once you launches all the nodes. you will initially see the particles around the robot, which means that AMCL recognizes the initial robot pose. Now, manually (using 2D NAV Goal arrow in rviz) point out to two different goals, one at a time, and direct the robot to reach them and orient itself with respect to the goals.
### Navigation Goal Node
After testing the robot's ability to navigate to a location, third task is to write a node that will communicate with ROS navigation stack and autonomously send successive goals for the robot to reach. `pick_objects.sh` script file launches the __turtlebot__,__AMCL__,__rviz__ and __pick_objects__ node.
### Virtual Object
`add_marker.sh` script file launches the __turtlebot__, __AMCL__, __rviz__ and __add_markers__ node.
### Home Service
Goals achieved: The home service robot is simulated as follows:
- Initially a marker is shown at the pickup zone.
- Marker dissapears when the robot reach the pickup zone.
- Robot waits for 5 seconds to simulate a pickup before moving towards the drop off zone.
- Marker appears once again at the drop off zone once the robot reaches it.

In order to achieve this goal, __add_marker__ node is modified to subscribe to robot odometry and keep track of robot's velocity (linear and angular). A zero velocity indicates the starting, pick-up and drop-off zones. `home_service.sh` script file launches __turtlebot__, __AMCL__, __rviz__, __pick_objects__ and __add_markers__ nodes. 
