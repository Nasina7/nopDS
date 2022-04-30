#include <iostream>
#include "ram.hpp"
#include "cpu.hpp"

using namespace std;

ramMap ram;

#define mode8Bit 0
#define mode16Bit 1
#define mode32Bit 2

bool printWarnMessages = false;

void ramMap::writeMem(unsigned int address, unsigned int mode, unsigned int value)
{
    if(cpuIsArm9)
    {
        writeMem9(address, value, mode);
    }
    else
    {
        writeMem7(address, value, mode);
    }
    
}

unsigned int ramMap::readMem(unsigned int address, unsigned int mode)
{
    if(cpuIsArm9)
    {
        return readMem9(address, mode);
    }
    else
    {
        return readMem7(address, mode);
    }
    
}

unsigned int ramMap::arm9IORead(unsigned int address, unsigned int mode)
{
    switch(address)
    {
        case 0x04000000:
            return ENG_A_DISPCNT;
        break;

        case 0x04000004:
            dispStat ^= 0x1;
            return dispStat;
        break;

        case 0x04000130:
            return KEYINPUT;
        break;

        case 0x04000304:
            return POWCNT1;
        break;

        default:
            std::cout<<"WARN: Unhandled ARM9 I/O Read at "<< std::hex << address<<std::endl;
        break;
    }
    return 0;
}

void ramMap::arm9IOWrite(unsigned int address, unsigned int value, unsigned int mode)
{
    switch(address)
    {
        case 0x04000000:
            ENG_A_DISPCNT = value;
        break;

        case 0x04000247:
            WRAMCNT = value;
        break;

        case 0x04000304:
            POWCNT1 = value;
        break;

        default:
            std::cout<<"WARN: Unhandled ARM9 I/O Write at "<< std::hex << address<<std::endl;
        break;
    }
}

unsigned int ramMap::readMem9(unsigned int address, unsigned int mode)
{
    unsigned char* addr8;
    unsigned short* addr16;
    unsigned int* addr32;
    if(address < 0x8000)
    {
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(instTSM + address);
                return (*addr8);
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(instTSM + address);
                return (*addr16);
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(instTSM + address);
                return (*addr32);
            break;
        }
    }
    else if(address >= 0x00800000 && address < 0x00804000)
    {
        address &= 0x0000FFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(dataTCM + address);
                return (*addr8);
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(dataTCM + address);
                return (*addr16);
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(dataTCM + address);
                return (*addr32);
            break;
        }
    }
    else if(address >= 0x02000000 && address < 0x02400000)
    {
        address &= 0x003FFFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(mRAM + address);
                return (*addr8);
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(mRAM + address);
                return (*addr16);
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(mRAM + address);
                return (*addr32);
            break;
        }
    }
    else if(address >= 0x03000000 && address < 0x037FFFFF)
    {
        std::cout<<"WARN: Unhandled ARM9 wRAM Read at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x04000000 && address < 0x04FFFFFF)
    {
        return arm9IORead(address, mode);
    }
    else if(address >= 0x06000000 && address < 0x06800000)
    {
        std::cout<<"WARN: Unhandled ARM9 vRAM Read at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x06800000 && address < 0x068A4000)
    {
        address &= 0x000FFFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(vRAM + address);
                return (*addr8);
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(vRAM + address);
                return (*addr16);
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(vRAM + address);
                return (*addr32);
            break;
        }
        return 0;
    }
    else if(address >= 0x07000000 && address < 0x07002000)
    {
        std::cout<<"WARN: Unhandled ARM9 OAM Read at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x08000000 && address < 0x0A000000)
    {
        std::cout<<"WARN: Unhandled ARM9 GBA ROM Read at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x0A000000 && address < 0x0A010000)
    {
        std::cout<<"WARN: Unhandled ARM9 GBA RAM Read at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0xFFFF0000 && address < 0xFFFF8000)
    {
        address &= 0x0000FFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(arm9bios + address);
                return (*addr8);
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(arm9bios + address);
                return (*addr16);
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(arm9bios + address);
                return (*addr32);
            break;
        }
        return 0;
    }
    else
    {
        if(printWarnMessages)
        {
            std::cout<<"WARN: Unhandled ARM9 UNKNOWN Read at "<< std::hex << address<<std::endl;
        }
    }
}

void ramMap::writeMem9(unsigned int address, unsigned int value, unsigned int mode)
{
    unsigned char* addr8;
    unsigned short* addr16;
    unsigned int* addr32;
    if(address < 0x8000)
    {
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(instTSM + address);
                (*addr8) = value;
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(instTSM + address);
                (*addr16) = value;
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(instTSM + address);
                (*addr32) = value;
            break;
        }
    }
    else if(address >= 0x00800000 && address < 0x00804000)
    {
        address &= 0x0000FFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(dataTCM + address);
                (*addr8) = value;
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(dataTCM + address);
                (*addr16) = value;
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(dataTCM + address);
                (*addr32) = value;
            break;
        }
    }
    else if(address >= 0x02000000 && address < 0x02400000)
    {
        address &= 0x003FFFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(mRAM + address);
                (*addr8) = value;
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(mRAM + address);
                (*addr16) = value;
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(mRAM + address);
                (*addr32) = value;
            break;
        }
        return;
    }
    else if(address >= 0x03000000 && address < 0x037FFFFF)
    {
        std::cout<<"WARN: Unhandled ARM9 wRAM Write at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x04000000 && address < 0x04FFFFFF)
    {
        arm9IOWrite(address, value, mode);
    }
    else if(address >= 0x06000000 && address < 0x06800000)
    {
        std::cout<<"WARN: Unhandled ARM9 vRAM Write at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x06800000 && address < 0x068A4000)
    {
        address &= 0x000FFFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(vRAM + address);
                (*addr8) = value;
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(vRAM + address);
                (*addr16) = value;
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(vRAM + address);
                (*addr32) = value;
            break;
        }
        return;
    }
    else if(address >= 0x07000000 && address < 0x07002000)
    {
        std::cout<<"WARN: Unhandled ARM9 OAM Write at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x08000000 && address < 0x0A000000)
    {
        std::cout<<"WARN: Unhandled ARM9 GBA ROM Write at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x0A000000 && address < 0x0A010000)
    {
        std::cout<<"WARN: Unhandled ARM9 GBA RAM Write at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0xFFFF0000 && address < 0xFFFF8000)
    {
        std::cout<<"WARN: Unhandled ARM9 BIOS Write at "<< std::hex << address<<std::endl;
    }
    else
    {
        if(printWarnMessages)
        {
            std::cout<<"WARN: Unhandled ARM9 UNKNOWN Write at "<< std::hex << address<<std::endl;
        }
    }
    return;
}

unsigned int ramMap::readMem7(unsigned int address, unsigned int mode)
{
    unsigned char* addr8;
    unsigned short* addr16;
    unsigned int* addr32;
    if(address < 0x4000)
    {
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(arm7bios + address);
                return (*addr8);
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(arm7bios + address);
                return (*addr16);
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(arm7bios + address);
                return (*addr32);
            break;
        }
    }
    else if(address >= 0x02000000 && address < 0x02400000)
    {
        address &= 0x003FFFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(mRAM + address);
                return (*addr8);
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(mRAM + address);
                return (*addr16);
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(mRAM + address);
                return (*addr32);
            break;
        }
    }
    else if(address >= 0x03000000 && address < 0x037FFFFF)
    {
        uint32_t newAddress = address % wRamModeLookup7[WRAMCNT & 0x3];
        if((WRAMCNT & 0x3) == 0)
        {
            switch(mode)
            {
                case mode8Bit:
                    addr8 = (unsigned char*)(wRAM + 0x8000 + newAddress);
                    return (*addr8);
                break;

                case mode16Bit:
                    addr16 = (unsigned short*)(wRAM + 0x8000 + newAddress);
                    return (*addr16);
                break;

                case mode32Bit:
                    addr32 = (unsigned int*)(wRAM + 0x8000 + newAddress);
                    return (*addr32);
                break;
            }
        }
        else if((WRAMCNT & 0x3) == 1 || (WRAMCNT & 0x3) == 3)
        {
            switch(mode)
            {
                case mode8Bit:
                    addr8 = (unsigned char*)(wRAM + 0 + newAddress);
                    return (*addr8);
                break;

                case mode16Bit:
                    addr16 = (unsigned short*)(wRAM + 0 + newAddress);
                    return (*addr16);
                break;

                case mode32Bit:
                    addr32 = (unsigned int*)(wRAM + 0 + newAddress);
                    return (*addr32);
                break;
            }
        }
        else if((WRAMCNT & 0x3) == 2)
        {
            switch(mode)
            {
                case mode8Bit:
                    addr8 = (unsigned char*)(wRAM + 0x4000 + newAddress);
                    return (*addr8);
                break;

                case mode16Bit:
                    addr16 = (unsigned short*)(wRAM + 0x4000 + newAddress);
                    return (*addr16);
                break;

                case mode32Bit:
                    addr32 = (unsigned int*)(wRAM + 0x4000 + newAddress);
                    return (*addr32);
                break;
            }
        }
    }
    else if(address >= 0x03800000 && address < 0x03810000)
    {
        address &= 0x0000FFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(wRAM + 0x8000 + address);
                return (*addr8);
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(wRAM + 0x8000 + address);
                return (*addr16);
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(wRAM + 0x8000 + address);
                return (*addr32);
            break;
        }
    }
    else if(address >= 0x04000000 && address < 0x04FFFFFF)
    {
        if(printWarnMessages)
        {
            std::cout<<"WARN: Unhandled ARM7 I/O Read at "<< std::hex << address<<std::endl;
        }
    }
    else if(address >= 0x06000000 && address < 0x06400000)
    {
        std::cout<<"WARN: Unhandled ARM7 vRAM Read at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x08000000 && address < 0x0A000000)
    {
        std::cout<<"WARN: Unhandled ARM7 GBA ROM Read at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x0A000000 && address < 0x0A010000)
    {
        std::cout<<"WARN: Unhandled ARM7 GBA RAM Read at "<< std::hex << address<<std::endl;
    }
    else
    {
        if(printWarnMessages)
        {
            std::cout<<"WARN: Unhandled ARM7 UNKNOWN Read at "<< std::hex << address<<std::endl;
        }
    }
    return 0;
}

void ramMap::writeMem7(unsigned int address, unsigned int value, unsigned int mode)
{
    unsigned char* addr8;
    unsigned short* addr16;
    unsigned int* addr32;
    if(address < 0x4000)
    {
        std::cout<<"WARN: Unhandled ARM7 BIOS Write at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x02000000 && address < 0x02400000)
    {
        address &= 0x003FFFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(mRAM + address);
                (*addr8) = value;
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(mRAM + address);
                (*addr16) = value;
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(mRAM + address);
                (*addr32) = value;
            break;
        }
        return;
    }
    else if(address >= 0x03000000 && address < 0x037FFFFF)
    {
        uint32_t newAddress = address % wRamModeLookup7[WRAMCNT & 0x3];
        if((WRAMCNT & 0x3) == 0)
        {
            switch(mode)
            {
                case mode8Bit:
                    addr8 = (unsigned char*)(wRAM + 0x8000 + newAddress);
                    (*addr8) = value;
                break;

                case mode16Bit:
                    addr16 = (unsigned short*)(wRAM + 0x8000 + newAddress);
                    (*addr16) = value;
                break;

                case mode32Bit:
                    addr32 = (unsigned int*)(wRAM + 0x8000 + newAddress);
                    (*addr32) = value;
                break;
            }
        }
        else if((WRAMCNT & 0x3) == 1 || (WRAMCNT & 0x3) == 3)
        {
            switch(mode)
            {
                case mode8Bit:
                    addr8 = (unsigned char*)(wRAM + 0 + newAddress);
                    (*addr8) = value;
                break;

                case mode16Bit:
                    addr16 = (unsigned short*)(wRAM + 0 + newAddress);
                    (*addr16) = value;
                break;

                case mode32Bit:
                    addr32 = (unsigned int*)(wRAM + 0 + newAddress);
                    (*addr32) = value;
                break;
            }
        }
        else if((WRAMCNT & 0x3) == 2)
        {
            switch(mode)
            {
                case mode8Bit:
                    addr8 = (unsigned char*)(wRAM + 0x4000 + newAddress);
                    (*addr8) = value;
                break;

                case mode16Bit:
                    addr16 = (unsigned short*)(wRAM + 0x4000 + newAddress);
                    (*addr16) = value;
                break;

                case mode32Bit:
                    addr32 = (unsigned int*)(wRAM + 0x4000 + newAddress);
                    (*addr32) = value;
                break;
            }
        }
    }
    else if(address >= 0x03800000 && address < 0x03810000)
    {
        address &= 0x0000FFFF;
        switch(mode)
        {
            case mode8Bit:
                addr8 = (unsigned char*)(wRAM + 0x8000 + address);
                (*addr8) = value;
            break;

            case mode16Bit:
                addr16 = (unsigned short*)(wRAM + 0x8000 + address);
                (*addr16) = value;
            break;

            case mode32Bit:
                addr32 = (unsigned int*)(wRAM + 0x8000 + address);
                (*addr32) = value;
            break;
        }
        return;
    }
    else if(address >= 0x04000000 && address < 0x04FFFFFF)
    {
        if(printWarnMessages)
        {
            std::cout<<"WARN: Unhandled ARM7 I/O Write at "<< std::hex << address<<std::endl;
        }
    }
    else if(address >= 0x06000000 && address < 0x06400000)
    {
        std::cout<<"WARN: Unhandled ARM7 vRAM Write at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x08000000 && address < 0x0A000000)
    {
        std::cout<<"WARN: Unhandled ARM7 GBA ROM Write at "<< std::hex << address<<std::endl;
    }
    else if(address >= 0x0A000000 && address < 0x0A010000)
    {
        std::cout<<"WARN: Unhandled ARM7 GBA RAM Write at "<< std::hex << address<<std::endl;
    }
    else
    {
        std::cout<<"WARN: Unhandled ARM7 UNKNOWN Write at "<< std::hex << address<<std::endl;
    }
    return;
}