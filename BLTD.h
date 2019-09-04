/*
 * BLTD.h
 *
 * Created: 31/07/2015 12:35:08 ص
 *  Author: hossam
 */ 


#ifndef BLTD_H_
#define BLTD_H_
#include "Basic_Types.h"
#define BLTD_RESP_STATUS_OK ((unsigned char)0x00)
#define BLTD_RESP_STATUS_NOK ((unsigned char)0x01)
#define BLTD_RESP_STATUS_NON ((unsigned char)0x02)
typedef void (*CbkPfnType)(void);
extern void BLTD_SendInitCmd(void);
extern u8 BLTD_CheckForResponse(const u8* Response,u16 RespLength);
extern void BLTD_SendInquireCmd(void);
extern void BLTD_SendMessage(const char* Message,u16 MsgLength);
extern void BLTD_StartWaitPairing(void);
extern void BLTD_StartReceivingData(char* DataBuffer,u16 BufferLength,CbkPfnType CbkFnPtr);
extern u8 BLTD_CheckForData( char* Data);
extern void BLTD_SenTestCmd(void);
extern u8 BLTD_GetRecievedData(char*Data, u16 Length);




#endif /* BLTD_H_ */
