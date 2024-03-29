/* ###################################################################
**     Filename    : main.c
**     Project     : minicurso-eeprom-driver
**     Processor   : MKL16Z128VLH4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-06-10, 10:20, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "clockMan1.h"
#include "pin_mux.h"
#include "osa1.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */

#include "FreeRTOS.h"
#include "task.h"
#include "EEPROM/S25FL1K/Driver.h"
#include "Utils/Utils.h"

void task(void* param)
{
	uint8_t data[] = "Ol�, mundo! Este �, poss�velmente, o meu primeiro device driver embarcado!";

	uint8_t read_buffer[sizeof(data)] = {0x0};

	// Interface de comunica��o SPI
	SPIInterface interface(spiEEPROM_IDX, spiEEPROM_MasterConfig0);

	// Canal de comunica��o exclusivo com a mem�ria, segue o padr�o de projeto "decorator"
	SPICommunicationChannel communication_channel(interface, OutputPort<Port>(SPI_CS));

	EEPROM::S25FL1K::Driver driver(communication_channel, EE_VCC_CTRL);

	driver.turn_on();

	driver.read(0, read_buffer, sizeof(read_buffer));

	driver.store(0, data, sizeof(data));

	driver.read(0, read_buffer, sizeof(read_buffer));

	driver.erase_sector(0);

	driver.read(0, read_buffer, sizeof(read_buffer));

	for(;;)
	{
		COP_DRV_Refresh(cop1_IDX);
		vTaskDelay(1000);
	}
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  TaskHandle_t handle;

  BaseType_t rc = xTaskCreate(task,
                              "teste",
                              configMINIMAL_STACK_SIZE * 5,
                              nullptr,
                              tskIDLE_PRIORITY,
                              &handle);

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
