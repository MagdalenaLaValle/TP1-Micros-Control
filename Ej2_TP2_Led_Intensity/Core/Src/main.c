/* Includes ---------*/
#include "main.h"


/* Global variables ----*/
extern uint8_t ON_Counter;
uint8_t Duty = DC;

/* Main Function ----*/
int main(void)
{
  // Hardware Initialize
  Hw_Init();
  while(1){
	  if(SWICTH_Filtered(SWITCH_PORT, SWITCH_PIN_A)==Pressed){
		  Duty = DC1;
  }
	  if(SWICTH_Filtered(SWITCH_PORT, SWITCH_PIN_B)==Pressed){
		  Duty = DC2;
	    }
	  if(SWICTH_Filtered(SWITCH_PORT, SWITCH_PIN_C)==Pressed){
		  Duty = DC3;
	    }
  // Infinite Loop

}}
