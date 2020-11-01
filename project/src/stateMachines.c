#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

unsigned char state = 1;

void buttonOneState()	       
{
  red_on = 1;
  green_on = 0;
}

void buttonTwoState()	
{
  red_on = 0;
  green_on = 1;
}

void buttonThreeState()
{
  red_on = 0;
  green_on = 0;
}

void buttonFourState()
{
  red_on = 1;
  green_on = 1;
}

void state_advance()		/* alternate between toggling red & green */
{
  
  switch (state) {
  case 1: buttonOneState(); state++; break;
  case 2: buttonTwoState(); state++; break;
  case 3: buttonThreeState(); state++; break;
  case 4: buttonFourState(); state = 1; break;
  }

  led_changed = 1;
  led_update();
}
