#include <fstream>
#include <limits>
#include "rom.hpp"
#include <iostream>
#include <string.h>
#include "ram.hpp"
#include "cpu.hpp"

bool romFile::loadROM(std::string filename)
{
    std::ifstream rom(filename, std::fstream::binary);

    if(!rom.is_open())
    {
        return false;
    }

    rom.ignore(std::numeric_limits<std::streamsize>::max());
    std::streamsize length = rom.gcount();
    rom.clear();
    rom.seekg(0, std::ios_base::beg);

    romPointer = new uint8_t[length];

    rom.read((char*)romPointer, length);

    rom.close();

    char romName[0xC];
    memcpy(romName, romPointer, 0xC);
    std::cout<<romName<<std::endl;

    unsigned int* arm9bin;
    unsigned int* arm9exec;
    unsigned int* arm9ram;
    unsigned int* arm9len;

    arm9bin = (unsigned int*)(romPointer + 0x20);
    arm9exec = (unsigned int*)(romPointer + 0x24);
    arm9ram = (unsigned int*)(romPointer + 0x28);
    arm9len = (unsigned int*)(romPointer + 0x2C);
    std::cout<<std::hex<<(*arm9exec)<<std::endl;

    unsigned int ramLocation, romLocation;
    romLocation = (*arm9bin);
    ramLocation = (*arm9ram);
    for(unsigned int i = 0; i < (*arm9len); i++)
    {
        ram.writeMem9(ramLocation, romPointer[romLocation], 0);
        if(i < 4)
        {
            //std::cout<<std::hex<<(unsigned int)romPointer[romLocation]<<std::endl;
        }
        ramLocation++;
        romLocation++;
    }

    arm9.R[15] = (*arm9exec);
    arm9.R[14] = arm9.R[15];
    arm9.R1314_irq[1] = arm9.R[15];
    arm9.R1314_svc[1] = arm9.R[15];


    //LOAD ARM 7 BINARY

    arm9bin = (unsigned int*)(romPointer + 0x30);
    arm9exec = (unsigned int*)(romPointer + 0x34);
    arm9ram = (unsigned int*)(romPointer + 0x38);
    arm9len = (unsigned int*)(romPointer + 0x3C);
    std::cout<<std::hex<<(*arm9exec)<<std::endl;
    //std::cout<<std::hex<<(*arm9bin)<<std::endl;
    //std::cout<<std::hex<<(*arm9ram)<<std::endl;

    romLocation = (*arm9bin);
    ramLocation = (*arm9ram);
    for(unsigned int i = 0; i < (*arm9len); i++)
    {
        ram.writeMem7(ramLocation, romPointer[romLocation], 0);
        if(i < 4)
        {
            std::cout<<std::hex<<(unsigned int)romPointer[romLocation]<<std::endl;
        }
        ramLocation++;
        romLocation++;
    }

    arm7.R[15] = (*arm9exec);
    arm7.R[14] = arm7.R[15];
    arm7.R1314_irq[1] = arm7.R[15];
    arm7.R1314_svc[1] = arm7.R[15];



    // ARM7 BIOS LOAD
    std::ifstream bios7("bios/biosnds7.bin", std::fstream::binary);
    if(!bios7.is_open())
    {
        return false;
    }
    bios7.ignore(std::numeric_limits<std::streamsize>::max());
    length = bios7.gcount();
    bios7.clear();
    bios7.seekg(0, std::ios_base::beg);
    bios7.read((char*)ram.arm7bios, 0x4000);
    bios7.close();

    std::ifstream bios9("bios/biosnds9.bin", std::fstream::binary);
    if(!bios9.is_open())
    {
        return false;
    }
    bios9.ignore(std::numeric_limits<std::streamsize>::max());
    length = bios9.gcount();
    bios9.clear();
    bios9.seekg(0, std::ios_base::beg);
    bios9.read((char*)ram.arm9bios, 0x8000);
    bios9.close();

    return true;
}