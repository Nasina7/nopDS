#include "cpu.hpp"
#include "ram.hpp"
#include <iostream>


armCPU arm9;
armCPU arm7;




uint32_t armCPU::readCPSR(cpsrS value)
{
    return
            value.N << 31 |
            value.Z << 30 |
            value.C << 29 |
            value.V << 28 |
            value.Q << 27 |
            value.I << 7 |
            value.F << 6 |
            value.T << 5 |
            (value.mode & 0x1F);
}

cpsrS armCPU::writeCPSR(cpsrS value, uint32_t value2, bool doModeSwitch)
{
    value.N = ((value2 >> 31) & 0x1);
    value.Z = ((value2 >> 30) & 0x1);
    value.C = ((value2 >> 29) & 0x1);
    value.V = ((value2 >> 28) & 0x1);
    value.Q = ((value2 >> 27) & 0x1);
    value.I = ((value2 >> 7) & 0x1);
    value.F = ((value2 >> 6) & 0x1);
    value.T = ((value2 >> 5) & 0x1);
    if(doModeSwitch == true)
    {
        //std::cout<<std::hex<<value2<<std::endl;
        modeSwitch((value2 & 0x1F));
    }
    value.mode = (value2 & 0x1F);
    return value;
}


uint8_t armCPU::modeSwitch(uint8_t switchMode)
{
    //printf("Mode Switch 0x%X\n",switchMode);
    if(cpsr.mode == switchMode)
    {
        return 0;
    }
    if(cpsr.mode == 0x1F && switchMode == 0x10) // Swap from System to User
    {
        return 0;
    }
    if(cpsr.mode == 0x10 && switchMode == 0x1F) // Swap from User to System
    {
        return 0;
    }
    uint32_t swapVal;
    cpsrS swapCPSR;
    switch(switchMode)
    {
        case 0x10:
            switch(cpsr.mode)
            {
                case 0x12: // IRQ
                    swapVal = R[13];
                    R[13] = R1314_irq[0];
                    R1314_irq[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_irq[1];
                    R1314_irq[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_irq;
                    spsr_irq = swapCPSR;
                break;

                case 0x13: // Supervisor
                    swapVal = R[13];
                    R[13] = R1314_svc[0];
                    R1314_svc[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_svc[1];
                    R1314_svc[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_svc;
                    spsr_svc = swapCPSR;
                break;

                default:
                    printf("Unknown Current Mode 0x%X!\n",cpsr.mode);
                break;
            }
        break;

        case 0x12:
            switch(cpsr.mode)
            {
                case 0x10: // User
                    swapVal = R[13];
                    R[13] = R1314_irq[0];
                    R1314_irq[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_irq[1];
                    R1314_irq[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_irq;
                    spsr_irq = swapCPSR;
                break;

                case 0x13: // Supervisor
                    swapVal = R[13];
                    R[13] = R1314_irq[0];
                    R1314_irq[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_irq[1];
                    R1314_irq[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_irq;
                    spsr_irq = swapCPSR;
                break;

                case 0x1F: // System
                    swapVal = R[13];
                    R[13] = R1314_irq[0];
                    R1314_irq[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_irq[1];
                    R1314_irq[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_irq;
                    spsr_irq = swapCPSR;
                break;

                default:
                    printf("Unknown Current Mode 0x%X!\n",cpsr.mode);
                break;
            }
        break;

        case 0x13:
            switch(cpsr.mode)
            {
                case 0x10: // User COULD CAUSE ISSUES?
                    swapVal = R[13];
                    R[13] = R1314_svc[0];
                    R1314_svc[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_svc[1];
                    R1314_svc[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_svc;
                    spsr_svc = swapCPSR;
                break;

                case 0x12: // IRQ
                    swapVal = R[13];
                    R[13] = R1314_svc[0];
                    R1314_svc[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_svc[1];
                    R1314_svc[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_svc;
                    spsr_svc = swapCPSR;
                break;

                case 0x1F: // System
                    swapVal = R[13];
                    R[13] = R1314_svc[0];
                    R1314_svc[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_svc[1];
                    R1314_svc[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_svc;
                    spsr_svc = swapCPSR;
                break;

                default:
                    printf("Unknown Current Mode 0x%X!\n",cpsr.mode);
                break;
            }
        break;

        case 0x1F:
            switch(cpsr.mode)
            {
                case 0x12: // IRQ
                    swapVal = R[13];
                    R[13] = R1314_irq[0];
                    R1314_irq[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_irq[1];
                    R1314_irq[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_irq;
                    spsr_irq = swapCPSR;
                break;

                case 0x13: // Supervisor
                    swapVal = R[13];
                    R[13] = R1314_svc[0];
                    R1314_svc[0] = swapVal;

                    swapVal = R[14];
                    R[14] = R1314_svc[1];
                    R1314_svc[1] = swapVal;

                    swapCPSR = spsr;
                    spsr = spsr_svc;
                    spsr_svc = swapCPSR;
                break;

                default:
                    printf("Unknown Current Mode 0x%X!\n",cpsr.mode);
                break;
            }
        break;

        default:
            printf("Unknown Mode Switch 0x%X!\n",switchMode);
        break;
    }
    cpsr.mode = switchMode;
    return 0;
}

uint16_t intToHandle;

/*

void arm9CPU::doInterrupts()
{
    if(io.IME == true && cpsr.I == 0)
    {
        intToHandle = io.IE & io.IF;
        //if((intToHandle & 0x1) == 1 && (((io.dispStat) & 0x8) == 0))
        //{
            //intToHandle &= 0xFFFE;
        //}
        //if((intToHandle & 0x4) == 4 && (((io.dispStat) & 0x20) == 0))
        //{
            //intToHandle &= 0xFFFB;
        //}

        if(intToHandle != 0x0)
        {
            R1314_irq[1] = R[15] + 4;
            spsr_irq = cpsr;
            R[15] = 0x18;
            modeSwitch(0x12);
            cpsr.I = 1;
            cpsr.T = 0;
            //cpsr.mode = 0x12;

            //printf("PC: 0x%X\n",R[15]);
            //ui.pauseEmulation = true;
            //ui.runNoStep = false;
            //ui.useRunTo = false;
        }
    }
}
*/

void armCPU::doOpcode()
{
    //runTHUMB(0);
    //return;
    //if(ui.experimentalSpeedup == true)
    //{
    //    if(R[15] == 0x358 && io.IF == 0)
    //    {
    //        return;
    //    }
    //}
    if(cpsr.T == modeArm)
    {
        decodeAndRunARM();
        return;
    }
    else
    {
        runTHUMB(ram.readMem(R[15], 1));
        return;
    }
    /*
    switch(cpsr.T)
    {
        case modeArm:

        break;

        case modeThumb:

        break;
    }
    */
}
