#include "SoftTimer.h"

unsigned long now, previous;
unsigned int  pwm1pin = 4, pwm2pin = 2;
unsigned int  pwmlevel, pwmperiod;

//PWM function for LED
unsigned int  counter = 0;
SoftTimer StepT( &millis );
unsigned int  levels[13] = { 0,0,1,2,3,5,8,13,21,34,55,89,144 };
unsigned int  step=0;
bool  direction = true;

bool  LedPWM( void )
{
  return( ( levels[step] ) > counter );
}

void  LedPWMtask( void )
{

  if( !StepT.TimerRun() )
  {
    StepT.TimerReStart(30);
    if( direction ) step++;
    else  step-- ;

    if(  direction && ( step == 12) ) direction = false;
    if( !direction && ( step == 0 ) ) direction = true;
  }
  
  counter++;
  if( counter > 144 ) counter = 0; 
}

void setup() {
  // put your setup code here, to run once:

  pinMode( pwm1pin, OUTPUT );
  pinMode( pwm2pin, OUTPUT );

  pwmlevel = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  LedPWMtask();

  digitalWrite( pwm1pin ,  LedPWM() );
  digitalWrite( pwm2pin , !LedPWM() );

}
