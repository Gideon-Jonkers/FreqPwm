#include <FreqPwm.h>
/*
Create only one instance per timer

Timer pin pair 0 deg out of phase(use FREQ_PWM_0_DEG_PHASE):
Timer 0 pin 5,6 8-bit timer frequencies 61Hz,244Hz,977Hz,7812Hz,62500Hz

Timer 1 pin 9,10 16-bit timer any frequency from  244Hz(High res)(65533), 15.952KHz(Medium res)(1000), to 5.3MHz(very low res)(1) with cycles of 0% 50% 100%

Timer 2 pin 3,11 8-bit timer frequencies 61Hz,244Hz,488Hz,,1953Hz,977Hz,7812Hz,62500Hz

Timer pin pair 180 deg out of phase(use FREQ_PWM_180_DEG_PHASE):
Timer 0 pin 5,6 8-bit timer frequencies 31Hz,123Hz,490Hz,3922Hz,31373Hz

Timer 1 pin 9,10 16-bit timer any frequency from  122Hz(High res)(65534), 7.992KHz(Medium res)(1000), to 4MHz(very low res)(1) with cycles of 0% 50% 100%

Timer 2 pin 3,11 8-bit timer frequencies 31Hz,123Hz,245Hz,490Hz,980Hz,3922Hz,31373Hz

The class library will interpolate frequencies on timer 0 and timer 2 to the frequencies supported
Timer one will work on frequencies between 244Hz and 5.3Mhz 0 deg out of phase
Timer one will work on frequencies between 122Hz and 4Mhz 180 deg out of phase
*/


//            FreqPwm(timer , frequency, phase);
FreqPwm pwm = FreqPwm(1,5000,FREQ_PWM_0_DEG_PHASE);

void setup()
{
  pinMode(9,OUTPUT);

  pwm.init();

  //  SetCycle(pin,percentage);
  pwm.SetCycle(9,50);
}
int val = 0;
void loop()
{
  delay(100);
  val++;
  if(val>100)
    val = 0;
  pwm.SetCycle(9,val);
}
