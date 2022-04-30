#include <iostream>
#include "rom.hpp"
#include "cpu.hpp"
#include "ram.hpp"
#include "input.hpp"
#include "display.hpp"
#include <chrono>
#include "emu.hpp"



using namespace std;

void emuInit()
{
    arm9.opcodesRan = 0;
    arm7.opcodesRan = 0;
    for(int i = 0; i < 13; i++)
    {
        arm9.R[i] = 0;
    }
    arm9.R[0] = 0xCA5;
    arm9.R[13] = 0x03002F7C;
    //cpu.R[14] = 0x08000000;
    arm9.R1314_svc[0] = 0x03002F7C;
    //cpu.R1314_svc[1] = 0x08000000;
    arm9.R1314_irq[0] = 0x03002F7C;
    //cpu.R1314_irq[1] = 0x08000000;
    arm9.cpsr.mode = 0x1F;
    arm9.spsr.mode = 0x10;
    arm9.cpsr.T = false;
    arm9.cpsr.N = false;
    arm9.cpsr.C = false;
    arm9.cpsr.F = false;
    arm9.cpsr.I = false;
    arm9.cpsr.Q = false;
    arm9.cpsr.V = false;
    arm9.cpsr.Z = false;

    for(int i = 0; i < 13; i++)
    {
        arm7.R[i] = 0;
    }
    arm7.R[0] = 0xCA5;
    arm7.R[13] = 0x03002F7C;
    //cpu.R[14] = 0x08000000;
    arm7.R1314_svc[0] = 0x03002F7C;
    //cpu.R1314_svc[1] = 0x08000000;
    arm7.R1314_irq[0] = 0x03002F7C;
    //cpu.R1314_irq[1] = 0x08000000;
    arm7.cpsr.mode = 0x1F;
    arm7.spsr.mode = 0x10;
    arm7.cpsr.T = false;
    arm7.cpsr.N = false;
    arm7.cpsr.C = false;
    arm7.cpsr.F = false;
    arm7.cpsr.I = false;
    arm7.cpsr.Q = false;
    arm7.cpsr.V = false;
    arm7.cpsr.Z = false;
    ram.WRAMCNT = 3;
    ram.KEYINPUT = 0xFFFF;
}

int main()
{
    

    romFile rom;

    cout<<"Enter Rom Name: ";
    string romName;
    cin>>romName;
    string romFileName = "roms/" + romName;

    if(!rom.loadROM(romFileName))
    {
        cout<<"Couldn't Load File"<<endl;
        return 1;
    }
    arm9.generateThumbLookup();
    arm7.generateThumbLookup();

    cout<<"Type anything to begin."<<endl;
    cin>>romName;

    display.initDisplay();

    emuInit();

    int64_t opcodeAmount = 0;

    auto start = std::chrono::system_clock::now();

    while(1)
    {
        ram.cpuIsArm9 = true;
        arm9.doOpcode();
        arm9.doOpcode();
        ram.cpuIsArm9 = false;
        arm7.doOpcode();
        ram.cpuIsArm9 = true;
        
        //std::string test;
        //cin>>test;
        opcodeAmount++;
        if(opcodeAmount % opPerFrame == 0)
        {
            display.mainDisplayFunc();
            int pollRetVal = input.handleInput();
            if(pollRetVal == 1)
            {
                return 0;
            }
        }
        if(opcodeAmount % (opPerFrame * 60) == 0)
        {
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            uint32_t framerate = 60 / elapsed_seconds.count();
            std::string newTitle;
            newTitle = "nopDS :> - FPS: ";
            newTitle.append(to_string(framerate));
            display.setWindowTitle(newTitle);
            start = std::chrono::system_clock::now();
        }
    }

}