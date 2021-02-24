/*
 * Port.h
 *
 *  Created on: Dec 23, 2019
 *      Author: Aya Hussein
 */

#ifndef PORT_H_
#define PORT_H_


/* Id for the company in the AUTOSAR*/

#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for PORT Init  */
#define PORT_INIT_SID                   (uint8)0x00

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIRECTION_SID      (uint8)0x01

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIRECTION_SID (uint8)0x02

/* Service ID for Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID           (uint8)0x04

/* Service ID for PORT GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID       (uint8)0x03

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                  (uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE     (uint8)0x0B

/* API Service called with wrong parameter. */
#define PORT_E_PARAM_CONFIG               (uint8)0x0C

/* API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_PARAM_INVALID_MODE         (uint8)0x0D

/*API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE          (uint8)0x0E

/*API service called without module initialization */
#define PORT_E_UNINIT                     (uint8)0x0F

/*APIs called with a Null Pointer
 */
#define PORT_E_PARAM_POINTER              (uint8)0x10
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef uint8 Port_PinType;
typedef uint8 Port_PinModeType;

/********** ENUM for defining the direction of the pin**************************/
typedef enum{
	PORT_PIN_IN,
	PORT_PIN_OUT
}Port_PinDirectionType;

typedef enum{
	PIN_HIGH=STD_HIGH,
	PIN_LOW=STD_LOW,
	NoInitial,/************************ pin is input ***************************/
}initial_ValueType;


typedef enum{
	PULL_UP_ON=STD_ON,
	PULL_UP_OFF=STD_OFF,
	NoActivation,  /********************* pin is output*************************/
	DefaultActivation= PORT_CONFIGURED_DEFAULT_ACTIVATION
}pull_Up_ActivationType;


/* Data Structure required for initializing the Port Driver */
typedef struct
{
	/* Member contains the ID of the pin*/
	Port_PinType pin_Num;
	/*Member contains the direction of the channel*/
	Port_PinDirectionType PortPinDirection;

	initial_ValueType initial_Value;

	pull_Up_ActivationType pull_Up_Activation;

	boolean Pin_is_changeable;

}Port_ConfigChannel;

typedef struct
{
	Port_ConfigChannel Channels[32];

} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );

#if (PortSetPinDirectionApi == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

void Port_RefreshPortDirection( void );

#if (PORT_VERSION_INFO_API == STD_ON)
void PORT_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;
#endif /* PORT_H_ */
