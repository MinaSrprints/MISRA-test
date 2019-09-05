#include "Basic_Types.h"
#include "CRC.h"
u32 randi(void);
/***************************************************************************************/
static u32 GetPower(u32 Base,u32 Pow);
static u16 gen_crc16(const u8 *data, u16 size, u32 CRC16);
/***************************************************************************************/
void SECR_CrcPolynomialGenerate(u32* PolynomialPtr,u8 CrcLengthInBits)
{
    u32 DevisorValue;
    DevisorValue = (u32)(GetPower((u32)2,(u32)CrcLengthInBits)) - (u32)1;
    *PolynomialPtr = (randi() % DevisorValue) +(u32)0x10000 ;
}
/***************************************************************************************/
void SECR_GnerateCrc(const u8* PayloadPtr,u8 PayloadLength, u16* CrcPtr, u32 CrcPoly)
{
    u16 LoopIndex;
    static u8 InternalBuffer[8];
    u8* pot=InternalBuffer;
    /*Copying data to internal buffer*/
    for (LoopIndex = 0u; LoopIndex < PayloadLength; LoopIndex ++)
    {
        pot+=LoopIndex;
        PayloadPtr += LoopIndex;
        *(pot) = *(PayloadPtr);
    }
    /*perform bit wise invert on the data*/
    for (LoopIndex = 0u; LoopIndex < PayloadLength; LoopIndex ++)
    {
        InternalBuffer[LoopIndex]  ^= 0xffu;
    }
    /*Generate CRC*/
    *CrcPtr = gen_crc16(InternalBuffer,(u16)PayloadLength*8u,(u32)0x18005);
}
/***************************************************************************************/
static u32 GetPower(u32 Base,u32 Pow)
{
    u32 result = 1u;
    u32 LoopIndex_1;
    for (LoopIndex_1 = 0u; LoopIndex_1 < Pow; LoopIndex_1 ++)
    {
        result *= Base;
    }
    return result;
}
/***************************************************************************************/
static u16 gen_crc16(const u8 *data, u16 size, u32 CRC16)
{
    u16 out = 0u;
    u16 bits_read = 0u;
    u16   bit_flag;
    u16 i;
    u16 abs1=1;
    u16 temp;
    u16 crc = 0u;
    u16 j = 0x0001u;
    /* Sanity check: */
    if(data == 0u)
    {
        crc= 0u;
    }

    while(size > 0u)
    {
        bit_flag = out >> 15;

        /* Get next bit: */
        out <<= 1u;
        temp= *data >> bits_read;
        temp= temp |out;
        if((temp & abs1) !=0u)
        {
            out=0x0001u;
        }
        else
        {
            out=0x0000u;
        }


        /* Increment bit counter: */
        bits_read++;
        if(bits_read > 7u)
        {
            bits_read = 0u;
            size--;
        }

        /* Cycle check: */
        if(bit_flag)
        {
                    out ^= CRC16;
        }


    }

    /* item b) "push out" the last 16 bits*/

    for (i = 0u; i < 16u; ++i) {
        bit_flag = out >> 15u;
        out <<= 1u;
        if(bit_flag)
        {
            if(((out ^ (u16)CRC16)!=0u))
            {
                (out ^= (u16)CRC16);
            }
        }
    }

    /* item c) reverse the bits*/



    for (i = 0x8000u; i != 0u; i >>=1u)
    {
        j <<= 1u;
        if (i & out)
        {
            crc |= j;
        }
    }

    return crc;
}
/***************************************************************************************/
