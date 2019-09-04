/*
 * BLTD.c
 *
 * Created: 31/07/2015 12:35:22 ص
 *  Author: hossam
 */ 
#include "Basic_Types.h"
#include "UART_Drv.h"
#include "BLTD.h"


static u8 IsRespRecieved = 0;
static char RxBuffer[100];
static void BTCommandSend(const char* Command,u16 CommandLength);
static  void MemCpy(char *Des,const char *Src,u16 Length);
static void RxcCallBackFun(void);
static u8 MemCmp(const u8 * Src1,const u8 *Src2,u16 CmpLength);
/***************************************************************************************************************/
void BLTD_SendInitCmd(void)
{
    IsRespRecieved = 0u;
    UART_StartReception(RxBuffer,4u,&RxcCallBackFun);
    BTCommandSend((u8*)"+INIT",5u);
}
/***************************************************************************************************************/
void BLTD_SendInquireCmd(void)
{
    IsRespRecieved = 0u;
    UART_StartReception(RxBuffer,4u,&RxcCallBackFun);
    BTCommandSend((u8*)"+INQ",4u);
}
u8 BLTD_CheckForResponse(const u8* Response,u16 RespLength)
{
    u8 RespStatus=0;
    u8 IsEqual=0;
    if(IsRespRecieved == 1u)
    {
        IsRespRecieved = 0u;
        IsEqual = MemCmp(Response,RxBuffer,RespLength);
        if(IsEqual == 0u)
        {
            RespStatus = BLTD_RESP_STATUS_OK;

        }
        else
        {
            RespStatus = BLTD_RESP_STATUS_NOK;
        }

    }
    else
    {

        RespStatus = BLTD_RESP_STATUS_NON;
    }
    return RespStatus;
}	
/***************************************************************************************************************/
void BLTD_StartWaitPairing(void)
{
    UART_StopRception();
    UART_StartReception(RxBuffer,4u,&RxcCallBackFun);
    /*BTCommandSend(0,0);*/

}
/***************************************************************************************************************/	
void BLTD_SendMessage(const char* Message,u16 MsgLength)
{
    UART_TxBuffer(Message,MsgLength);
}	
/***************************************************************************************************************/
u8 BLTD_GetRecievedData(char*Data, u16 Length)
{
    u8 RespStatus_1;
    u8 i;
    char *count=Data;
    char *count2=RxBuffer;
    if(IsRespRecieved == 1u)
    {
        IsRespRecieved = 0u;
        RespStatus_1 = BLTD_RESP_STATUS_OK;
        for( i = 0u; i< Length ; i++)
        {
            count+=i;
            count2+=i;
            *(count) = *(count2);
        }
    }
    else
    {
        RespStatus_1 = BLTD_RESP_STATUS_NON;
    }

    return RespStatus_1;
}
/***************************************************************************************************************/
void BLTD_StartReceivingData(char* DataBuffer,u16 BufferLength,CbkPfnType CbkFnPtr)
{
    UART_StartReception(DataBuffer,BufferLength,CbkFnPtr);

}
/***************************************************************************************************************/
u8 BLTD_CheckForData( char* Data)
{
    u16 RxBytesNum;
    u8 IsReceived;
    RxBytesNum = UART_GetNumOfRxbytes();
    if(RxBytesNum > 0u)
    {
        IsReceived = 0x01u;
        RxBytesNum+=1u;
        *Data = RxBuffer[RxBytesNum];
        UART_StopRception();
        UART_StartReception(RxBuffer,100u,&RxcCallBackFun);
    }
    else
    {
        IsReceived = 0x00u;
        *Data  = (char)0;
    }
    return IsReceived;
}

/***************************************************************************************************************/	
void BLTD_SenTestCmd(void)
{
    UART_StartReception(RxBuffer,4u,&RxcCallBackFun);
    BTCommandSend((char*)0,(u16)0);

}
/***************************************************************************************************************/
static void BTCommandSend(const char* Command,u16 CommandLength)
{
    static char BTCommandBuffer[100];
    BTCommandBuffer[0] = (char)'A';
    BTCommandBuffer[1] = (char)'T';
    MemCpy(&BTCommandBuffer[2],Command,CommandLength);
    CommandLength+=2u;
    BTCommandBuffer[CommandLength] = (char)0x0d;
    CommandLength+=3u;
    BTCommandBuffer[CommandLength] = (char)0x0a;
    UART_TxBuffer(BTCommandBuffer,CommandLength + 4u);

}
/***************************************************************************************************************/
static  void MemCpy(char *Des,const char *Src,u16 Length)
{
    u16 i_2;
    for(i_2 = 0u ; i_2<Length ; i_2++)
    {
        Des+=i_2;
        Src+=i_2;
        *(Des) = *(Src);
    }
}
/***************************************************************************************************************/	
static void RxcCallBackFun(void)
{

    IsRespRecieved = 1u;
}
/***************************************************************************************************************/
static u8 MemCmp(const u8 * Src1,const u8 *Src2,u16 CmpLength)
{
    u8 RetVal = 0u;
    u16 i_;
    const u8* con=Src1;
    const u8*con2=Src2;
    for(i_ = 0u ;(i_ < CmpLength); i_++)
    {
        con+=i_;
        con2+=i_;
        if(*(con) != *(con2))
        {
            RetVal = 1u;
            break;
        }
    }
    return RetVal;
}
/***************************************************************************************************************/
