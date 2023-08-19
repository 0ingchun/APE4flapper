#include <imu_task.h>

basicMPU6050<> imu;

imuFilter fusion;

imu_measure_t imu_measure;

void imu_task(void *p_imu_task)
{
    //Serial.begin(115200);

    // Calibrate imu
    imu.setup();
    imu.setBias();

    // Initialize filter: 
    fusion.setup( imu.ax(), imu.ay(), imu.az() );     

    // Rotate heading:
    float angle = 45 * DEG_TO_RAD;                // angle in radians to rotate heading about z-axis
    fusion.rotateHeading( angle, LARGE_ANGLE );   // Can choose LARGE_ANGLE or SMALL_ANGLE approximation

    while (1)
    {
        // Update filter:
        fusion.update( imu.gx(), imu.gy(), imu.gz(), imu.ax(), imu.ay(), imu.az() );    

        imu_measure.angle_dim.yaw = fusion.yaw();
        imu_measure.angle_dim.pitch = fusion.pitch();
        imu_measure.angle_dim.roll = fusion.roll();

        // Display angles:
        Serial.print( fusion.pitch() );
        Serial.print( " " );
        Serial.print( fusion.yaw() );
        Serial.print( " " );
        Serial.print( fusion.roll() );
        Serial.println();
        vTaskDelay(100);
    }
}