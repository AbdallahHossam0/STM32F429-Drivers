/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <spi.h>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <29 - 9 - 2021>
 *
 * [DESCRIPTION]: <Header file for SPI driver for STM32F429>
 * ---------------------------------------------------------------------------------------------------
 */
 
#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "common_macros.h"
#include "spi_private.h"

/*---------------- SPI Data Types -----------------*/

typedef struct{
	uint8 SPI_u8ModuleNumber;
	uint8 SPI_u8DeviceMode;
	uint8 SPI_u8ClockMode;
	uint8 SPI_u8DataSize;
	uint8 SPI_u8DataDirection;
	uint8 SPI_u8NssMode;
	uint8 SPI_u8BaudRate;
	uint8 SPI_u8BiDiMode;
}SPI_ConfigType;


/*-------------- Function Prototypes ---------------*/ 
void SPI_vInit(SPI_ConfigType* config);
void SPI_vEnable(uint8 SPI_u8ModuleNumber);
void SPI_vDisable(uint8 SPI_u8ModuleNumber);

void SPI_vInterruptEnable(uint8 SPI_u8ModuleNumber, uint8 SPI_u8InterruptEnableDevice);
void SPI_vSetCallBack(uint8 SPI_u8ModuleNumber, void (*SPI_TX_InterruptFunction)(void), void (*SPI_RX_InterruptFunction)(void));

void SPI_vSendString(uint8 SPI_u8ModuleNumber, uint8* str);
void SPI_vSendData(uint8 SPI_u8ModuleNumber, uint16 u16data);
uint16 SPI_u16ReceiveData(uint8 SPI_u8ModuleNumber);

#endif
