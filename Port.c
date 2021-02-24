/*
 * Port.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Aya Hussein
 */
#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

STATIC uint8 Port_mapToRegChannelNum (Port_PinType,uint8*, uint8*);

STATIC Port_ConfigChannel *Port_ArrPtr = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): a pointer to the configuration structure
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to initialize the Port Driver module.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr ){
	uint8 i;
	uint8 Port_Channel;
	uint8 *Port_PORTRegPtr=NULL_PTR;
	uint8 *Port_DDRRegPtr=NULL_PTR;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Port_Status       = PORT_INITIALIZED;
		Port_ArrPtr = ConfigPtr->Channels;

		for(i=0;i<32;i++){
			Port_Channel= Port_mapToRegChannelNum(Port_ArrPtr[i].pin_Num , &Port_PORTRegPtr,&Port_DDRRegPtr );

			if((Port_PORTRegPtr!=NULL_PTR) && (Port_DDRRegPtr!=NULL_PTR)){


				/************************** FOR OUTPUT PINS ************************************************/
				if((Port_ArrPtr[i].PortPinDirection)==PORT_PIN_OUT ){

					SET_BIT(*Port_DDRRegPtr,Port_Channel);

					if((Port_ArrPtr[i].initial_Value)==PIN_HIGH){

						SET_BIT(*Port_PORTRegPtr,Port_Channel);
					}
					else if((Port_ArrPtr[i].initial_Value)==PIN_LOW){

						CLEAR_BIT(*Port_PORTRegPtr,Port_Channel);
					}
					else{

					}
				}
				/************************** FOR INPUT PINS ************************************************/
				else if((Port_ArrPtr[i].PortPinDirection)==PORT_PIN_IN ){

					CLEAR_BIT(*Port_DDRRegPtr,Port_Channel);

					if((Port_ArrPtr[i].pull_Up_Activation)==PULL_UP_ON){

						SET_BIT(*Port_PORTRegPtr,Port_Channel);
					}
					else if((Port_ArrPtr[i].pull_Up_Activation)==PULL_UP_OFF){
						CLEAR_BIT(*Port_PORTRegPtr,Port_Channel);

					}
					else{ /********* DEFAULT_PULL_UP_ACTIVATION *********/
						#if(PORT_CONFIGURED_DEFAULT_ACTIVATION ==STD_ON)
						SET_BIT(*Port_PORTRegPtr,Port_Channel);
						#elif(PORT_CONFIGURED_DEFAULT_ACTIVATION ==STD_OFF)
						CLEAR_BIT(*Port_PORTRegPtr,Port_Channel);
						#endif
					}
				}
				else{}
			}

			else{}
		}
	}
}


/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - the pin ID  / Direction - input or output
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the port pin direction during runtime..
************************************************************************************/

#if (PortSetPinDirectionApi == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){

	uint8 PORT_Channel;
	uint8 *Port_PortRegPtr=NULL_PTR;
	uint8 *Port_DirRegPtr=NULL_PTR;
	boolean error = FALSE;

	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if (PORT_NOT_INITIALIZED == Port_Status)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
					PORT_SET_PIN_DIRECTION_SID  , PORT_E_UNINIT);
			error = TRUE;
		}
		else
		{
			/* No Action Required */
		}
		/* Check if the used channel is within the valid range */
		if (PORT_CONFIGURED_CHANNLES <= Pin)
		{

			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
					PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
			error = TRUE;
		}
		else
		{
			/* No Action Required */
		}
		if ((Port_ArrPtr[Pin].Pin_is_changeable) == STD_OFF)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
					PORT_SET_PIN_DIRECTION_SID  , PORT_E_DIRECTION_UNCHANGEABLE);
			error = TRUE;
		}
		else
		{
			/* No Action Required */
		}
	#endif

		/* In-case there are no errors */
		if(FALSE == error)
		{
			/* Point to the correct PORT register & DDR register according to the pin Id stored in the pin_Num member */
			PORT_Channel= Port_mapToRegChannelNum(Port_ArrPtr[Pin].pin_Num , &Port_PortRegPtr,&Port_DirRegPtr );

			if(Direction == PORT_PIN_OUT)
			{
				/* Write Logic High */
				SET_BIT(*Port_DirRegPtr,PORT_Channel);
			}
			else if(Direction == PORT_PIN_OUT)
			{
				/* Write Logic Low */
				CLEAR_BIT(*Port_DirRegPtr,PORT_Channel);
			}
		}
		else
		{
			/* No Action Required */
		}
}
#endif


/************************************************************************************
* Service Name: PORT_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to exclude those port pins from refreshing that are configured as
  pin direction changeable during runtime and refresh the direction of all configured ports to the configured direction.
************************************************************************************/
void Port_RefreshPortDirection( void ){

	uint8 j;
	uint8 Port_RefChannel;
	uint8 *Port_PORTRefRegPtr=NULL_PTR;
	uint8 *Port_DDRRefRegPtr=NULL_PTR;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID  , PORT_E_UNINIT);

	}
	else
#endif
	{

		for(j=0;j<32;j++){


			if(Port_ArrPtr[j].Pin_is_changeable==STD_ON){

			Port_RefChannel= Port_mapToRegChannelNum(Port_ArrPtr[j].pin_Num , &Port_PORTRefRegPtr,&Port_DDRRefRegPtr );

				if((Port_PORTRefRegPtr!=NULL_PTR) && (Port_DDRRefRegPtr!=NULL_PTR)){

					if((Port_ArrPtr[j].PortPinDirection)==PORT_PIN_OUT ){

						SET_BIT(*Port_DDRRefRegPtr,Port_RefChannel);

					}
					else{ /*then pin is input*/
						CLEAR_BIT(*Port_DDRRefRegPtr,Port_RefChannel);
					}
			  }
				else{ /*No action requied if pointers still Null*/}
			}
			else{

			}

		}
	}
}




/************************************************************************************
* Service Name: PORT_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to get the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void PORT_GetVersionInfo(Std_VersionInfoType *versioninfo){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID,PORT_E_PARAM_POINTER);
	}
	else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif


/************************************************************************************
* Service Name: Port_mapToRegChannelNum
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin number
* Parameters (inout): None
* Parameters (out): a Pointer to point to PORT Reg & a Pointer to point to DDR Reg.
* Return value: ch_Num - have the number of the channel in the port
* Description: static function to map the pin number from the config structure to the related reg and ch number.
************************************************************************************/
STATIC uint8 Port_mapToRegChannelNum (Port_PinType pin , uint8 *Port_Ptr,  uint8 *DDR_Ptr){
	uint8 ch_Num;
	switch(pin)
	{  /**************************  PORTA *******************************/
		case PORT_A_PIN_0:	*Port_Ptr = &PORTA_REG;
							*DDR_Ptr = &DDRA_REG;
							ch_Num=0;
	        break;
		case PORT_A_PIN_1:	*Port_Ptr = &PORTA_REG;
							*DDR_Ptr = &DDRA_REG;
							ch_Num=1;
	        break;
		case PORT_A_PIN_2:	*Port_Ptr = &PORTA_REG;
		                    *DDR_Ptr = &DDRA_REG;
							ch_Num=2;
	        break;
		case PORT_A_PIN_3:	*Port_Ptr = &PORTA_REG;
							*DDR_Ptr = &DDRA_REG;
							ch_Num=3;
	        break;
		case PORT_A_PIN_4:	*Port_Ptr = &PORTA_REG;
							*DDR_Ptr = &DDRA_REG;
							ch_Num=4;
	        break;
		case PORT_A_PIN_5:	*Port_Ptr = &PORTA_REG;
							*DDR_Ptr = &DDRA_REG;
							ch_Num=5;
	        break;
		case PORT_A_PIN_6:	*Port_Ptr = &PORTA_REG;
							*DDR_Ptr = &DDRA_REG;
							ch_Num=6;
	        break;
		case PORT_A_PIN_7:	*Port_Ptr = &PORTA_REG;
							*DDR_Ptr = &DDRA_REG;
							ch_Num=7;
	        break;



	      /***********************  PORTB  **************************/
		case PORT_B_PIN_0:	*Port_Ptr = &PORTB_REG;
							*DDR_Ptr = &DDRB_REG;
							ch_Num=0;
	        break;
		case PORT_B_PIN_1:	*Port_Ptr = &PORTB_REG;
		                    *DDR_Ptr = &DDRB_REG;
							ch_Num=1;
	        break;
		case PORT_B_PIN_2:	*Port_Ptr = &PORTB_REG;
							*DDR_Ptr = &DDRB_REG;
							ch_Num=2;
	        break;
		case PORT_B_PIN_3:	*Port_Ptr = &PORTB_REG;
							*DDR_Ptr = &DDRB_REG;
							ch_Num=3;
	        break;
		case PORT_B_PIN_4:	*Port_Ptr = &PORTB_REG;
        					*DDR_Ptr = &DDRB_REG;
							ch_Num=4;
	        break;
		case PORT_B_PIN_5:	*Port_Ptr = &PORTB_REG;
        					*DDR_Ptr = &DDRB_REG;
							ch_Num=5;
	        break;
		case PORT_B_PIN_6:	*Port_Ptr = &PORTB_REG;
							*DDR_Ptr = &DDRB_REG;
							ch_Num=6;
	        break;
		case PORT_B_PIN_7:	*Port_Ptr = &PORTB_REG;
        					*DDR_Ptr = &DDRB_REG;
							ch_Num=7;
	        break;


	    /************************  PORTC *****************************/
		case PORT_C_PIN_0:	*Port_Ptr = &PORTC_REG;
							*DDR_Ptr = &DDRC_REG;
							ch_Num=0;
	        break;
		case PORT_C_PIN_1:	*Port_Ptr = &PORTC_REG;
							*DDR_Ptr = &DDRC_REG;
							ch_Num=1;
	        break;
		case PORT_C_PIN_2:	*Port_Ptr = &PORTC_REG;
							*DDR_Ptr = &DDRC_REG;
							ch_Num=2;
	        break;
		case PORT_C_PIN_3:	*Port_Ptr = &PORTC_REG;
							*DDR_Ptr = &DDRC_REG;
							ch_Num=3;
	        break;
		case PORT_C_PIN_4:	*Port_Ptr = &PORTC_REG;
							*DDR_Ptr = &DDRC_REG;
							ch_Num=4;
	        break;
		case PORT_C_PIN_5:	*Port_Ptr = &PORTC_REG;
							*DDR_Ptr = &DDRC_REG;
							ch_Num=5;
	        break;
		case PORT_C_PIN_6:	*Port_Ptr = &PORTC_REG;
							*DDR_Ptr = &DDRC_REG;
							ch_Num=6;
	        break;
		case PORT_C_PIN_7:	*Port_Ptr = &PORTC_REG;
							*DDR_Ptr = &DDRC_REG;
							ch_Num=7;
	        break;



	    /*********************   PORTD  ********************************/
		case PORT_D_PIN_0:	*Port_Ptr = &PORTD_REG;
							*DDR_Ptr = &DDRD_REG;
							ch_Num=0;
	        break;
		case PORT_D_PIN_1:	*Port_Ptr = &PORTD_REG;
							*DDR_Ptr = &DDRD_REG;
							ch_Num=1;
	        break;
		case PORT_D_PIN_2:	*Port_Ptr = &PORTD_REG;
							*DDR_Ptr = &DDRD_REG;
							ch_Num=2;
	        break;
		case PORT_D_PIN_3:	*Port_Ptr = &PORTD_REG;
							*DDR_Ptr = &DDRD_REG;
							ch_Num=3;
	        break;
		case PORT_D_PIN_4:	*Port_Ptr = &PORTD_REG;
							*DDR_Ptr = &DDRD_REG;
							ch_Num=4;
	        break;
		case PORT_D_PIN_5:	*Port_Ptr = &PORTD_REG;
							*DDR_Ptr = &DDRD_REG;
							ch_Num=5;
	        break;
		case PORT_D_PIN_6:	*Port_Ptr = &PORTD_REG;
							*DDR_Ptr = &DDRD_REG;
							ch_Num=6;
	        break;
		case PORT_D_PIN_7:	*Port_Ptr = &PORTD_REG;
							*DDR_Ptr = &DDRD_REG;
							ch_Num=7;
	        break;


	}

	return ch_Num;

}
