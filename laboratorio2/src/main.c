#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h" // CMSIS-Core
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h" // driverlib
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/systick.h"
#include "driverlib/drivertimer.h"
#include "driverlib/uartstdio.h"

#define PERIODO 60001
#define DELTA 3000

uint32_t ui32SysClock ;
uint8_t LED_D1 = 0;
int32_t LED_D4 = PERIODO;
uint8_t updn = 1;
void SysTick_Handler(void){
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, LED_D1);
    LED_D1 ^= GPIO_PIN_1;
    //ReiniciaContador();
} // SysTick_Handler

//void Periodo1(){
//SysTickPeriodSet(25000000); // f = 25MHz / t = 1 s
//int32_t contador = TIMER0_TAR_R;
//
//}
//void Periodo1ms(){
//SysTickPeriodSet(25000); // f = 25MHz / t = 1ms
//}

void ConfigUART(void){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  
  UARTStdioConfig(0, 115200, ui32SysClock);
  
}

void main(void){
 ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                              SYSCTL_OSC_MAIN |
                                              SYSCTL_USE_PLL |
                                              SYSCTL_CFG_VCO_480),   
                                              120000000); // PLL em 120MHz
   IniciaTimer();
   SysTickEnable();
   SysTickPeriodSet(25000000);   
   ConfigUART();
  //UARTprintf("TESTE");
 
  //Periodo1();
  
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); // Habilita GPIO N (LED D1 = PN1, LED D2 = PN0)
  
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)); // Aguarda final da habilitação
  
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1); // LEDs D1 e D2 como saída
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);
  GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); // Habilita GPIO J (push-button SW1 = PJ0, push-button SW2 = PJ1)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)); // Aguarda final da habilitação
    
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1); // push-buttons SW1 e SW2 como entrada
  GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  
  SysTickIntEnable();

  while(1){
    
    if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) != GPIO_PIN_0) // Testa estado do push-button SW1
        UARTprintf("TESTE1");//Periodo1();
    
    if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) != GPIO_PIN_1) // Testa estado do push-button SW2
       UARTprintf("TESTE2");// Periodo1ms();    
      
  };
} // main