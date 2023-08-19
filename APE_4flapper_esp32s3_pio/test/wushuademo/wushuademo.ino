#include <Servo.h>

Servo myservo1;//
int Max=3000;       //转速最大时候的pwm
int Min=1000;       //转速最小时候的pwm
int pos=Min;        //初始转速赋值
int sign=0;         //标志位，用于切换转速增大还是减小

void setup() {
  myservo1.attach(9);  //pwm输出口为9号端口
  myservo1.write(Max); //输出定义的pwm最大值，模拟遥控器油门打到最大
  delay(5000);         //等待电机设定最大值，会滴滴的发出声音
  myservo1.write(Min); //输出定义的pwm最小值，模拟遥控器油门打到最小
  delay(5000);         //等待电机设定最小值，会滴滴滴的发出声音
  Serial.begin(9600);  
}

void loop()    //电机转速从小变大再变小，反复循环. pwm数值会从串口输出。
{
  delay(10);

  if(sign==0)              //让转速逐渐增大，增大到最大速度的一半
  {
    Serial.println(pos);  
    myservo1.write(pos);   
    //输出pwm到9号端口
    pos++;
    if(pos==(Max+Min)/2)
    sign=1;   
  }
    if(sign==1)              //让转速逐渐减小，减小到电机停止转动
  {
      Serial.println(pos);
      myservo1.write(pos);   
      //输出pwm到9号端口
      pos--;
      if(pos==Min)
      sign=0;
  }
      
}