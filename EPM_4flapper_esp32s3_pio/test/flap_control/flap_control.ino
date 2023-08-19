#include <Servo.h>

// -- Constants:
  // PWM input:
const int N_INPUTS = 3;
const int DEADBAND = 4;
  
  // PWM output:
const int PWM_CHANGE = 500;
const int PWM_MID = 1500;
const float DECAY_INPUT = 0.1;

  // Amplitude control: 
const int AMP_CUTOFF = 10;
const int AMP_OFFSET = 300;

  // Wave signals:
const float WAVE_INT = 150.0; // Half period 
const float FREQ = PI/WAVE_INT;

//-- Variables:
Servo servo[2];
volatile int16_t pwm_raw[N_INPUTS] = {0};
int16_t pwm_input[N_INPUTS] = {0};

// -- Pin Change Interrupt to get PWM inputs: 

ISR( PCINT0_vect ) {  

  static int32_t change_time[N_INPUTS] = {0};
  
  uint8_t mask = B00000010;
  
  for ( uint8_t index = 0 ; index < N_INPUTS ; index += 1 ) {      
   
    if( (change_time[index] == 0) && (PINB & mask) ) {  
      change_time[index] = micros();
    }
    
    else if( (change_time[index] != 0) && !(PINB & mask) ) {
      
      change_time[index] = ( micros() - change_time[index] ) - PWM_MID;

      //-

      int16_t diff = change_time[index] - pwm_raw[index];
    
      if( diff > DEADBAND ) {
        pwm_raw[index] = change_time[index] - DEADBAND;
      }

      if( diff < -DEADBAND ) {
        pwm_raw[index] = change_time[index] + DEADBAND;
      }

      //-
      
      change_time[index] = 0;
    } 
    mask = mask << 1;
  }
}

// -- 

void input_filter( void ) {
  for( int index = 0; index < N_INPUTS; index += 1 ) {
    pwm_input[index] = pwm_raw[index]*DECAY_INPUT + pwm_input[index]*( 1 - DECAY_INPUT );
  }
}

// -- Function to set amplitude via throttle: 

int amp_func( int input ) {
  int var = ( input + AMP_OFFSET );
  if( var <= AMP_CUTOFF ) {
    return 0;
  } else {
    return var - AMP_CUTOFF;
  }
}


// -- Wave functions [for wing oscillation]:

float tri_wave( void ) {
  static int last_time = millis();

  int int_time = millis() - last_time;

  if( int_time < WAVE_INT ) {
    
    return 2*int_time/WAVE_INT - 1;
    
  } else if ( (int_time > WAVE_INT) && (int_time < 2*WAVE_INT) ) {
    
    return  3 - 2*int_time/WAVE_INT; 

  } else if( int_time > WAVE_INT ) {
    last_time = millis();
    
    return -1;
  }
}

float saw_wave( void ) {
  static int last_time = millis();

  int int_time = millis() - last_time;

  if( int_time < 2*WAVE_INT ) {
    
    return int_time/WAVE_INT - 1;
    
  } else {
    
    last_time = millis();
    
    return -1;
  }
}

float sin_wave( void ) {
  return sin( millis()*FREQ );
}


// -- Function to combine wing oscillation and dihedral angle:

int flap_func( int amplitude, int offset ) {
  if( amplitude == 0 ) {
    return constrain( offset , -PWM_CHANGE, PWM_CHANGE );
  } else {
    return constrain( offset + sin_wave()*amplitude , -PWM_CHANGE, PWM_CHANGE );
  }
}


// -- Main functions:

void setup() {

  // Enabling interrupt:
  PCICR |= (B00000001 << 0);

  // Setting PWM inputs:
  for ( int index = 0; index < N_INPUTS ; index += 1 ) {
    PCMSK0 = PCMSK0 | (B00000010 << index);
    pinMode( index + 9 , INPUT_PULLUP );
  }

  // Setting servo outputs:
  for( int index = 2; index <= 3 ; index += 1 ) {
    pinMode( index , OUTPUT );
    servo[index - 2].attach( index );
    servo[index - 2].write( PWM_MID );   
  }

  //Default to minimum throttle:
  pwm_raw[2] = -AMP_OFFSET;
  pwm_input[2] = pwm_raw[2]; 
  
  //Serial.begin(9600);
}

void loop() {

  input_filter();

  int16_t amp = amp_func( pwm_input[2] );
  
  servo[0].writeMicroseconds( PWM_MID - flap_func( amp , pwm_input[0] + pwm_input[1] ) );
  servo[1].writeMicroseconds( PWM_MID + flap_func( amp , -pwm_input[0] + pwm_input[1] ) );

  //Serial.println( pwm_input[2] );
}
