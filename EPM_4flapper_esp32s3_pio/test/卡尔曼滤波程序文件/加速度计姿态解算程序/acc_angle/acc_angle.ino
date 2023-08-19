#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

float i;//计算偏移量时的循环次数
float ax_offset = 0, ay_offset = 0; //x,y轴的加速度偏移量
float gx_offset = 0, gy_offset = 0; //x,y轴的角速度偏移量
float rad2deg = 57.29578;
float roll, pitch; //储存角度

void setup(void) {
  //定义I2C的接口
  Wire.begin(23, 5);

  //打开串口
  Serial.begin(115200);
  delay(100); // will pause Zero, Leonardo, etc until serial console opens

  //初始化mpu6050
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);//加速度量程±2G
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);//角速度量程±250°/s
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);//采样频率21Hz

  //计算偏移量
  for (i = 1; i <= 2000; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);//获取加速度、角速度、温度
    ax_offset = ax_offset + a.acceleration.x;//计算x轴加速度的偏移总量
    ay_offset = ay_offset + a.acceleration.y;//计算y轴加速度的偏移总量
  }
  ax_offset = ax_offset / 2000; //计算x轴加速度的偏移量
  ay_offset = ay_offset / 2000; //计算y轴加速度的偏移量
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);//获取加速度、角速度、温度

  /*减去偏移量并根据加速度计算角度*/
  //roll角度
  roll = atan((a.acceleration.y - ay_offset) / (a.acceleration.z)) * rad2deg;

  //pitch角度
  pitch = atan((a.acceleration.x - ax_offset) / sqrt(sq(a.acceleration.y - ay_offset) + sq(a.acceleration.z))) * rad2deg;

  //打印角度
  Serial.print("roll: ");
  Serial.print(roll);
  Serial.print(",");
  Serial.print("pitch: ");
  Serial.println(pitch);
  //delay(33);
}
