/*
 * L3G4200D_Cfg.h
 *
 * Created: 24/09/2015 09:13:50 م
 *  Author: hossam
 */ 


#ifndef L3G4200D_CFG_H_
#define L3G4200D_CFG_H_
#include "Basic_Types.h"
#include "DIO.h"
#include "SPI.h"
#include "delay.h"
#include "L3G4200D.h"
void u8START_TIME_OUT_MS(u32 DELAY_MS, u32* FLAG_PTR) ;
void GYHD_INIT_SLAVE_SELECT(void);
/*SPI Communication Configuration*/

#define GYHD_ACTIVATE_SLAVE_SELECT (DIO_WritePort((u8)PB,(u8)0b11101111,(u8)0x10))
#define GYHD_DEACTIVATE_SLAVE_SELECT (DIO_WritePort(PB,(1u<<4u),(1u<<4u)))

/*Timeout Management Configuration*/
#define u8USE_DELAY (0x00u)
#define u8USE_TIMER (0x01u)

#define u8TIMEOUT_FUNCTION (u8USE_DELAY)

/*Self Axis Movement Detection Config*/
#define ON (1u)
#define u8SELF_AXIS_MOV  (ON)


#endif /* L3G4200D_CFG_H_ */
