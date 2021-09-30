/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <spi.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <29 - 9 - 2021>
 *
 * [DESCRIPTION]: <Source file for SPI driver for STM32F429>
 * ---------------------------------------------------------------------------------------------------
 */

#include "spi.h"



/*--------------------------- Array of pointers to functions for call back -------------------------*/
volatile void (*SPI_TX_InterruptHandler[6])(void) = {NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR};
volatile void (*SPI_RX_InterruptHandler[6])(void) = {NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR};



/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:				SPI_vInit
 *
 * [DESCRIPTION]:				Function to initialize SPI module on STM boared.
 * 								Before you initialize it you have to set the clock to the module by RCC module.
 *								Also you need to select the alternative function to the pins used from the GPIO driver.
 *
 * [Args]:						SPI_ConfigType* config
 *
 * [IN]:						SPI_ConfigType* config
 * 								A pointer to structure has all configurations you need.
 *
 * [OUT]:						None.
 *
 * [IN / OUT]:					None.
 *
 * [RETURNS]:					Void.
 * ---------------------------------------------------------------------------------------------------
 */
void SPI_vInit(SPI_ConfigType* config){

	switch(config -> SPI_u8ModuleNumber){
	case SPI1:

		// Set the device mode
		switch(config -> SPI_u8DeviceMode){
		case SPI_MASTER:
			SPI1_CR1 |= 1 << 2;
			break;
		case SPI_SLAVE:
			SPI1_CR1 &= ~(1 << 2);
			break;
		default:
			break;
		}

		// Set the device clock mode

		switch(config -> SPI_u8ClockMode){
		case SPI_CLOCK_MODE1:
			//Set the phase and the polarity to 0
			SPI1_CR1 &= ~(1 << 0);
			SPI1_CR1 &= ~(1 << 1);
			break;
		case SPI_CLOCK_MODE2:
			SPI1_CR1 &= ~(1 << 0);
			SPI1_CR1 |= 1 << 1;
			break;
		case SPI_CLOCK_MODE3:
			SPI1_CR1 &= ~(1 << 1);
			SPI1_CR1 |= 1 << 0;
			break;
		case SPI_CLOCK_MODE4:
			SPI1_CR1 |= 1 << 0;
			SPI1_CR1 |= 1 << 1;
			break;
		default: break;
		}

		// To set the data size
		switch(config -> SPI_u8DataSize){
		case SPI_DATA_SIZE_8:	SPI1_CR1 &= ~(1 << 11);	break;
		case SPI_DATA_SIZE_16:	SPI1_CR1 |= 1 << 11; 	break;
		default: break;
		}

		// Set the direction of transfer (To start with MSB or with LSB)
		switch(config -> SPI_u8DataDirection){
		case SPI_DATA_DIR_MSB:	SPI1_CR1 &= ~(1 << 7);	break;
		case SPI_DATA_DIR_LSB:	SPI1_CR1 |= 1 << 7; 	break;
		default: break;
		}


		if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
			SPI1_CR1 |= 1 << 9;
			SPI1_CR1 |= 1 << 8;
		}
		else if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
			SPI1_CR1 &= ~(1 << 9);
		}
		else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
			SPI1_CR1 |= 1 << 9;
		}
		else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
			SPI1_CR1 &= ~(1 << 9);
		}
		else{}


		// Set the baud rate
		SPI1_CR1 &= ~(1 << 3);
		SPI1_CR1 &= ~(1 << 4);
		SPI1_CR1 &= ~(1 << 5);
		SPI1_CR1 |= (config -> SPI_u8BaudRate << 3);

		// Set the Bidirectional mode
		SPI1_CR1 &= ~(1 << 15);
		SPI1_CR1 |= (config -> SPI_u8BiDiMode << 15);

		break;
		case SPI2:
			// Set the device mode
			switch(config -> SPI_u8DeviceMode){
			case SPI_MASTER:
				SPI2_CR1 |= 1 << 2;
				break;
			case SPI_SLAVE:
				SPI2_CR1 &= ~(1 << 2);
				break;
			default:
				break;
			}

			// Set the device clock mode

			switch(config -> SPI_u8ClockMode){
			case SPI_CLOCK_MODE1:
				//Set the phase and the polarity to 0
				SPI2_CR1 &= ~(1 << 0);
				SPI2_CR1 &= ~(1 << 1);
				break;
			case SPI_CLOCK_MODE2:
				SPI2_CR1 &= ~(1 << 0);
				SPI2_CR1 |= 1 << 1;
				break;
			case SPI_CLOCK_MODE3:
				SPI2_CR1 &= ~(1 << 1);
				SPI2_CR1 |= 1 << 0;
				break;
			case SPI_CLOCK_MODE4:
				SPI2_CR1 |= 1 << 0;
				SPI2_CR1 |= 1 << 1;
				break;
			default: break;
			}

			// To set the data size
			switch(config -> SPI_u8DataSize){
			case SPI_DATA_SIZE_8:	SPI2_CR1 &= ~(1 << 11);	break;
			case SPI_DATA_SIZE_16:	SPI2_CR1 |= 1 << 11; 	break;
			default: break;
			}

			// Set the direction of transfer (To start with MSB or with LSB)
			switch(config -> SPI_u8DataDirection){
			case SPI_DATA_DIR_MSB:	SPI2_CR1 &= ~(1 << 7);	break;
			case SPI_DATA_DIR_LSB:	SPI2_CR1 |= 1 << 7; 	break;
			default: break;
			}


			if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
				SPI2_CR1 |= 1 << 9;
				SPI2_CR1 |= 1 << 8;
			}
			else if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
				SPI2_CR1 &= ~(1 << 9);
			}
			else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
				SPI2_CR1 |= 1 << 9;
			}
			else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
				SPI2_CR1 &= ~(1 << 9);
			}
			else{}


			// Set the baud rate
			SPI2_CR1 &= ~(1 << 3);
			SPI2_CR1 &= ~(1 << 4);
			SPI2_CR1 &= ~(1 << 5);
			SPI2_CR1 |= (config -> SPI_u8BaudRate << 3);

			// Set the Bidirectional mode
			SPI2_CR1 &= ~(1 << 15);
			SPI2_CR1 |= (config -> SPI_u8BiDiMode << 15);

			break;
			case SPI3:
				// Set the device mode
				switch(config -> SPI_u8DeviceMode){
				case SPI_MASTER:
					SPI3_CR1 |= 1 << 2;
					break;
				case SPI_SLAVE:
					SPI3_CR1 &= ~(1 << 2);
					break;
				default:
					break;
				}

				// Set the device clock mode

				switch(config -> SPI_u8ClockMode){
				case SPI_CLOCK_MODE1:
					//Set the phase and the polarity to 0
					SPI3_CR1 &= ~(1 << 0);
					SPI3_CR1 &= ~(1 << 1);
					break;
				case SPI_CLOCK_MODE2:
					SPI3_CR1 &= ~(1 << 0);
					SPI3_CR1 |= 1 << 1;
					break;
				case SPI_CLOCK_MODE3:
					SPI3_CR1 &= ~(1 << 1);
					SPI3_CR1 |= 1 << 0;
					break;
				case SPI_CLOCK_MODE4:
					SPI3_CR1 |= 1 << 0;
					SPI3_CR1 |= 1 << 1;
					break;
				default: break;
				}

				// To set the data size
				switch(config -> SPI_u8DataSize){
				case SPI_DATA_SIZE_8:	SPI3_CR1 &= ~(1 << 11);	break;
				case SPI_DATA_SIZE_16:	SPI3_CR1 |= 1 << 11; 	break;
				default: break;
				}

				// Set the direction of transfer (To start with MSB or with LSB)
				switch(config -> SPI_u8DataDirection){
				case SPI_DATA_DIR_MSB:	SPI3_CR1 &= ~(1 << 7);	break;
				case SPI_DATA_DIR_LSB:	SPI3_CR1 |= 1 << 7; 	break;
				default: break;
				}


				if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
					SPI3_CR1 |= 1 << 9;
					SPI3_CR1 |= 1 << 8;
				}
				else if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
					SPI3_CR1 &= ~(1 << 9);
				}
				else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
					SPI3_CR1 |= 1 << 9;
				}
				else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
					SPI3_CR1 &= ~(1 << 9);
				}
				else{}


				// Set the baud rate
				SPI3_CR1 &= ~(1 << 3);
				SPI3_CR1 &= ~(1 << 4);
				SPI3_CR1 &= ~(1 << 5);
				SPI3_CR1 |= (config -> SPI_u8BaudRate << 3);

				// Set the Bidirectional mode
				SPI3_CR1 &= ~(1 << 15);
				SPI3_CR1 |= (config -> SPI_u8BiDiMode << 15);

				break;
				case SPI4:
					// Set the device mode
					switch(config -> SPI_u8DeviceMode){
					case SPI_MASTER:
						SPI4_CR1 |= 1 << 2;
						break;
					case SPI_SLAVE:
						SPI4_CR1 &= ~(1 << 2);
						break;
					default:
						break;
					}

					// Set the device clock mode

					switch(config -> SPI_u8ClockMode){
					case SPI_CLOCK_MODE1:
						//Set the phase and the polarity to 0
						SPI4_CR1 &= ~(1 << 0);
						SPI4_CR1 &= ~(1 << 1);
						break;
					case SPI_CLOCK_MODE2:
						SPI4_CR1 &= ~(1 << 0);
						SPI4_CR1 |= 1 << 1;
						break;
					case SPI_CLOCK_MODE3:
						SPI4_CR1 &= ~(1 << 1);
						SPI4_CR1 |= 1 << 0;
						break;
					case SPI_CLOCK_MODE4:
						SPI4_CR1 |= 1 << 0;
						SPI4_CR1 |= 1 << 1;
						break;
					default: break;
					}

					// To set the data size
					switch(config -> SPI_u8DataSize){
					case SPI_DATA_SIZE_8:	SPI4_CR1 &= ~(1 << 11);	break;
					case SPI_DATA_SIZE_16:	SPI4_CR1 |= 1 << 11; 	break;
					default: break;
					}

					// Set the direction of transfer (To start with MSB or with LSB)
					switch(config -> SPI_u8DataDirection){
					case SPI_DATA_DIR_MSB:	SPI4_CR1 &= ~(1 << 7);	break;
					case SPI_DATA_DIR_LSB:	SPI4_CR1 |= 1 << 7; 	break;
					default: break;
					}


					if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
						SPI4_CR1 |= 1 << 9;
						SPI4_CR1 |= 1 << 8;
					}
					else if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
						SPI4_CR1 &= ~(1 << 9);
					}
					else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
						SPI4_CR1 |= 1 << 9;
					}
					else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
						SPI4_CR1 &= ~(1 << 9);
					}
					else{}


					// Set the baud rate
					SPI4_CR1 &= ~(1 << 3);
					SPI4_CR1 &= ~(1 << 4);
					SPI4_CR1 &= ~(1 << 5);
					SPI4_CR1 |= (config -> SPI_u8BaudRate << 3);

					// Set the Bidirectional mode
					SPI4_CR1 &= ~(1 << 15);
					SPI4_CR1 |= (config -> SPI_u8BiDiMode << 15);
					break;

					case SPI5:
						// Set the device mode
						switch(config -> SPI_u8DeviceMode){
						case SPI_MASTER:
							SPI5_CR1 |= 1 << 2;
							break;
						case SPI_SLAVE:
							SPI5_CR1 &= ~(1 << 2);
							break;
						default:
							break;
						}

						// Set the device clock mode

						switch(config -> SPI_u8ClockMode){
						case SPI_CLOCK_MODE1:
							//Set the phase and the polarity to 0
							SPI5_CR1 &= ~(1 << 0);
							SPI5_CR1 &= ~(1 << 1);
							break;
						case SPI_CLOCK_MODE2:
							SPI5_CR1 &= ~(1 << 0);
							SPI5_CR1 |= 1 << 1;
							break;
						case SPI_CLOCK_MODE3:
							SPI5_CR1 &= ~(1 << 1);
							SPI5_CR1 |= 1 << 0;
							break;
						case SPI_CLOCK_MODE4:
							SPI5_CR1 |= 1 << 0;
							SPI5_CR1 |= 1 << 1;
							break;
						default: break;
						}

						// To set the data size
						switch(config -> SPI_u8DataSize){
						case SPI_DATA_SIZE_8:	SPI5_CR1 &= ~(1 << 11);	break;
						case SPI_DATA_SIZE_16:	SPI5_CR1 |= 1 << 11; 	break;
						default: break;
						}

						// Set the direction of transfer (To start with MSB or with LSB)
						switch(config -> SPI_u8DataDirection){
						case SPI_DATA_DIR_MSB:	SPI5_CR1 &= ~(1 << 7);	break;
						case SPI_DATA_DIR_LSB:	SPI5_CR1 |= 1 << 7; 	break;
						default: break;
						}


						if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
							SPI5_CR1 |= 1 << 9;
							SPI5_CR1 |= 1 << 8;
						}
						else if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
							SPI5_CR1 &= ~(1 << 9);
						}
						else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
							SPI5_CR1 |= 1 << 9;
						}
						else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
							SPI5_CR1 &= ~(1 << 9);
						}
						else{}


						// Set the baud rate
						SPI5_CR1 &= ~(1 << 3);
						SPI5_CR1 &= ~(1 << 4);
						SPI5_CR1 &= ~(1 << 5);
						SPI5_CR1 |= (config -> SPI_u8BaudRate << 3);

						// Set the Bidirectional mode
						SPI5_CR1 &= ~(1 << 15);
						SPI5_CR1 |= (config -> SPI_u8BiDiMode << 15);
						break;

						case SPI6:
							// Set the device mode
							switch(config -> SPI_u8DeviceMode){
							case SPI_MASTER:
								SPI6_CR1 |= 1 << 2;
								break;
							case SPI_SLAVE:
								SPI6_CR1 &= ~(1 << 2);
								break;
							default:
								break;
							}

							// Set the device clock mode

							switch(config -> SPI_u8ClockMode){
							case SPI_CLOCK_MODE1:
								//Set the phase and the polarity to 0
								SPI6_CR1 &= ~(1 << 0);
								SPI6_CR1 &= ~(1 << 1);
								break;
							case SPI_CLOCK_MODE2:
								SPI6_CR1 &= ~(1 << 0);
								SPI6_CR1 |= 1 << 1;
								break;
							case SPI_CLOCK_MODE3:
								SPI6_CR1 &= ~(1 << 1);
								SPI6_CR1 |= 1 << 0;
								break;
							case SPI_CLOCK_MODE4:
								SPI6_CR1 |= 1 << 0;
								SPI6_CR1 |= 1 << 1;
								break;
							default: break;
							}

							// To set the data size
							switch(config -> SPI_u8DataSize){
							case SPI_DATA_SIZE_8:	SPI6_CR1 &= ~(1 << 11);	break;
							case SPI_DATA_SIZE_16:	SPI6_CR1 |= 1 << 11; 	break;
							default: break;
							}

							// Set the direction of transfer (To start with MSB or with LSB)
							switch(config -> SPI_u8DataDirection){
							case SPI_DATA_DIR_MSB:	SPI6_CR1 &= ~(1 << 7);	break;
							case SPI_DATA_DIR_LSB:	SPI6_CR1 |= 1 << 7; 	break;
							default: break;
							}


							if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
								SPI6_CR1 |= 1 << 9;
								SPI6_CR1 |= 1 << 8;
							}
							else if(config -> SPI_u8DeviceMode == SPI_MASTER && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
								SPI6_CR1 &= ~(1 << 9);
							}
							else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_SW){
								SPI6_CR1 |= 1 << 9;
							}
							else if(config -> SPI_u8DeviceMode == SPI_SLAVE && config -> SPI_u8NssMode == SPI_NSS_MODE_HW){
								SPI6_CR1 &= ~(1 << 9);
							}
							else{}


							// Set the baud rate
							SPI6_CR1 &= ~(1 << 3);
							SPI6_CR1 &= ~(1 << 4);
							SPI6_CR1 &= ~(1 << 5);
							SPI6_CR1 |= (config -> SPI_u8BaudRate << 3);

							// Set the Bidirectional mode
							SPI6_CR1 &= ~(1 << 15);
							SPI6_CR1 |= (config -> SPI_u8BiDiMode << 15);
							break;
	}
}



/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:				SPI_vEnable
 *
 * [DESCRIPTION]:				Function to enable a certain SPI module.
 *
 * [Args]:						uint8 SPI_u8ModuleNumber
 *
 * [IN]:						SPI_u8ModuleNumber: Variable to inform the function.
 * 								Available values: SPI1 - SPI2 - SPI3 - SPI4 - SPI5 - SPI6
 *
 * [OUT]:						None.
 *
 * [IN / OUT]:					None.
 *
 * [RETURNS]:					Void.
 * ---------------------------------------------------------------------------------------------------
 */
void SPI_vEnable(uint8 SPI_u8ModuleNumber){
	switch(SPI_u8ModuleNumber){
	case SPI1:	SPI1_CR1 |= 1 << 6; 	break;
	case SPI2:	SPI2_CR1 |= 1 << 6; 	break;
	case SPI3:	SPI3_CR1 |= 1 << 6; 	break;
	case SPI4:	SPI4_CR1 |= 1 << 6; 	break;
	case SPI5:	SPI5_CR1 |= 1 << 6; 	break;
	case SPI6:	SPI6_CR1 |= 1 << 6; 	break;
	default: break;
	}
}



/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:				SPI_vDisable
 *
 * [DESCRIPTION]:				Function to disable a certain SPI module.
 *
 * [Args]:						uint8 SPI_u8ModuleNumber
 *
 * [IN]:						SPI_u8ModuleNumber: Variable to inform the function
 * 								Available values: SPI1 - SPI2 - SPI3 - SPI4 - SPI5 - SPI6
 *
 * [OUT]:						None.
 *
 * [IN / OUT]:					None.
 *
 * [RETURNS]:					Void.
 * ---------------------------------------------------------------------------------------------------
 */
void SPI_vDisable(uint8 SPI_u8ModuleNumber){
	switch(SPI_u8ModuleNumber){
	case SPI1:	SPI1_CR1 &= ~(1 << 6); 	break;
	case SPI2:	SPI2_CR1 &= ~(1 << 6); 	break;
	case SPI3:	SPI3_CR1 &= ~(1 << 6); 	break;
	case SPI4:	SPI4_CR1 &= ~(1 << 6); 	break;
	case SPI5:	SPI5_CR1 &= ~(1 << 6); 	break;
	case SPI6:	SPI6_CR1 &= ~(1 << 6); 	break;
	default: break;
	}
}



/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:			SPI_vSendData
 *
 * [DESCRIPTION]:			Function to send data by the SPI.
 *
 * [Args]:					uint8 SPI_u8ModuleNumber, uint16 u16data.
 *
 * [IN]:					SPI_u8ModuleNumber: A variable to specify which SPI to send the data through.
 * 							u16data:  			A variable to contain the data to be sent.
 *
 * [OUT]:					None.
 *
 * [IN / OUT]:				None.
 *
 * [RETURNS]:				Void.
 * ---------------------------------------------------------------------------------------------------
 */
void SPI_vSendData(uint8 SPI_u8ModuleNumber, uint16 u16data){
	switch(SPI_u8ModuleNumber){
	case SPI1:
		while((SPI1_SR & ((1 << 1) | (1 << 0))) || (SPI1_SR & (1 << 7)));
		SPI1_DR = u16data;
		break;

	case SPI2:
		while((SPI2_SR & ((1 << 1) | (1 << 0))) || (SPI2_SR & (1 << 7)));
		SPI2_DR = u16data;
		break;

	case SPI3:
		while((SPI3_SR & ((1 << 1) | (1 << 0))) || (SPI3_SR & (1 << 7)));
		SPI3_DR = u16data;
		break;

	case SPI4:
		while((SPI4_SR & ((1 << 1) | (1 << 0))) || (SPI4_SR & (1 << 7)));
		SPI4_DR = u16data;
		break;
	case SPI5:
		while((SPI5_SR & ((1 << 1) | (1 << 0))) || (SPI5_SR & (1 << 7)));
		SPI5_DR = u16data;
		break;

	case SPI6:
		while((SPI6_SR & ((1 << 1) | (1 << 0))) || (SPI6_SR & (1 << 7)));
		SPI6_DR = u16data;
		break;
	default: break;
	}
}



/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:				SPI_vSendString
 *
 * [DESCRIPTION]:				Function to pass a string with the SPI.
 *
 * [Args]:						uint8 SPI_u8ModuleNumber, uint8* str
 *
 * [IN]:						SPI_u8ModuleNumber: contains the SPI channel used to send the data.
 * 								str : pointer to char points to the string you want to send.
 *
 * [OUT]:						None.
 *
 * [IN / OUT]:					None.
 *
 * [RETURNS]:					Void.
 * ---------------------------------------------------------------------------------------------------
 */
void SPI_vSendString(uint8 SPI_u8ModuleNumber, uint8* str){
	while(*str != '\0'){
		SPI_vSendData(SPI_u8ModuleNumber, *str++);
	}
}

/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:			SPI_u16ReceiveData
 *
 * [DESCRIPTION]:			Function to receive data from the SPI
 *
 * [Args]:					uint8 SPI_u8ModuleNumber
 *
 * [IN]:					SPI_u8ModuleNumber: to specify which channel you want to receive the data from.
 *
 * [OUT]:					None.
 *
 * [IN / OUT]:				None.
 *
 * [RETURNS]:				uint16
 * 							return the data SPI module received.
 * ---------------------------------------------------------------------------------------------------
 */
uint16 SPI_u16ReceiveData(uint8 SPI_u8ModuleNumber){
	switch(SPI_u8ModuleNumber){
	case SPI1:
		while(BIT_IS_CLEAR(SPI1_SR, 0));
		return SPI1_DR;
		break;

	case SPI2:
		while(BIT_IS_CLEAR(SPI2_SR, 0));
		return SPI2_DR;
		break;

	case SPI3:
		while(BIT_IS_CLEAR(SPI3_SR, 0));
		return SPI3_DR;
		break;

	case SPI4:
		while(BIT_IS_CLEAR(SPI4_SR, 0));
		return SPI4_DR;
		break;
	case SPI5:
		while(BIT_IS_CLEAR(SPI5_SR, 0));
		return SPI5_DR;
		break;

	case SPI6:
		while(BIT_IS_CLEAR(SPI6_SR, 0));
		return SPI6_DR;
		break;
	default: return 0x00; break;
	}
}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:					SPI_vInterruptEnable
 *
 * [DESCRIPTION]:					Function to enable interrupts for SPI.
 *
 * [Args]:							uint8 SPI_u8ModuleNumber,
 * 									uint8 SPI_u8InterruptEnableDevice.
 *
 * [IN]:							SPI_u8ModuleNumber: To specify the module number.
 * 									SPI_u8InterruptEnableDevice: To choose to enable the interrupts
 * 									for each device.
 * 									**Available values => SPI_RX_ONLY - SPI_TX_ONLY - SPI_BOTH_RX_TX.
 *
 * [OUT]:							None.
 *
 * [IN / OUT]:						None.
 *
 * [RETURNS]:						None.
 * ---------------------------------------------------------------------------------------------------
 */
void SPI_vInterruptEnable(uint8 SPI_u8ModuleNumber, uint8 SPI_u8InterruptEnableDevice){
	switch (SPI_u8ModuleNumber){
	case SPI1:
		CLEAR_BIT(SPI1_CR2, 6);
		CLEAR_BIT(SPI1_CR2, 7);
		SPI1_CR2 |= (SPI_u8InterruptEnableDevice << 6);
		break;
	case SPI2:
		CLEAR_BIT(SPI2_CR2, 6);
		CLEAR_BIT(SPI2_CR2, 7);
		SPI2_CR2 |= (SPI_u8InterruptEnableDevice << 6);
		break;
	case SPI3:
		CLEAR_BIT(SPI3_CR2, 6);
		CLEAR_BIT(SPI3_CR2, 7);
		SPI3_CR2 |= (SPI_u8InterruptEnableDevice << 6);
		break;
	case SPI4:
		CLEAR_BIT(SPI4_CR2, 6);
		CLEAR_BIT(SPI4_CR2, 7);
		SPI4_CR2 |= (SPI_u8InterruptEnableDevice << 6);
		break;
	case SPI5:
		CLEAR_BIT(SPI5_CR2, 6);
		CLEAR_BIT(SPI5_CR2, 7);
		SPI5_CR2 |= (SPI_u8InterruptEnableDevice << 6);
		break;
	case SPI6:
		CLEAR_BIT(SPI6_CR2, 6);
		CLEAR_BIT(SPI6_CR2, 7);
		SPI6_CR2 |= (SPI_u8InterruptEnableDevice << 6);
		break;
	default: break;
	}
}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:				SPI_vSetCallBack
 *
 * [DESCRIPTION]:				Function to set the call back pointers to the avaliable functions.
 *
 * [Args]:						uint8 SPI_u8ModuleNumber,
 * 								void (*SPI_TX_InterruptFunction)(void),
 * 								void (*SPI_RX_InterruptFunction)(void).
 *
 * [IN]:						SPI_u8ModuleNumber: To specify the module number.
 * 								void (*SPI_TX_InterruptFunction)(void): A pointer to TX interrupt function.
 * 								** Pass it to {NULL_PTR} if you do not want to use this variable.
 * 								void (*SPI_RX_InterruptFunction)(void): A pointer to TX interrupt function.
 * 								** Pass it to {NULL_PTR} if you do not want to use this variable.
 *
 * [OUT]:						None.
 *
 * [IN / OUT]:					None.
 *
 * [RETURNS]:					Void.
 * ---------------------------------------------------------------------------------------------------
 */
void SPI_vSetCallBack(uint8 SPI_u8ModuleNumber, void (*SPI_TX_InterruptFunction)(void), void (*SPI_RX_InterruptFunction)(void)){
	switch (SPI_u8ModuleNumber){
	case SPI1:
		SPI_TX_InterruptHandler[0] = SPI_TX_InterruptFunction;
		SPI_RX_InterruptHandler[0] = SPI_RX_InterruptFunction;
		break;
	case SPI2:
		SPI_TX_InterruptHandler[1] = SPI_TX_InterruptFunction;
		SPI_RX_InterruptHandler[1] = SPI_RX_InterruptFunction;
		break;
	case SPI3:
		SPI_TX_InterruptHandler[2] = SPI_TX_InterruptFunction;
		SPI_RX_InterruptHandler[2] = SPI_RX_InterruptFunction;
		break;
	case SPI4:
		SPI_TX_InterruptHandler[3] = SPI_TX_InterruptFunction;
		SPI_RX_InterruptHandler[3] = SPI_RX_InterruptFunction;
		break;
	case SPI5:
		SPI_TX_InterruptHandler[4] = SPI_TX_InterruptFunction;
		SPI_RX_InterruptHandler[4] = SPI_RX_InterruptFunction;
		break;
	case SPI6:
		SPI_TX_InterruptHandler[5] = SPI_TX_InterruptFunction;
		SPI_RX_InterruptHandler[5] = SPI_RX_InterruptFunction;
		break;
	default: break;
	}

}


/*---------------- Interrupt Handler for each Channel -------------------*/
void SPI1_InterruptHandler(void){
	if(BIT_IS_SET(SPI1_SR, 1)){
		if(SPI_TX_InterruptHandler[0] != NULL_PTR) { SPI_TX_InterruptHandler[0](); }
		else{	}
	}
	else if(BIT_IS_SET(SPI1_SR, 0)){
		if(SPI_RX_InterruptHandler[0] != NULL_PTR) { SPI_RX_InterruptHandler[0](); }
		else{	}
	}
	else{	}
}

void SPI2_InterruptHandler(void){
	if(BIT_IS_SET(SPI2_SR, 1)){
		if(SPI_TX_InterruptHandler[1] != NULL_PTR) { SPI_TX_InterruptHandler[1](); }
		else{	}
	}
	else if(BIT_IS_SET(SPI2_SR, 0)){
		if(SPI_RX_InterruptHandler[1] != NULL_PTR) { SPI_RX_InterruptHandler[1](); }
		else{	}
	}
	else{	}
}

void SPI3_InterruptHandler(void){
	if(BIT_IS_SET(SPI3_SR, 1)){
		if(SPI_TX_InterruptHandler[2] != NULL_PTR) { SPI_TX_InterruptHandler[2](); }
		else{	}
	}
	else if(BIT_IS_SET(SPI3_SR, 0)){
		if(SPI_RX_InterruptHandler[2] != NULL_PTR) { SPI_RX_InterruptHandler[2](); }
		else{	}
	}
	else{	}
}

void SPI4_InterruptHandler(void){
	if(BIT_IS_SET(SPI4_SR, 1)){
		if(SPI_TX_InterruptHandler[3] != NULL_PTR) { SPI_TX_InterruptHandler[3](); }
		else{	}
	}
	else if(BIT_IS_SET(SPI4_SR, 0)){
		if(SPI_RX_InterruptHandler[3] != NULL_PTR) { SPI_RX_InterruptHandler[3](); }
		else{	}
	}
	else{	}
}

void SPI5_InterruptHandler(void){
	if(BIT_IS_SET(SPI5_SR, 1)){
		if(SPI_TX_InterruptHandler[4] != NULL_PTR) { SPI_TX_InterruptHandler[4](); }
		else{	}
	}
	else if(BIT_IS_SET(SPI5_SR, 0)){
		if(SPI_RX_InterruptHandler[4] != NULL_PTR) { SPI_RX_InterruptHandler[4](); }
		else{	}
	}
	else{	}
}

void SPI6_InterruptHandler(void){
	if(BIT_IS_SET(SPI6_SR, 1)){
		if(SPI_TX_InterruptHandler[5] != NULL_PTR) { SPI_TX_InterruptHandler[5](); }
		else{	}
	}
	else if(BIT_IS_SET(SPI6_SR, 0)){
		if(SPI_RX_InterruptHandler[5] != NULL_PTR) { SPI_RX_InterruptHandler[5](); }
		else{	}
	}
	else{	}
}

