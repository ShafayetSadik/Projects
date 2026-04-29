# Autonomous SLAM Drone

## Overview

Autonomous SLAM Drone is a GPS-assisted aerial robotics project built around real-time depth sensing, RGB-D SLAM, 3D mapping, state estimation, waypoint navigation, obstacle avoidance, simulation, and telemetry. The drone uses an Intel RealSense D435 stereo depth camera, Raspberry Pi companion computer, ROS 2, Pixhawk flight controller, and optical flow sensing as core parts of the system.

The project focuses on mapping, localization, navigation, and flight monitoring. It does not include onboard object detection, YOLO detection, ArUco tracking, or visual-servo target approach.

Key planned and integrated software capabilities include:

- Real-time 3D point cloud generation from Intel RealSense D435 depth frames
- RGB-D SLAM with RTAB-Map for real-time 3D occupancy map building
- Loop closure detection to reduce pose drift during longer missions
- OctoMap voxel grid storage for efficient 3D environment representation
- Visual-inertial/state estimation using camera data, Pixhawk IMU data, GPS, barometer, and magnetometer sources
- EKF fusion through `robot_localization` for filtered odometry output
- Nav2 global planning with A* / RRT*-style collision-free path planning
- Nav2 local planning with DWA / MPPI-style real-time obstacle avoidance
- Minimum-snap polynomial trajectory generation for smoother flyable paths
- GPS waypoint missions loaded from `targets.csv` at launch
- Pixhawk GPS and compass heading integration through MAVLink / MAVROS
- Autonomous waypoint sequencing with arrival detection and mission task triggering
- GPS-based outward spiral search route generation for area coverage when needed
- D435 depth data feeding a 3D costmap layer inside Nav2
- Reactive depth-based fallback avoidance for sudden close obstacles
- Configurable inflation radius and minimum clearance distance
- Gazebo simulation with a D435-style camera plugin for offline SLAM and navigation testing
- RViz2 visualization of the live 3D map, drone pose, planned path, and telemetry overlays
- QGroundControl compatibility for mission planning, parameter tuning, and MAVLink monitoring

## Components Used

- Intel RealSense D435 stereo depth camera
- Raspberry Pi companion computer
- Pixhawk flight controller
- Optical flow sensor
- GPS module
- Barometer
- Magnetometer / compass
- ROS 2
- RTAB-Map RGB-D SLAM
- OctoMap
- VINS-Fusion / visual-inertial odometry stack
- `robot_localization` EKF
- Nav2
- MAVLink / MAVROS
- Gazebo
- RViz2
- QGroundControl

## Preview

### Photos

![Autonomous SLAM drone photo](./PXL_20240917_152632146.jpg)

![Autonomous SLAM drone build photo](./PXL_20250207_061148788~2.jpg)

### Videos

[Flight demo video](./PXL_20240329_210226425.mp4)

[Drone test video](./Messenger_creation_1949600B-1008-463A-A4D5-041C8CE3E035.mp4)
