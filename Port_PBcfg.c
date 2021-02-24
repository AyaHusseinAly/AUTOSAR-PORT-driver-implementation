/*
 * Port_PBcfg.c
 *
 *  Created on: Dec 25, 2019
 *      Author: Aya Hussein
 */

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with PORT_Init API */
const Port_ConfigType Port_Configuration =
                                   {

                /*1*/    		    PortConf_LED1_PIN_NUM,
									PORT_PIN_OUT,
									PIN_HIGH,
									NoActivation,
									STD_ON,

				/*2*/				PortConf_BUTTON1_PIN_NUM,
									PORT_PIN_IN,
									NoInitial,
									PULL_UP_OFF,
									STD_ON,

									/*********Rest of the pins not defined so IT"S INPUT by default, then NoInitial value
									 *and default Activation for pull-up res is applied***********/
									/*******PORTA*******/


				/*3*/				PORT_A_PIN_1,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation, /* apply pull_up default configured state*/
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*4*/				PORT_A_PIN_2,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*5*/				PORT_A_PIN_3,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*6*/				PORT_A_PIN_4,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*7*/				PORT_A_PIN_5,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*8*/				PORT_A_PIN_6,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*9*/				PORT_A_PIN_7,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,


									/*****************************************PORTB************************************************/

				/*10*/				PORT_B_PIN_0,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*11*/				PORT_B_PIN_1,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*12*/				PORT_B_PIN_2,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*13*/				PORT_B_PIN_3,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*14*/				PORT_B_PIN_4,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*15*/				PORT_B_PIN_5,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*16*/				PORT_B_PIN_6,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*17*/				PORT_B_PIN_7,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,


									/**************************************PORTC************************************/

				/*18*/				PORT_C_PIN_0,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*19*/				PORT_C_PIN_1,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*20*/				PORT_C_PIN_2,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*21*/				PORT_C_PIN_3,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*22*/				PORT_C_PIN_4,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*23*/				PORT_C_PIN_5,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*24*/				PORT_C_PIN_6,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*25*/				PORT_C_PIN_7,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,


									/******************************* PORTD ************************************/

				/*26*/				PORT_D_PIN_0,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*27*/				PORT_D_PIN_1,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

									/*PIN 2 IS CONNECTED TO THE BUTTON*/

				/*28*/				PORT_D_PIN_3,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*29*/		    	PORT_D_PIN_4,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*30*/				PORT_D_PIN_5,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*31*/  			PORT_D_PIN_6,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE,

				/*32*/				PORT_D_PIN_7,
									PORT_PIN_IN,
									NoInitial,
									DefaultActivation,
									PORT_DEFAULT_PIN_DIRECTION_CHANGEABLE

								   };

