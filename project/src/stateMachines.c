#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

char buttonPressed = 0;

int song[] = {3030, 3030, 3030, 3921, 3030, 2597, 5263, 3921,
              5263, 6250, 4545, 4166, 4444, 4651, 5263, 3030,
              2631, 2325, 2857, 2631, 3030, 3846, 3448, 4166,
              3921, 5263, 6250, 4545, 4166, 4444, 4651, 5263,
              3030, 2631, 2325, 2857, 2631, 3030, 3846, 3448,
              4166, 4000, 2631, 2777, 2941, 3225, 3076, 5263,
              4651, 4000, 4651, 4000, 3508, 4000, 2631, 2777,
	      2941, 3225, 3076, 1960, 1960, 1960, 5263, 4000};

static int ratio = 1100;

void buttonOneState()	       
{
  static char goUp = 1;
  
  if (ratio > 1400) goUp = 0;
  else if (ratio < 1100) goUp = 1;

  if (goUp) ratio += 5;
  else ratio -= 5;
  
  buzzer_set_period(2000000 / ratio);
  
  red_on = 0;
  green_on = 1;

  static char greenState = 0;

  switch (greenState) {
  case 0: greenState++;   green_on = 1; break;
  case 1: greenState++;   green_on = 0; break;
  case 2: greenState++;   green_on = 0; break;
  case 3: greenState++;   green_on = 0; break;
  case 4: greenState = 0; green_on = 0; break;
  }
}

void buttonTwoState()	
{
  static int i = 0;
  static int timer = 0;

  if (timer++ > 30) {
    if (i == 42) i = 0;
  
    buzzer_set_period(song[i++]);
    timer = 0;
  }
  
  red_on = 0;
  green_on = 1;
  
  static char greenState = 0;

  switch (greenState) {
  case 0: greenState++; green_on = 1; break;
  case 1: greenState++; green_on = 1; break;
  case 2: greenState++; green_on = 1; break;
  case 3: greenState++; green_on = 0; break;
  case 4: greenState = 0; green_on = 0; break;
  }
}

void buttonThreeState()
{
  buzzer_set_period(2000);
  red_on = 0;
  green_on = 1;
}

void buttonFourState()
{
  buzzer_set_period(0);
  red_on = 1;
  green_on = 0;
}

void state_advance()
{
  char changed = 0;
  
  switch (buttonPressed) {
  case 1: buttonOneState();   changed = 1; break;
  case 2: buttonTwoState();   changed = 1; break;
  case 3: buttonThreeState(); changed = 1; break;
  case 4: buttonFourState();  changed = 1; break;
  }

  led_changed = changed;
  led_update();
}

void setButtonPress(char state)
{
  switch (state) {
  case 1: buttonPressed = 1; break;
  case 2: buttonPressed = 2; break;
  case 3: buttonPressed = 3; break;
  case 4: buttonPressed = 4; break;
  }
}
