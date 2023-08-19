#include <fly_control_task.h>

fly_vec_t fly_vec;
servo_param_t servo_param;

Servo MOTOR_servo_shoulder_left, MOTOR_servo_shoulder_right, MOTOR_brushless_left, MOTOR_brushless_right, MOTOR_servo_tail;

PID_param_t PID_servo_shoulder_left, PID_servo_shoulder_right, PID_brushless_left, PID_brushless_right, PID_servo_tail;

PID pidCalc_servo_shoulder_left(&PID_servo_shoulder_left.Input, &PID_servo_shoulder_left.Output, &PID_servo_shoulder_left.Setpoint, PID_servo_shoulder_left.Kp, PID_servo_shoulder_left.Ki, PID_servo_shoulder_left.Kd, DIRECT);
PID pidCalc_servo_shoulder_right(&PID_servo_shoulder_right.Input, &PID_servo_shoulder_right.Output, &PID_servo_shoulder_right.Setpoint, PID_servo_shoulder_right.Kp, PID_servo_shoulder_right.Ki, PID_servo_shoulder_right.Kd, DIRECT);
PID pidCalc_brushless_left(&PID_brushless_left.Input, &PID_brushless_left.Output, &PID_brushless_left.Setpoint, PID_brushless_left.Kp, PID_brushless_left.Ki, PID_brushless_left.Kd, DIRECT);
PID pidCalc_brushless_right(&PID_brushless_right.Input, &PID_brushless_right.Output, &PID_brushless_right.Setpoint, PID_brushless_right.Kp, PID_brushless_right.Ki, PID_brushless_right.Kd, DIRECT);
PID pidCalc_servo_tail(&PID_servo_tail.Input, &PID_servo_tail.Output, &PID_servo_tail.Setpoint, PID_servo_tail.Kp, PID_servo_tail.Ki, PID_servo_tail.Kd, DIRECT);


void fly_control_task(void *p_fly_control_task)
{

	// Allow allocation of all timers
    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

    // standard 50 hz servo
    MOTOR_servo_shoulder_left.setPeriodHertz(50);
    MOTOR_servo_shoulder_right.setPeriodHertz(50);
    MOTOR_brushless_left.setPeriodHertz(50);
    MOTOR_brushless_right.setPeriodHertz(50);
    MOTOR_servo_tail.setPeriodHertz(50);

#define servo_min_US 1000
#define servo_max_US 2000
#define brushless_min_US 1000
#define brushless_max_US 3000
#define servo_shoulder_left_Pin 18
#define servo_shoulder_right_Pin 19
#define brushless_left_Pin 21
#define brushless_right_Pin 22
#define servo_tail_Pin 23

	MOTOR_servo_shoulder_left.attach(servo_shoulder_left_Pin, servo_min_US, servo_max_US);
    MOTOR_servo_shoulder_right.attach(servo_shoulder_right_Pin, servo_min_US, servo_max_US);
    MOTOR_brushless_left.attach(brushless_left_Pin, brushless_min_US, brushless_max_US);
    MOTOR_brushless_right.attach(brushless_right_Pin, brushless_min_US, brushless_max_US);
    MOTOR_servo_tail.attach(servo_tail_Pin, servo_min_US, servo_max_US);
    // attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep

pidCalc_servo_shoulder_left.SetMode(AUTOMATIC);
pidCalc_servo_shoulder_right.SetMode(AUTOMATIC);
pidCalc_brushless_left.SetMode(AUTOMATIC);
pidCalc_brushless_right.SetMode(AUTOMATIC);
pidCalc_servo_tail.SetMode(AUTOMATIC);


    while (1)
    {
        vector_solve(&servo_param, &fly_vec);
        imu_feedback(&imu_measure);
        fly_att_pid(&servo_param);
        fly_control_loop(&servo_param);
        vTaskDelay(100);
    }
    
}

void vector_solve(servo_param_t *p_servo_param, fly_vec_t *p_fly_vec)
{
    p_servo_param->servo_shoulder_left = p_fly_vec->v_y;
    p_servo_param->servo_shoulder_right = p_fly_vec->v_y * -1;
    p_servo_param->brushless_left = p_fly_vec->v_z;
    p_servo_param->brushless_right = p_fly_vec->v_z;
    p_servo_param->servo_tail = p_fly_vec->v_w;
}

void imu_feedback(imu_measure_t *p_imu_measure)
{
    // Input = p_imu_measure->angle_dim.yaw;
    // Input = p_imu_measure->angle_dim.pitch;
    // Input = p_imu_measure->angle_dim.roll;//////////////
}

void fly_att_pid(servo_param_t *p_servo_param)
{
    pidCalc_servo_shoulder_left.Compute();
    p_servo_param->servo_shoulder_left = PID_servo_shoulder_left.Output;
    pidCalc_servo_shoulder_right.Compute();
    p_servo_param->servo_shoulder_right = PID_servo_shoulder_right.Output;
    pidCalc_brushless_left.Compute();
    p_servo_param->brushless_left = PID_brushless_left.Output;
    pidCalc_brushless_right.Compute();
    p_servo_param->brushless_right = PID_brushless_right.Output;
    pidCalc_servo_tail.Compute();
    p_servo_param->servo_tail = PID_servo_tail.Output;
}

void fly_control_loop(servo_param_t *p_servo_param)
{
    MOTOR_servo_shoulder_left.write(p_servo_param->servo_shoulder_left);
    MOTOR_servo_shoulder_right.write(p_servo_param->servo_shoulder_right);
    MOTOR_brushless_left.write(p_servo_param->brushless_left);
    MOTOR_brushless_right.write(p_servo_param->brushless_right);
    MOTOR_servo_tail.write(p_servo_param->servo_tail);
}