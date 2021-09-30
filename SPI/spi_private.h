/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <spi_private.h>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <29 - 9 - 2021>
 *
 * [DESCRIPTION]: <Private header file for SPI driver for STM32F429>
 * ---------------------------------------------------------------------------------------------------
 */
 
 
#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

//STM32F429 contains 6 SPI modules



#ifndef NULL_PTR
#define NULL_PTR        (void*) 0
#endif


/*---------------- Register Definition -------------------*/

/*---------------- Base addresses -------------------*/
#define SPI1_BASE_ADDRESS				(0x40013000) // APB2 bus
#define SPI3_BASE_ADDRESS				(0x40003C00) // APB1 bus
#define SPI2_BASE_ADDRESS				(0x40003800) // APB1 bus
#define SPI4_BASE_ADDRESS				(0x40013400) // APB2 bus
#define SPI5_BASE_ADDRESS				(0x40015000) // APB2 bus
#define SPI6_BASE_ADDRESS				(0x40015400) // APB2 bus


/*---------------- SPI1 Registers -------------------*/
#define SPI1_CR1 						(*(volatile uint32*) (SPI1_BASE_ADDRESS + 0x00))
#define SPI1_CR2 						(*(volatile uint32*) (SPI1_BASE_ADDRESS + 0x04))
#define SPI1_SR 						(*(volatile uint32*) (SPI1_BASE_ADDRESS + 0x08))
#define SPI1_DR 						(*(volatile uint32*) (SPI1_BASE_ADDRESS + 0x0C))

/*---------------- SPI2 Registers -------------------*/
#define SPI2_CR1 						(*(volatile uint32*) (SPI2_BASE_ADDRESS + 0x00))
#define SPI2_CR2 						(*(volatile uint32*) (SPI2_BASE_ADDRESS + 0x04))
#define SPI2_SR 						(*(volatile uint32*) (SPI2_BASE_ADDRESS + 0x08))
#define SPI2_DR 						(*(volatile uint32*) (SPI2_BASE_ADDRESS + 0x0C))

/*---------------- SPI3 Registers -------------------*/
#define SPI3_CR1 						(*(volatile uint32*) (SPI3_BASE_ADDRESS + 0x00))
#define SPI3_CR2 						(*(volatile uint32*) (SPI3_BASE_ADDRESS + 0x04))
#define SPI3_SR 						(*(volatile uint32*) (SPI3_BASE_ADDRESS + 0x08))
#define SPI3_DR 						(*(volatile uint32*) (SPI3_BASE_ADDRESS + 0x0C))

/*---------------- SPI4 Registers -------------------*/
#define SPI4_CR1 						(*(volatile uint32*) (SPI4_BASE_ADDRESS + 0x00))
#define SPI4_CR2 						(*(volatile uint32*) (SPI4_BASE_ADDRESS + 0x04))
#define SPI4_SR 						(*(volatile uint32*) (SPI4_BASE_ADDRESS + 0x08))
#define SPI4_DR 						(*(volatile uint32*) (SPI4_BASE_ADDRESS + 0x0C))


/*---------------- SPI5 Registers -------------------*/
#define SPI5_CR1 						(*(volatile uint32*) (SPI5_BASE_ADDRESS + 0x00))
#define SPI5_CR2 						(*(volatile uint32*) (SPI5_BASE_ADDRESS + 0x04))
#define SPI5_SR 						(*(volatile uint32*) (SPI5_BASE_ADDRESS + 0x08))
#define SPI5_DR 						(*(volatile uint32*) (SPI5_BASE_ADDRESS + 0x0C))

/*---------------- SPI6 Registers -------------------*/
#define SPI6_CR1 						(*(volatile uint32*) (SPI6_BASE_ADDRESS + 0x00))
#define SPI6_CR2 						(*(volatile uint32*) (SPI6_BASE_ADDRESS + 0x04))
#define SPI6_SR 						(*(volatile uint32*) (SPI6_BASE_ADDRESS + 0x08))
#define SPI6_DR 						(*(volatile uint32*) (SPI6_BASE_ADDRESS + 0x0C))


/*---------------- SPI Macros -------------------*/

/*---------------- SPI_u8ModuleNumber -------------------*/
#define SPI1 				(1UL)
#define SPI2 				(2UL)
#define SPI3 				(3UL)
#define SPI4 				(4UL)
#define SPI5 				(5UL)
#define SPI6 				(6UL)


/*---------------- SPI_u8DeviceMode -------------------*/
#define SPI_MASTER			(0UL)
#define SPI_SLAVE			(1UL)

/*---------------- SPI_u8ClockMode -------------------*/
									//		Polarity		  Phase
#define SPI_CLOCK_MODE1		(0UL)	//			0				0	
#define SPI_CLOCK_MODE2		(1UL)	//			0				1
#define SPI_CLOCK_MODE3		(2UL)	//			1				0
#define SPI_CLOCK_MODE4		(3UL)	//			1				1


/*---------------- SPI_u8DataSize -------------------*/
#define SPI_DATA_SIZE_8			(0UL)
#define SPI_DATA_SIZE_16		(1UL)


/*---------------- SPI_u8DataDirection -------------------*/
#define SPI_DATA_DIR_MSB		(0UL)
#define SPI_DATA_DIR_LSB		(1UL)


/*---------------- SPI_u8NssMode -------------------*/
#define SPI_NSS_MODE_SW			(0UL)
#define SPI_NSS_MODE_HW			(1UL)

/*---------------- SPI_u8BiDiMode -------------------*/
#define SPI_BI_DIRECTIONAL_MODE_1_LINE		(1UL)
#define SPI_BI_DIRECTIONAL_MODE_2_LINES		(0UL)


/*---------------- SPI_u8BaudRate -------------------*/
#define SPI_BAUD_RATE_0				(0UL)			// FCLK / 2
#define SPI_BAUD_RATE_1				(1UL)			// FCLK / 4
#define SPI_BAUD_RATE_2				(2UL)			// FCLK / 8
#define SPI_BAUD_RATE_3				(3UL)			// FCLK / 16
#define SPI_BAUD_RATE_4				(4UL)			// FCLK / 32
#define SPI_BAUD_RATE_5				(5UL)			// FCLK / 64
#define SPI_BAUD_RATE_6				(6UL)			// FCLK / 128
#define SPI_BAUD_RATE_7				(7UL)			// FCLK / 256

/*---------------- SPI_u8InterruptEnableDevice -------------------*/
#define SPI_RX_ONLY					(1UL)
#define SPI_TX_ONLY					(2UL)
#define SPI_BOTH_RX_TX				(3UL)


#endif
