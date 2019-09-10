/*
 * KEYPAD.h
 *
 * Created: 30/01/2016 07:01:25 م
 *  Author: hossam
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


#define KPD_COL_PORT (PD)
#define KPD_ROW_PORT (PD)
#define KPD_COL_MASK ((unsigned char)0x70)
#define KPD_ROW_MASK ((unsigned char)0x0f)
#define KPD_COL_PIN_NUM (4u)
#define KPD_ROW_PIN_NUM (0u)
#define APS_ZERO ((unsigned char)0x00)
#define APS_ONE ((unsigned char)0xFF)
/**************************************************/


void KPD_Init(void);


void KPD_Init(void);
void KPD_ReadVal(char* ValuePtr);
void KPD_COL_READ(unsigned char* VALPTR);
void KPD_ROW_WRITE(unsigned char DATA);
void KPD_COL_INIT(void);
void KPD_ROW_INIT(void);

#endif /* KEYPAD_H_ */
