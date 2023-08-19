#pragma once

#include <Arduino.h>

#include "ESP32Servo.h"
#include "PID_v1.h"

#include <math.h>
#include "imu_task.h"

void fly_control_task(void *p_fly_control_task);

typedef struct {
    float v_x;
    float v_y;
    float v_z;
    float v_w;
} fly_vec_t;

extern fly_vec_t fly_vec;

typedef struct {
    float servo_shoulder_left;
    float servo_shoulder_right;
    float brushless_left;
    float brushless_right;
    float servo_tail;
} servo_param_t;

typedef struct {
    double Input;
    double Output;
    double Setpoint;
    double Kp;
    double Ki;
    double Kd;
} PID_param_t;

void vector_solve(servo_param_t *p_servo_param, fly_vec_t *p_fly_vec);
void imu_feedback(imu_measure_t *p_imu_measure);
void fly_att_pid(servo_param_t *p_servo_param);
void fly_control_loop(servo_param_t *p_servo_param);
