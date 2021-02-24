/*
 * Port_Cfg.h
 *
 *  Created on: Dec 23, 2019
 *      Author: Aya Hussein
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for setPinDirection API */
#define PortSetPinDirectionApi               (STD_ON)

/* Symbolic names for port pins*/
#define PORT_A_PIN_0   (Port_PinType)40
#define PORT_A_PIN_1   (Port_PinType)39
#define PORT_A_PIN_2   (Port_PinType)38
#define PORT_A_PIN_3   (Port_PinType)37
#define PORT_A_PIN_4   (Port_PinType)36
#define PORT_A_PIN_5   (Port_PinType)35
#define PORT_A_PIN_6   (Port_PinType)34
#define PORT_A_PIN_7   (Port_PinType)33

#define PORT_B_PIN_0   (Port_PinType)1
#define PORT_B_PIN_1   (Port_PinType)2
#define PORT_B_PIN_2   (Port_PinType)3
#define PORT_B_PIN_3   (Port_PinType)4
#define PORT_B_PIN_4   (Port_PinType)5
#define PORT_B_PIN_5   (Port_PinType)6
#define PORT_B_PIN_6   (Port_PinType)7
#define PORT_B_PIN_7   (Port_PinType)8

#define PORT_C_PIN_0   (Port_PinType)22
#define PORT_C_PIN_1   (Port_PinType)23
#define PORT_C_PIN_2   (Port_PinType)24
#define PORT_C_PIN_3   (Port_PinType)25
#define PORT_C_PIN_4   (Port_PinType)26
#define PORT_C_PIN_5   (Port_PinType)27
#define PORT_C_PIN_6   (Port_PinType)28
#define PORT_C_PIN_7   (Port_PinType)29

#define PORT_D_PIN_0   (Port_PinType)14
#define PORT_D_PIN_1   (Port_PinType)15
#define PORT_D_PIN_2   (Port_PinType)16
#define PORT_D_PIN_3   (Port_PinType)17
#define PORT_D_PIN_4   (Port_PinType)18
#define PORT_D_PIN_5   (Port_PinType)19
#define PORT_D_PIN_6   (Port_PinType)20
#define PORT_D_PIN_7   (Port_PinType)21



/* Number of the configured Port Channels */
#define PORT_CONFIGURED_CHANNLES                 (2U)

#define PORT_CONFIGURED_DEFAULT_ACTIVATION       STD_OFF  /*** Pull-up res is off by default for not configured pins ****/

#define PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE    STD_ON

/* Channel Index in the array of structures in Port_PBcfg.c */
#define PortConf_LED1_CHANNEL_ID_INDEX        (uint8)0x00
#define PortConf_BUTTON1_CHANNEL_ID_INDEX     (uint8)0x01

/* PORT Configured Pin ID's  */
#define PortConf_LED1_PIN_NUM                PORT_A_PIN_0
#define PortConf_BUTTON1_PIN_NUM             PORT_D_PIN_2

#endif /* PORT_CFG_H_ */
