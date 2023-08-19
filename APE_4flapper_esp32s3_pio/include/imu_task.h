#pragma once

#include <Arduino.h>

#include "basicMPU6050.h"   // Library for IMU sensor. See this link: https://github.com/RCmags/basicMPU6050
#include "imuFilter.h"


void imu_task(void *p_imu_task);

typedef struct {
    
    struct {
        float yaw;
        float pitch;
        float roll;
    } angle_dim;

    struct {
        float yaw;
        float pitch;
        float roll;
    } angle_accel;

    struct {
        float x;
        float y;
        float z;
    } line_accel;

    struct {
        float x;
        float y;
        float z;
    } line_dim;

    struct {
        float x;
        float y;
        float z;
    } mag_dim;

    float imu_temp;

} imu_measure_t;

extern imu_measure_t imu_measure;