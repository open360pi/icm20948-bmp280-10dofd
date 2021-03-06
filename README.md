# icm20948-bmp280-10dofd

Simple RaspberryPI daemon that interacts with WaveShare's 
[10 DOF IMU Sensor (D)](https://www.waveshare.com/wiki/10_DOF_IMU_Sensor_(D)) in background
and writes current yaw pitch and roll to file, so other applications can use it.

![10 dof sensor](https://www.waveshare.com/w/thumb.php?f=10-DOF-IMU-Sensor-D-1.jpg&width=300)

## Requirements
- bullseye os
- wiringpi (provided as deb package in repository)
- connected and working [10 DOF IMU Sensor (D)](https://www.waveshare.com/wiki/10_DOF_IMU_Sensor_(D)) module


## Installation

Install pi360 repository.
```shell
wget -O - https://repo.pi360.dev/public.key | sudo apt-key add -
sudo echo 'deb https://repo.pi360.dev/bullseye/ bullseye main' >> /etc/apt/sources.list
sudo apt update
```

Install package.
```shell
sudo apt install icm20948-bmp280-10dofd
```

Make sure that daemon is up and running.
```shell
sudo service 10dof status
```

## Data

On each loop daemon writes multiple params into simple file located inside `/var/run` directory. 
It's guaranteed that file is being updated atomically (so your external process won't 
read file in the middle of write operation). 

Don't rely on order of parameters in your scripts, match names with values instead.
```shell
pi@raspberrypi:~ $ cat /var/run/imu_data
roll=0.000000 pitch=0.000000 yaw=-180.013260 alt=44330.000000 temp=0.000000 time=1652897302
```

## Purpose

Our main project, pi360 camera daemon, requires datasource of images metadata, 
providing optional feature that saves information about how and where photosphere was taken.

This project integrates WaveShare's 10 DOF sensor with pi360, same time providing developers
ability to use whatever sensor they want (by creating alternative implementations
that write data to /var/run/imu_data file).
