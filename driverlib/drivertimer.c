#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/drivertimer.h"
#include "inc/tm4c1294ncpdt.h" // CMSIS-Core
#include "driverlib/timer.h"


void IniciaTimer(){
  TIMER0_CTL_R  = 0x0; //desliga o timer
  TIMER0_CFG_R |= 0x00000004; // usar timer 16 bits
  TIMER0_TAMR_R &= (0<<2); //TACMR
  TIMER0_TAMR_R |= (1<<0); //TAMR = 0x3
  TIMER0_TAMR_R |= (1<<1); //TAMR = 0x3
  TIMER0_CTL_R &= (0<<2) ; //BORDA SUBIDA
  TIMER0_CTL_R &= (0<<3) ; //BORDA SUBIDA
  TIMER0_TAMATCHR_R &= 0xFFFFFFFE; //
  TIMER0_TAPMR_R  &= 0xFFFFFFFE; //
  TIMER0_TAPR_R  &= 0xFFFFFFFF; //
  TIMER0_TAILR_R &= 0xFFFFFFFF; //
  //TIMER0_CTL_R  &= (1<<0); //liga o timer
  
  //SysCtlPeripheralEnable(TIMER0_CFG_R); // Habilita GPIO N (LED D1 = PN1, LED D2 = PN0)
  
  //while(!SysCtlPeripheralReady(TIMER0_CFG_R)); // Aguarda final da habilitação
  

};

void ReiniciaContador(){
  TIMER0_CTL_R  = 0x00000000; //desliga o timer
  TIMER0_CTL_R &= (0<<2) ; //BORDA SUBIDA
  TIMER0_CTL_R &= (0<<3) ; //BORDA SUBIDA
  TIMER0_TAMATCHR_R &= 0xFFFFFFFE; //
  TIMER0_TAPMR_R  &= 0xFFFFFFFE; //
  TIMER0_TAPR_R  &= 0xFFFFFFFF; //
  TIMER0_TAILR_R &= 0xFFFFFFFF; //
  TIMER0_CTL_R  = 0x00000001; //liga o timer
}