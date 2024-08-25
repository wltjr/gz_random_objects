# GZ Random Objects
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg?style=plastic)](https://github.com/wltjr/gz_random_objects/blob/master/LICENSE.txt)
![Build Status](https://github.com/wltjr/gz_random_objects/actions/workflows/docker_build.yml/badge.svg)
[![Code Quality](https://sonarcloud.io/api/project_badges/measure?project=wltjr_gz_random_objects&metric=alert_status)](https://sonarcloud.io/dashboard?id=wltjr_gz_random_objects)

Gazebo Random Objects is a plugin for Gazebo that will randomly place objects
in mesh files on a 2D plane.

## Download
Download and unpack or clone this repositories contents into your ros2
workspace; ex `~/ros2_ws/src/gz_random_objects`.


## Build
The plugin is built using the standard ROS 2 build process. Building is done
using colcon which will invoke cmake and run the necessary commands. Run the
following command in your ros2 workspace; ex `~/ros2_ws/`.
```bash
colcon build --symlink-install --packages-select  gz_random_objects
```

### Source install
Make sure to run the following command after install and login. Run the
following command in your ros2 workspace; ex `~/ros2_ws/`.
```bash
source install/setup.bash
```

You may want to have your development user environment do this on login via
`~/.bashrc` file; add the following to the end of that file.
```bash
source ~/ros2_ws/install/setup.bash
```

## Plugin Usage
In order to use the plugin, it needs to be added to a SDF world, or model to be
included in some SDF world, or part of a URDF.

```xml
<plugin filename="libgz_random_objects.so" name="gz::sim::systems::GzRandomObjects">
    <!-- Parent ID in SDF -->
    <parent>4</parent>
    <!--Number of Objects, same number as mesh files at this time -->
    <objects>7</objects>
    <!-- x/y min and max, difference becomes range, along with scale -->
    <x_min>-750</x_min>
    <x_max>750</x_max>
    <x_scale>0.5</x_scale>
    <y_min>-2250</y_min>
    <y_max>2250</y_max>
    <y_scale>0.5</y_scale>
    <!-- z scale only at this time -->
    <z_scale>0.5</z_scale>
    <!-- Mesh files to use, can use https:// or file:// -->
    <mesh>file://$(find gz_random_objects)/meshes/rocks/rock1.dae</mesh>
    <mesh>file://$(find gz_random_objects)/meshes/rocks/rock2.dae</mesh>
    <mesh>file://$(find gz_random_objects)/meshes/rocks/rock3.dae</mesh>
    <mesh>file://$(find gz_random_objects)/meshes/rocks/rock4.dae</mesh>
    <mesh>file://$(find gz_random_objects)/meshes/rocks/rock5.dae</mesh>
    <mesh>file://$(find gz_random_objects)/meshes/rocks/rock6.dae</mesh>
    <mesh>file://$(find gz_random_objects)/meshes/rocks/rock7.dae</mesh>
</plugin>
```
