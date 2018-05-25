#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/drivertimer.h"
#include "inc/tm4c1294ncpdt.h" // CMSIS-Core
#include "driverlib/timer.h"

void IniciaTimer(){
    
  SYSCTL_RCGCTIMER_R = 0x00000001; //Habilitar GPTM0
  TIMER0_CTL_R  = 0x00000000; //desliga o timer/borda de subida
  TIMER0_CFG_R  = 0x00000004; // usar timer 16 bits
  TIMER0_TAMR_R = 0x00000013; //Modo compare e capture
  TIMER0_TAMATCHR_R = 0xFFFFFFFE; //
  TIMER0_TAPMR_R  = 0xFFFFFFFE; //
  TIMER0_TAPR_R  = 0xFFFFFFFF; //
  TIMER0_TAILR_R = 0xFFFFFFFF; // 

};

void ReiniciaContador(){
  TIMER0_CTL_R  = 0x00000000; //desliga o timer
  TIMER0_TAMATCHR_R &= 0xFFFFFFFE; //
  TIMER0_TAPMR_R  &= 0xFFFFFFFE; //
  TIMER0_TAPR_R  &= 0xFFFFFFFF; //
  TIMER0_TAILR_R &= 0xFFFFFFFF; //
  TIMER0_CTL_R  = 0x00000001; //liga o timer
}