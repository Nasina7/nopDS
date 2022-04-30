#include "cpu.hpp"
#include "ram.hpp"
#include <stdio.h>
#include <iostream>

#define condEqual 0x0
#define condNotEqual 0x1
#define condCarrySet 0x2
#define condCarryClear 0x3
#define condNegativeSet 0x4
#define condNegativeClear 0x5
#define condOverflowSet 0x6
#define condOverflowClear 0x7
#define condCSetZClear 0x8
#define condCClearOrZSet 0x9
#define condSignedGreaterOrEqual 0xA
#define condSignedLessThan 0xB
#define condGreaterThan 0xC
#define condLessOrEqual 0xD
#define condAlways 0xE

/*

void condEqualFunc()
{
    if(cpsr.Z == 0)
    {
        R[15] += 4;
    }
    if(cpsr.Z == 1)
    {
        runARM(lastOpcodeRan);
    }
}

void condNotEqualFunc()
{
    if(cpsr.Z == 1)
    {
        R[15] += 4;
    }
    if(cpsr.Z == 0)
    {
        runARM(lastOpcodeRan);
    }
}

void condCarrySetFunc()
{
    if(cpsr.C == 0)
    {
        R[15] += 4;
    }
    if(cpsr.C == 1)
    {
        runARM(lastOpcodeRan);
    }
}

void condCarryClearFunc()
{
    if(cpsr.C == 1)
    {
        R[15] += 4;
    }
    if(cpsr.C == 0)
    {
        runARM(lastOpcodeRan);
    }
}

void condNegativeSetFunc()
{
    if(cpsr.N == 0)
    {
        R[15] += 4;
    }
    if(cpsr.N == 1)
    {
        runARM(lastOpcodeRan);
    }
}

void condNegativeClearFunc()
{
    if(cpsr.N == 1)
    {
        R[15] += 4;
    }
    if(cpsr.N == 0)
    {
        runARM(lastOpcodeRan);
    }
}

void condOverflowSetFunc()
{
    if(cpsr.V == 0)
    {
        R[15] += 4;
    }
    if(cpsr.V == 1)
    {
        runARM(lastOpcodeRan);
    }
}

void condOverflowClearFunc()
{
    if(cpsr.V == 1)
    {
        R[15] += 4;
    }
    if(cpsr.V == 0)
    {
        runARM(lastOpcodeRan);
    }
}

void condCSetZClearFunc()
{
    if(cpsr.C == 0 || cpsr.Z == 1)
    {
        R[15] += 4;
    }
    if(cpsr.C == 1 && cpsr.Z == 0)
    {
        runARM(lastOpcodeRan);
    }
}

void condCClearOrZSetFunc()
{
    if(cpsr.C == 1 && cpsr.Z == 0)
    {
        R[15] += 4;
    }
    if(cpsr.C == 0 || cpsr.Z == 1)
    {
        runARM(lastOpcodeRan);
    }
}

void condGreaterThanFunc()
{
    if(cpsr.Z != 0)
    {
        R[15] += 4;
        return;
    }
    if(cpsr.N != cpsr.V)
    {
        R[15] += 4;
        return;
    }
    if(cpsr.Z == 0 && cpsr.N == cpsr.V)
    {
        runARM(lastOpcodeRan);
    }
}

void condLessOrEqualFunc()
{
    if(cpsr.Z == 0 && cpsr.N == cpsr.V)
    {
        R[15] += 4;
        return;
    }
    if(cpsr.Z != 0 || cpsr.N != cpsr.V)
    {
        runARM(lastOpcodeRan);
    }
}

void condSignedGreaterOrEqualFunc()
{
    if(cpsr.V != cpsr.N)
    {
        R[15] += 4;
    }
    if(cpsr.V == cpsr.N)
    {
        runARM(lastOpcodeRan);
    }
}

void condSignedLessThanFunc()
{
    if(cpsr.V == cpsr.N)
    {
        R[15] += 4;
    }
    if(cpsr.V != cpsr.N)
    {
        runARM(lastOpcodeRan);
    }
}

void condAlwaysFunc()
{
   runARM(lastOpcodeRan);
}

void condNeverFunc()
{
    printf("Unknown Condition 0xF!\n");
    printf("PC: 0x%X\n",R[15]);
    ////ui.pauseEmulation = true;
}

typedef void (*armCondLookup)();

const armCondLookup armCondLookupTable[0x10] =
{
    condEqualFunc,
    condNotEqualFunc,
    condCarrySetFunc,
    condCarryClearFunc,
    condNegativeSetFunc,
    condNegativeClearFunc,
    condOverflowSetFunc,
    condOverflowClearFunc,
    condCSetZClearFunc,
    condCClearOrZSetFunc,
    condSignedGreaterOrEqualFunc,
    condSignedLessThanFunc,
    condGreaterThanFunc,
    condLessOrEqualFunc,
    condAlwaysFunc,
    condNeverFunc
};
*/

void armCPU::decodeAndRunARM()
{
    //uint32_t opcode = ram.get32bitOpcode(R[15] - 8);
   // uint32_t opcode = ram.readMem(R[15], 2);
    lastOpcodeRan = ram.readMem(R[15], 2);
    //printf("Opcode: 0x%X\n",opcode);

    uint8_t condition = (lastOpcodeRan >> 28);

    //armCondLookupTable[condition]();
    //return;

    switch(condition)
    {
        case condEqual:
            if(cpsr.Z == 0)
            {
                R[15] += 4;
            }
            if(cpsr.Z == 1)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condNotEqual:
            if(cpsr.Z == 1)
            {
                R[15] += 4;
            }
            if(cpsr.Z == 0)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condCarrySet:
            if(cpsr.C == 0)
            {
                R[15] += 4;
            }
            if(cpsr.C == 1)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condCarryClear:
            if(cpsr.C == 1)
            {
                R[15] += 4;
            }
            if(cpsr.C == 0)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condNegativeSet:
            if(cpsr.N == 0)
            {
                R[15] += 4;
            }
            if(cpsr.N == 1)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condNegativeClear:
            if(cpsr.N == 1)
            {
                R[15] += 4;
            }
            if(cpsr.N == 0)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condOverflowSet:
            if(cpsr.V == 0)
            {
                R[15] += 4;
            }
            if(cpsr.V == 1)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condOverflowClear:
            if(cpsr.V == 1)
            {
                R[15] += 4;
            }
            if(cpsr.V == 0)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condCSetZClear:
            if(cpsr.C == 0 || cpsr.Z == 1)
            {
                R[15] += 4;
            }
            if(cpsr.C == 1 && cpsr.Z == 0)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condCClearOrZSet:
            if(cpsr.C == 1 && cpsr.Z == 0)
            {
                R[15] += 4;
            }
            if(cpsr.C == 0 || cpsr.Z == 1)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condGreaterThan:
            if(cpsr.Z != 0)
            {
                R[15] += 4;
                break;
            }
            if(cpsr.N != cpsr.V)
            {
                R[15] += 4;
                break;
            }
            if(cpsr.Z == 0 && cpsr.N == cpsr.V)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condLessOrEqual:
            if(cpsr.Z == 0 && cpsr.N == cpsr.V)
            {
                R[15] += 4;
                break;
            }
            if(cpsr.Z != 0 || cpsr.N != cpsr.V)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condSignedGreaterOrEqual:
            if(cpsr.V != cpsr.N)
            {
                R[15] += 4;
            }
            if(cpsr.V == cpsr.N)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condSignedLessThan:
            if(cpsr.V == cpsr.N)
            {
                R[15] += 4;
            }
            if(cpsr.V != cpsr.N)
            {
                runARM(lastOpcodeRan);
            }
        break;

        case condAlways:
            runARM(lastOpcodeRan);
        break;

        default:
            printf("Unknown Condition 0x%X!\n",condition);
            printf("PC: 0x%X\n",R[15]);
            ////ui.pauseEmulation = true;
        break;
    }
}

void armCPU::runARM(uint32_t opcode)
{

    switch((opcode & 0x0E000000) >> 25) // Get XXXXYYYXXXXXXXXX
    {
        case 0: // 000


            // Check for 7=1 and 4=1
                // Checks for Multiplies / Extra Load Stores
            if(((opcode >> 7) & 0x1) == 1 && ((opcode >> 4) & 0x1) == 1)
            {
                switch((opcode >> 4) & 0xF)
                {
                    case 0x9: //Multiplies
                        switch((opcode >> 21) & 0x7)
                        {
                            case 0: // Multiply
                                switch((opcode >> 24) & 0x1)
                                {
                                    case 0:
                                        MUL(opcode);
                                    break;

                                    case 1:
                                        // Apparently this decodes to SWP?
                                        SWP(opcode);
                                    break;
                                }

                            break;

                            case 1: // Multiply Accumulate
                                MLA(opcode);
                            break;

                            case 2:
                                SWPB(opcode);
                            break;

                            case 4: // Unsigned Multiply Long
                                UMULL(opcode);
                            break;

                            case 5: // Unsigned Multiply Accumulate Long
                                UMLAL(opcode);
                            break;

                            case 6: // Signed Multiply Long
                                SMULL(opcode);
                            break;

                            case 7: // Signed Multiply Accumulate Long
                                SMLAL(opcode);
                            break;

                            default:
                                printf("Undefined Multiply! 0x%X\n", R[15]);
                                //ui.pauseEmulation = true;
                            break;
                        }
                    break;

                    case 0xB: // Load store halfword
                        switch((opcode >> 22) & 0x1)
                        {
                            case 0:
                                LDST_HW_REG(opcode);
                            break;

                            case 1:
                                LDST_HW_IMD(opcode);
                            break;
                        }
                    break;

                    case 0xD ... 0xF: // Other LD/ST instructions
                        switch((opcode >> 22) & 0x1)
                        {
                            case 0:
                                LDST_HWB_REG(opcode);
                            break;

                            case 1:
                                LDST_HWB_IMD(opcode);
                            break;
                        }
                    break;
                }
                return; // Break out of run opcode
            }
            // Check for 24=1 and 23=0 and 20=0
                // Checks for Misc Instructions
            if(((opcode >> 24) & 0x1) == 1 && ((opcode >> 23) & 0x1) == 0 && ((opcode >> 20) & 0x1) == 0)
            {
                switch((opcode >> 4) & 0xF)
                {
                    case 0x0:
                        switch((opcode >> 21) & 0x1)
                        {
                            case 0:
                                MISC_MOV_SR_R(opcode);
                            break;

                            case 1:
                                MISC_MOV_R_SR(opcode);
                            break;
                        }
                    break;

                    case 0x1:
                        switch((opcode >> 22) & 0x1)
                        {
                            case 0:
                                BX(opcode);
                            break;

                            case 1:
                                printf("COUNT LEADING ZEROS NOT IMPLEMENTED!\n");
                                while(true)
                                {

                                }
                            break;
                        }
                    break;

                    default:
                        printf("UNIMPLEMENTED MISC INSTRUCTION 0x%X!\n",(opcode >> 4) & 0xF);
                        while(true)
                        {
                            // Temp
                        }
                    break;
                }
                return;
            }
            // Check for 4=1
                // Checks for Data Processing Register
            if(((opcode >> 4) & 0x1) == 1)
            {
                switch(((opcode >> 21) & 0xF)) // DATA PROCESSING IMMEDIATE
                {
                    case 0x0:
                        DPRS_AND(opcode);
                    break;

                    case 0x2:
                        DPRS_SUB(opcode);
                    break;

                    case 0x4:
                        DPRS_ADD(opcode);
                    break;

                    case 0x5:
                        DPRS_ADC(opcode);
                    break;

                    case 0x9:
                        DPRS_TEQ(opcode);
                    break;

                    case 0xC:
                        DPRS_ORR(opcode);
                    break;

                    case 0xD:
                        DPRS_MOV(opcode);
                    break;

                    case 0xE:
                        DPRS_BIC(opcode);
                    break;

                    default:
                        printf("DPRS 0x%X NOT IMPLEMENTED!\n",((opcode >> 21) & 0xF));
                        //ui.pauseEmulation = true;
                    break;
                }
                return;
            }
            // Check for 4=0
                // Checks for Data Processing Immediate Shift
            if(((opcode >> 4) & 0x1) == 0)
            {
                switch(((opcode >> 21) & 0xF)) // DATA PROCESSING IMMEDIATE
                {
                    case 0x0:
                        DPIS_AND(opcode);
                    break;

                    case 0x1:
                        DPIS_EOR(opcode);
                    break;

                    case 0x2:
                        DPIS_SUB(opcode);
                    break;

                    case 0x3:
                        DPIS_RSB(opcode);
                    break;

                    case 0x4:
                        DPIS_ADD(opcode);
                    break;

                    case 0x5:
                        DPIS_ADC(opcode);
                    break;

                    case 0x6:
                        DPIS_SBC(opcode);
                    break;

                    case 0x7:
                        DPIS_RSC(opcode);
                    break;

                    case 0x8:
                        DPIS_TST(opcode);
                    break;

                    case 0x9:
                        DPIS_TEQ(opcode);
                    break;

                    case 0xA:
                        DPIS_CMP(opcode);
                    break;

                    case 0xB:
                        DPIS_CMN(opcode);
                    break;

                    case 0xC:
                        DPIS_ORR(opcode);
                    break;

                    case 0xD:
                        DPIS_MOV(opcode);
                    break;

                    case 0xE:
                        DPIS_BIC(opcode);
                    break;

                    case 0xF:
                        DPIS_MVN(opcode);
                    break;

                    default:
                        printf("IMPOSSIBLE CODE PATH!\n");
                        //ui.pauseEmulation = true;
                    break;
                }
                return;
            }
            return;
        break;

        case 1: // 001
            // Check for SR Transfer
            if(((opcode >> 23) & 0x3) == 0x2 && ((opcode >> 20) & 0x1) == 0x0) // SR Transfer
            {
                MISC_MOV_I_SR(opcode);
            }
            switch(((opcode >> 21) & 0xF)) // DATA PROCESSING IMMEDIATE
            {

                case 0x0:
                    DPI_AND(opcode);
                break;

                case 0x1:
                    DPI_EOR(opcode);
                break;

                case 0x2:
                    DPI_SUB(opcode);
                break;

                case 0x3:
                    DPI_RSB(opcode);
                break;

                case 0x4:
                    DPI_ADD(opcode);
                break;

                case 0x5:
                    DPI_ADC(opcode);
                break;

                case 0x6:
                    DPI_SBC(opcode);
                break;

                case 0x7:
                    DPI_RSC(opcode);
                break;

                case 0x8:
                    DPI_TST(opcode);
                break;

                case 0x9:
                    DPI_TEQ(opcode);
                break;

                case 0xA:
                    DPI_CMP(opcode);
                break;

                case 0xB:
                    DPI_CMN(opcode);
                break;

                case 0xC:
                    DPI_ORR(opcode);
                break;

                case 0xD:
                    DPI_MOV(opcode);
                break;

                case 0xE:
                    DPI_BIC(opcode);
                break;

                case 0xF:
                    DPI_MVN(opcode);
                break;

                default:
                    printf("BAD_ERROR: Data Processing Immediate 0x%X not implemented!\n",((opcode >> 21) & 0xF));
                    //ui.pauseEmulation = true;
                break;
            }

        break;

        case 2: // 010    LOAD STORE IMMEDIATE
                 // Needs Immed, Immed Pre Indexed, Immed Post Indexed
            switch((opcode >> 24) & 0x1)
            {
                case 0: // Immed Post Indexed
                    switch((opcode >> 21) & 0x1)
                    {
                        case 0: // Immed Post Indexed
                            LDST_IMD_POST(opcode);
                        break;

                        case 1: // IDK what this decodes to, need to check later
                            printf("UNKNOWN IMMED COMBO!\n");
                            //ui.pauseEmulation = true;
                        break;
                    }
                break;

                case 1:
                    switch((opcode >> 21) & 0x1)
                    {
                        case 0: // Immed
                            LDST_IMD(opcode);
                        break;

                        case 1: // Immed Pre Indexed
                            LDST_IMD_PRE(opcode);
                        break;
                    }
                break;
            }
        break;

        case 3: // Load Store Register Offset
            switch((opcode >> 24) & 0x1)
            {
                case 0: // Immed Post Indexed
                    switch((opcode >> 21) & 0x1)
                    {
                        case 0: // Immed Post Indexed
                            LDST_REG_POST(opcode);
                        break;

                        case 1: // IDK what this decodes to, need to check later
                            printf("UNKNOWN IMMED COMBO!\n");
                            //ui.pauseEmulation = true;
                        break;
                    }
                break;

                case 1:
                    switch((opcode >> 21) & 0x1)
                    {
                        case 0: // Immed
                            LDST_REG(opcode);
                        break;

                        case 1: // Immed Pre Indexed
                            //LDST_IMD_PRE(opcode);
                           LDST_REG_PRE(opcode);
                        break;
                    }
                break;
            }
        break;

        case 4: // Load Store Multiple
            /*
                If LOADING PC, S indicates CPSR = SPSR
                For all STM and (LDM that doesn't load PC), S indicates that we are using the user mode banked registers, and not
                    the registers for the current mode [HAVEN'T IMPLEMENTED THIS YET, THROWS ERROR IF USED]

                P,U,and W indicate different addressing modes

                L indicates a load or store


                Bits that can be handled within a function,
                    W
                    U
                    P
                    If STM, S

                This is gonna be a mess, will need to cleanup later
            */

            switch((opcode >> 20) & 0x1)
            {
                case 0: // STM
                    STMIA(opcode);
                break;

                case 1: // LDM
                    LDMIA(opcode);
                break;
            }
            ////ui.pauseEmulation = true;


        break;

        case 5: // 101
            switch((opcode & 0xF0000000) >> 28)
            {
                case 0xF:
                    printf("Unimplemented Branch and Branch with Link and Change to Thumb!\n");
                    //ui.pauseEmulation = true;
                break;

                default: // Branch and Branch with Link
                    BL(opcode);
                break;
            }
        break;

        case 6:
            // Coprocessor load/store and double register transfers
            std::cout<<"WARN: Coprocessor load/store and double register transfers is NOT IMPLEMENTED!"<<std::endl;
            R[15] += 4;
            //while(1)
            //{

            //}
        break;

        case 7:
            if(!ram.cpuIsArm9)
            {
                SWI(opcode);
            }
            else
            {
                switch((opcode >> 24) & 0x1)
                {
                    case 0:
                        switch((opcode >> 4) & 0x1)
                        {
                            case 0:
                                // Coprocessor Data Processing
                                std::cout<<"WARN: Coprocessor Data Processing is NOT IMPLEMENTED!"<<std::endl;
                                R[15] += 4;
                                //while(1)
                                //{

                                //}
                            break;

                            case 1:
                                // Coprocessor Register Transfers
                                switch((opcode >> 20) & 0x1)
                                {
                                    case 0:
                                        // Move to Coprocessor from ARM Register
                                        R[15] += 4;
                                        std::cout<<"Move to Coprocessor from ARM Register is NOT IMPLEMENTED!"<<std::endl;
                                        //while(1)
                                        //{

                                        //}
                                    break;

                                    case 1:
                                        // Move to ARM Register from Coprocessor
                                        A9_MRC(opcode);
                                    break;
                                }
                            break;
                        }
                    break;

                    case 1:
                        SWI(opcode);
                    break;
                }
            }
        break;

        default:
            printf("Unimplemented opcode 0x%X\n",opcode);
            //ui.pauseEmulation = true;
        break;
    }
}

// BEGINNING OF ARM OPCODES

void armCPU::SWI(uint32_t opcode)
{
    R1314_svc[1] = (R[15] + 4);
    spsr_svc = cpsr;
    modeSwitch(0x13);
    cpsr.T = false;
    cpsr.I = true;
    R[15] = 0x8;
}

void armCPU::BL(uint32_t opcode) // Branch or Branch with Link
{
    ////ui.pauseEmulation = true;
    R[15] += 4;
    int branchOffset = opcode & 0x00FFFFFF;
    branchOffset = ((branchOffset << 8) >> 6); // Sign Extend
    if((opcode & 0x01000000) != 0)
    {
        R[14] = (R[15]);
    }
    R[15] = ((R[15] + branchOffset) + 4);
}

void armCPU::BX(uint32_t opcode) // Branch or Branch with Link
{
    uint8_t Rm = ((opcode) & 0xF);
    cpsr.T = ((R[Rm] & 0x1) != 0);
    R[15] = R[Rm] & 0xFFFFFFFE;
}

void armCPU::DPI_ADD(uint32_t opcode)
{
    R[15] += 8;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    uint32_t result = R[Rn] + aluVal;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)aluVal));
            cpsr.V = ( ~ ( (uint64_t)R[Rn] ^ ( (uint64_t)aluVal ) ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[15] -= 4;
    R[Rd] = result;
}
void armCPU::DPI_CMN(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    uint32_t result = R[Rn] + aluVal;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)aluVal));
            cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ (uint64_t)R[Rn] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[15] += 4;
}

void armCPU::DPI_ADC(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    uint32_t result = R[Rn] + aluVal + cpsr.C;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)aluVal + (uint64_t)cpsr.C));
            cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ ( (uint64_t)R[Rn] + (uint64_t)cpsr.C ) ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4;
    }
}

void armCPU::DPI_SUB(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    uint32_t result = R[Rn] - aluVal;
    //printf("SUSSY: 0x%X\n",aluVal);

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)aluVal));
            cpsr.V = (( (uint64_t)R[Rn] ^ (uint64_t)aluVal ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4;
    }

}

void armCPU::DPI_CMP(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    uint32_t result = R[Rn] - aluVal;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)aluVal));
            cpsr.V = (( (uint64_t)R[Rn] ^ (uint64_t)aluVal ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[15] += 4;
}

void armCPU::DPI_SBC(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    uint32_t result = R[Rn] - aluVal - (!cpsr.C);

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)aluVal - (uint64_t)(!cpsr.C)));
            cpsr.V = ( ( (uint64_t)R[Rn] ^ ( (uint64_t)aluVal + (uint64_t)(!cpsr.C) ) ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4;
    }
}

void armCPU::DPI_RSB(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    uint32_t result = aluVal - R[Rn];

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)aluVal - (uint64_t)R[Rn]));
            cpsr.V = (( (uint64_t)aluVal ^ (uint64_t)R[Rn] ) &
                     ( ( (uint64_t)aluVal ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4;
    }
}

void armCPU::DPI_RSC(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    uint32_t result = aluVal - R[Rn] - (!cpsr.C);

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)aluVal - (uint64_t)R[Rn] - (uint64_t)(!cpsr.C)));
            cpsr.V = ( ( (uint64_t)aluVal ^ ( (uint64_t)R[Rn] - (uint64_t)(!cpsr.C) ) ) &
                     ( ( (uint64_t)aluVal ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4; // Could be an issue?
    }
}

void armCPU::DPI_EOR(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    bool carryOut = cpsr.C;
    if(shiftAmount != 0)
    {
        carryOut = ((rotr32(value,(shiftAmount - 1)) & 0x80000000) != 0);
    }
    uint32_t result = R[Rn] ^ aluVal;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4;
    }
}

void armCPU::DPI_ORR(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    bool carryOut = cpsr.C;
    if(shiftAmount != 0)
    {
        carryOut = ((rotr32(value,(shiftAmount - 1)) & 0x80000000) != 0);
    }
    uint32_t result = R[Rn] | aluVal;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4;
    }
}

void armCPU::DPI_TEQ(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    bool carryOut = cpsr.C;
    if(shiftAmount != 0)
    {
        carryOut = ((rotr32(value,(shiftAmount - 1)) & 0x80000000) != 0);
    }
    uint32_t result = R[Rn] ^ aluVal;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    if(Rd != 0xF)
    {
        R[15] += 4; // Could be an issue?
    }
}

void armCPU::DPI_AND(uint32_t opcode)
{
    R[15] += 4;
    R[15] += 8;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal;
    if(shiftAmount != 0)
    {
        aluVal = rotr32(value,shiftAmount);
    }
    else
    {
        aluVal = value;
    }
    bool carryOut = cpsr.C;
    if(shiftAmount != 0)
    {
        carryOut = ((rotr32(value,(shiftAmount)) & 0x80000000) != 0);
    }
    uint32_t result = R[Rn] & aluVal;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[15] -= 8;
    R[Rd] = result;
}

void armCPU::DPI_BIC(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    bool carryOut = cpsr.C;
    if(shiftAmount != 0)
    {
        carryOut = ((rotr32(value,(shiftAmount - 1)) & 0x80000000) != 0);
    }
    uint32_t result = R[Rn] & (~aluVal);

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4; // Could be an issue?
    }
}

void armCPU::DPI_TST(uint32_t opcode)
{
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    shiftAmount *= 2;
    uint32_t aluVal = rotr32(value,shiftAmount);
    bool carryOut = cpsr.C;
    if(shiftAmount != 0)
    {
        carryOut = ((rotr32(value,(shiftAmount - 1)) & 0x80000000) != 0);
    }
    uint32_t result = R[Rn] & aluVal;

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
        }
    }
    if(Rd == 0xF)
    {
        if(cpsr.T == 0)
        {
            R[15] += 8;
        }
        if(cpsr.T == 1)
        {
            R[15] += 4;
        }
    }
    if(Rd != 0xF)
    {
        R[15] += 4; // Could be an issue?
    }
}

void armCPU::DPI_MOV(uint32_t opcode)
{
    R[15] += 4;
    ////ui.pauseEmulation = true;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    shiftAmount *= 2;
    R[Rd] = rotr32(value,shiftAmount);
    bool carryOut = cpsr.C;
    if(shiftAmount != 0)
    {
        carryOut = ((rotr32(value,(shiftAmount - 1)) & 0x80000000) != 0);
    }

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        cpsr.N = ((R[Rd] & 0x80000000) != 0);
        cpsr.Z = (R[Rd] == 0);
        cpsr.C = carryOut;
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
    }

}

void armCPU::DPI_MVN(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    shiftAmount *= 2;
    R[Rd] = (~(rotr32(value,shiftAmount)));
    bool carryOut = cpsr.C;
    if(shiftAmount != 0)
    {
        carryOut = ((rotr32(value,(shiftAmount - 1)) & 0x80000000) != 0);
    }

    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        cpsr.N = ((R[Rd] & 0x80000000) != 0);
        cpsr.Z = (R[Rd] == 0);
        cpsr.C = carryOut;
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
    }
}

void armCPU::LDST_IMD(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint16_t offset = (opcode & 0x0FFF);
    bool U, B, L;
    U = ((opcode >> 23) & 0x1);
    B = ((opcode >> 22) & 0x1);
    L = ((opcode >> 20) & 0x1);
    uint32_t address;
    switch(U)
    {
        case 0:
            address = R[Rn] - offset;
            if(Rn == 0xF)
            {
                address += 4;
            }
        break;

        case 1:
            address = R[Rn] + offset;
            if(Rn == 0xF)
            {
                address += 4;
            }
        break;
    }
    switch(B << 1 | L)
    {
        case 0: // Store Word (32 bit)
            if(Rd != 15)
            {
                ram.writeMem(address,2,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,2,R[Rd] + 4);
            }
        break;

        case 1: // Load Word (32 bit)
            R[Rd] = ram.readMem(address,2); // TODO, ADD ADDRESS ROTATION
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;

        case 2: // Store Byte
            if(Rd != 15)
            {
                ram.writeMem(address,0,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,0,R[Rd] + 4);
            }
        break;

        case 3: // Load Byte
            R[Rd] = ram.readMem(address,0);
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;
    }
}
void armCPU::LDST_IMD_PRE(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint16_t offset = (opcode & 0x0FFF);
    bool U, B, L;
    U = ((opcode >> 23) & 0x1);
    B = ((opcode >> 22) & 0x1);
    L = ((opcode >> 20) & 0x1);
    uint32_t address;
    switch(U)
    {
        case 0:
            address = R[Rn] - offset;
            if(Rn == 0xF)
            {
                address += 4;
            }
            R[Rn] = address;
        break;

        case 1:
            address = R[Rn] + offset;
            if(Rn == 0xF)
            {
                address += 4;
            }
            R[Rn] = address;
        break;
    }
    switch(B << 1 | L)
    {
        case 0: // Store Word (32 bit)
            if(Rd != 15)
            {
                ram.writeMem(address,2,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,2,R[Rd] + 4);
            }
        break;

        case 1: // Load Word (32 bit)
            R[Rd] = ram.readMem(address,2); // TODO, ADD ADDRESS ROTATION
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;

        case 2: // Store Byte
            if(Rd != 15)
            {
                ram.writeMem(address,0,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,0,R[Rd] + 4);
            }
        break;

        case 3: // Load Byte
            R[Rd] = ram.readMem(address,0);
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;
    }
}
void armCPU::LDST_IMD_POST(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint16_t offset = (opcode & 0x0FFF);
    bool U, B, L;
    U = ((opcode >> 23) & 0x1);
    B = ((opcode >> 22) & 0x1);
    L = ((opcode >> 20) & 0x1);
    uint32_t address = R[Rn];
    switch(U)
    {
        case 0:
            //address = R[Rn] - offset;
            R[Rn] = address - offset;
            if(Rn == 0xF)
            {
                R[Rn] += 4;
            }
        break;

        case 1:
            //address = R[Rn] + offset;
            R[Rn] = address + offset;
            if(Rn == 0xF)
            {
                R[Rn] += 4;
            }
        break;
    }
    switch(B << 1 | L)
    {
        case 0: // Store Word (32 bit)
            if(Rd != 15)
            {
                ram.writeMem(address,2,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,2,R[Rd] + 8);
            }
        break;

        case 1: // Load Word (32 bit)
            R[Rd] = ram.readMem(address,2); // TODO, ADD ADDRESS ROTATION
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;

        case 2: // Store Byte
            if(Rd != 15)
            {
                ram.writeMem(address,0,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,0,R[Rd] + 8);
            }
        break;

        case 3: // Load Byte
            R[Rd] = ram.readMem(address,0);
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;
    }
}

void armCPU::MISC_MOV_SR_R(uint32_t opcode)
{
    uint8_t Rd = ((opcode >> 12) & 0xF);
    if(((opcode >> 22) & 0x1) != 0)
    {
        R[Rd] = readCPSR(spsr);
    }
    if(((opcode >> 22) & 0x1) == 0)
    {
        R[Rd] = readCPSR(cpsr);
    }
    R[15] += 4;
}

void armCPU::MISC_MOV_R_SR(uint32_t opcode)
{
    uint8_t Rm = (opcode & 0xF);
    bool f,s,x,c;
    f = ((opcode >> 19) & 0x1);
    s = ((opcode >> 18) & 0x1);
    x = ((opcode >> 17) & 0x1);
    c = ((opcode >> 16) & 0x1);

    if(((opcode >> 22) & 0x1) != 0)
    {
        uint32_t curCPSR = readCPSR(spsr);
        if(f == true)
        {
            curCPSR = curCPSR & 0x00FFFFFF;
            curCPSR = curCPSR | (R[Rm] & 0xFF000000);
        }
        if(s == true)
        {
            curCPSR = curCPSR & 0xFF00FFFF;
            curCPSR = curCPSR | (R[Rm] & 0x00FF0000);
        }
        if(x == true)
        {
            curCPSR = curCPSR & 0xFFFF00FF;
            curCPSR = curCPSR | (R[Rm] & 0x0000FF00);
        }
        if(c == true)
        {
            curCPSR = curCPSR & 0xFFFFFF00;
            curCPSR = curCPSR | (R[Rm] & 0x000000FF);
        }
        spsr = writeCPSR(spsr, curCPSR, false);
    }
    if(((opcode >> 22) & 0x1) == 0)
    {
        
        //R[Rm] = readCPSR(cpsr);
        uint32_t curCPSR = readCPSR(cpsr);
        if(f == true)
        {
            curCPSR = curCPSR & 0x00FFFFFF;
            curCPSR = curCPSR | (R[Rm] & 0xFF000000);
        }
        if(s == true)
        {
            curCPSR = curCPSR & 0xFF00FFFF;
            curCPSR = curCPSR | (R[Rm] & 0x00FF0000);
        }
        if(x == true)
        {
            curCPSR = curCPSR & 0xFFFF00FF;
            curCPSR = curCPSR | (R[Rm] & 0x0000FF00);
        }
        if(c == true)
        {
            curCPSR = curCPSR & 0xFFFFFF00;
            curCPSR = curCPSR | (R[Rm] & 0x000000FF);
            //std::cout<<std::hex<<curCPSR<<std::endl;
        }
        cpsr = writeCPSR(cpsr, curCPSR, true);
    }
    R[15] += 4;
}

void armCPU::MISC_MOV_I_SR(uint32_t opcode)
{
    //ui.pauseEmulation = ui.allowPauseEmulation;
    uint32_t immedVal = (opcode & 0xFF);
    uint8_t rotAmount = ((opcode >> 8) & 0xF);
    immedVal = rotr32(immedVal, rotAmount * 2);
    bool f,s,x,c;
    f = ((opcode >> 19) & 0x1);
    s = ((opcode >> 18) & 0x1);
    x = ((opcode >> 17) & 0x1);
    c = ((opcode >> 16) & 0x1);

    if(((opcode >> 22) & 0x1) != 0)
    {
        uint32_t curCPSR = readCPSR(spsr);
        if(f == true)
        {
            curCPSR = curCPSR & 0x00FFFFFF;
            curCPSR = curCPSR | (immedVal & 0xFF000000);
        }
        if(s == true)
        {
            curCPSR = curCPSR & 0xFF00FFFF;
            curCPSR = curCPSR | (immedVal & 0x00FF0000);
        }
        if(x == true)
        {
            curCPSR = curCPSR & 0xFFFF00FF;
            curCPSR = curCPSR | (immedVal & 0x0000FF00);
        }
        if(c == true)
        {
            curCPSR = curCPSR & 0xFFFFFF00;
            curCPSR = curCPSR | (immedVal & 0x000000FF);
        }
        spsr = writeCPSR(spsr, curCPSR, false);
    }
    if(((opcode >> 22) & 0x1) == 0)
    {
        //R[Rm] = readCPSR(cpsr);
        uint32_t curCPSR = readCPSR(cpsr);
        if(f == true)
        {
            curCPSR = curCPSR & 0x00FFFFFF;
            curCPSR = curCPSR | (immedVal & 0xFF000000);
        }
        if(s == true)
        {
            curCPSR = curCPSR & 0xFF00FFFF;
            curCPSR = curCPSR | (immedVal & 0x00FF0000);
        }
        if(x == true)
        {
            curCPSR = curCPSR & 0xFFFF00FF;
            curCPSR = curCPSR | (immedVal & 0x0000FF00);
        }
        if(c == true)
        {
            curCPSR = curCPSR & 0xFFFFFF00;
            curCPSR = curCPSR | (immedVal & 0x000000FF);
        }
        cpsr = writeCPSR(cpsr, curCPSR, true);
    }
    R[15] += 4;
}

void armCPU::LDST_HW_REG(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint16_t offset = R[(opcode & 0xF)];



    bool U, P, W, L;
    // L = Load or Store
    // U = Plus or Minus for offset
    // I = Register or Immediate offset
    // P & W = Addressing Mode
    U = ((opcode >> 23) & 0x1);
    P = ((opcode >> 24) & 0x1);
    W = ((opcode >> 21) & 0x1);
    L = ((opcode >> 20) & 0x1);

    /*
    PW
    00 = Post Indexed
    11 = Pre Indexed
    10 = Normal

    */
    uint8_t PW = (P << 1) | W;
    uint32_t address;
    if(PW == 0)
    {
        address = R[Rn];
    }
    if(PW != 0)
    {
        switch(U)
        {
            case 0:
                address = R[Rn] - offset;
            break;

            case 1:
                address = R[Rn] + offset;
            break;
        }
    }
    switch(L)
    {
        case 0: // Store Word (32 bit)
            if(Rd != 15)
            {
                ram.writeMem(address,1,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,1,R[Rd] + 8);
            }
        break;

        case 1: // Load Word (32 bit)
            R[Rd] = ram.readMem(address,1); // TODO, ADD ADDRESS ROTATION
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;
    }
    if(PW == 3)
    {
        R[Rn] = address;
    }
    if(PW == 0)
    {
        switch(U)
        {
            case 0:
                R[Rn] = R[Rn] - offset;
            break;

            case 1:
                R[Rn] = R[Rn] + offset;
            break;
        }
        // Kinda big, need to optimize here
    }
}

void armCPU::LDST_HW_IMD(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint32_t offset = (((opcode >> 8) & 0xF) << 4) | (opcode & 0xF);



    bool U, P, W, L;
    // L = Load or Store
    // U = Plus or Minus for offset
    // P & W = Addressing Mode
    U = ((opcode >> 23) & 0x1);
    P = ((opcode >> 24) & 0x1);
    W = ((opcode >> 21) & 0x1);
    L = ((opcode >> 20) & 0x1);

    /*
    PW
    00 = Post Indexed
    11 = Pre Indexed
    10 = Normal

    */
    uint8_t PW = ((P & 0x1) << 1) | (W & 0x1);
    uint32_t address;
    if(PW == 0)
    {
        address = R[Rn];
    }
    if(PW != 0)
    {
        switch(U)
        {
            case false:
                address = R[Rn] - offset;
            break;

            case true:
                address = R[Rn] + offset;
            break;
        }
    }
    if(PW == 3)
    {
        R[Rn] = address;
    }
    switch(L)
    {
        case false: // Store Word (32 bit)
            if(Rd != 15)
            {
                ram.writeMem(address,1,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,1,R[Rd] + 8);
            }
        break;

        case true: // Load Word (32 bit)
            R[Rd] = ram.readMem(address,1); // TODO, ADD ADDRESS ROTATION
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;
    }
    if(PW == 0)
    {
        switch(U)
        {
            case false:
                R[Rn] = R[Rn] - offset;
            break;

            case true:
                R[Rn] = R[Rn] + offset;
            break;
        }
        // Kinda big, need to optimize here
    }
}

void armCPU::LDST_HWB_IMD(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint32_t offset = (((opcode >> 8) & 0xF) << 4) | (opcode & 0xF);



    bool U, P, W, L;
    bool sizeB = ((opcode >> 5) & 0x1);
    // L = Load or Store
    // U = Plus or Minus for offset
    // I = Immediate or Register
    // P & W = Addressing Mode
    U = ((opcode >> 23) & 0x1);
    P = ((opcode >> 24) & 0x1);
    W = ((opcode >> 21) & 0x1);
    L = ((opcode >> 20) & 0x1);

    /*
    PW
    00 = Post Indexed
    11 = Pre Indexed
    10 = Normal

    */
    uint8_t PW = ((P & 0x1) << 1) | (W & 0x1);
    uint32_t address;
    if(PW == 0)
    {
        address = R[Rn];
    }
    if(PW != 0)
    {
        switch(U)
        {
            case false:
                address = R[Rn] - offset;
            break;

            case true:
                address = R[Rn] + offset;
            break;
        }
    }
    if(PW == 3)
    {
        R[Rn] = address;
        //if(ui.allowPauseEmulation == true)
        //{
            //ui.pauseEmulation = true;
        //}
    }
    switch(L)
    {
        case false: // Store Word (32 bit)
            switch(sizeB)
            {
                case false: // Byte
                    if(Rd != 15)
                    {
                        ram.writeMem(address,0,R[Rd]);
                    }
                    if(Rd == 15)
                    {
                        ram.writeMem(address,0,R[Rd] + 8);
                    }
                break;

                case true:
                    if(Rd != 15)
                    {
                        ram.writeMem(address,1,R[Rd]);
                    }
                    if(Rd == 15)
                    {
                        ram.writeMem(address,1,R[Rd] + 8);
                    }
                break;
            }

        break;

        case true: // Load Word (32 bit)
            switch(sizeB)
            {
                case false:
                    {
                        int32_t signExtend = ram.readMem(address,0); // TODO, ADD ADDRESS ROTATION
                        //printf("SIGN: 0x%X\n", signExtend);
                        //int64_t signExtend = R[Rd]
                        signExtend = signExtend << 24;
                        //printf("SIGN3: 0x%X\n", signExtend);
                        signExtend = signExtend >> 24;
                        //printf("SIGN2: 0x%X\n", signExtend);
                        R[Rd] = signExtend;
                    }
                break;

                case true:
                    {
                        int32_t signExtend = ram.readMem(address,1); // TODO, ADD ADDRESS ROTATION
                        //int64_t signExtend = R[Rd]
                        signExtend = signExtend << 16;
                        signExtend = signExtend >> 16;
                        R[Rd] = signExtend;
                    }
                break;
            }

        break;
    }
    if(PW == 0)
    {
        switch(U)
        {
            case false:
                R[Rn] = R[Rn] - offset;
            break;

            case true:
                R[Rn] = R[Rn] + offset;
            break;
        }
        // Kinda big, need to optimize here
    }
}


void armCPU::LDST_HWB_REG(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint32_t offset = R[Rm];



    bool U, P, W, L;
    bool sizeB = ((opcode >> 5) & 0x1);
    // L = Load or Store
    // U = Plus or Minus for offset
    // I = Immediate or Register
    // P & W = Addressing Mode
    U = ((opcode >> 23) & 0x1);
    P = ((opcode >> 24) & 0x1);
    W = ((opcode >> 21) & 0x1);
    L = ((opcode >> 20) & 0x1);

    /*
    PW
    00 = Post Indexed
    11 = Pre Indexed
    10 = Normal

    */
    uint8_t PW = ((P & 0x1) << 1) | (W & 0x1);
    uint32_t address;
    if(PW == 0)
    {
        address = R[Rn];
    }
    if(PW != 0)
    {
        switch(U)
        {
            case false:
                address = R[Rn] - offset;
            break;

            case true:
                address = R[Rn] + offset;
            break;
        }
    }
    if(PW == 3)
    {
        R[Rn] = address;
        //if(ui.allowPauseEmulation == true)
        //{
            //ui.pauseEmulation = true;
        //}
    }
    switch(L)
    {
        case false: // Store Word (32 bit)
            switch(sizeB)
            {
                case false: // Byte
                    if(Rd != 15)
                    {
                        ram.writeMem(address,0,R[Rd]);
                    }
                    if(Rd == 15)
                    {
                        ram.writeMem(address,0,R[Rd] + 8);
                    }
                break;

                case true:
                    if(Rd != 15)
                    {
                        ram.writeMem(address,1,R[Rd]);
                    }
                    if(Rd == 15)
                    {
                        ram.writeMem(address,1,R[Rd] + 8);
                    }
                break;
            }

        break;

        case true: // Load Word (32 bit)
            switch(sizeB)
            {
                case false:
                    {
                        //printf("SIGN\n");
                        int32_t signExtend = ram.readMem(address,0); // TODO, ADD ADDRESS ROTATION
                        //printf("0x%X\n",signExtend);
                        //int64_t signExtend = R[Rd]
                        signExtend = signExtend << 24;
                        signExtend = signExtend >> 24;
                        R[Rd] = signExtend;
                    }
                break;

                case true:
                    {
                        int32_t signExtend = ram.readMem(address,1); // TODO, ADD ADDRESS ROTATION
                        //int64_t signExtend = R[Rd]
                        signExtend = signExtend << 16;
                        signExtend = signExtend >> 16;
                        R[Rd] = signExtend;
                    }
                break;
            }

        break;
    }
    if(PW == 0)
    {
        switch(U)
        {
            case false:
                R[Rn] = R[Rn] - offset;
            break;

            case true:
                R[Rn] = R[Rn] + offset;
            break;
        }
        // Kinda big, need to optimize here
    }
}

void armCPU::LDMIA(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint16_t regList = (opcode & 0xFFFF);
    bool P,U,W,S;
    P = ((opcode >> 24) & 0x1);
    U = ((opcode >> 23) & 0x1);
    W = ((opcode >> 21) & 0x1);
    S = ((opcode >> 22) & 0x1);

    uint8_t setBits = 0;
    bool setBitArray[16];
    for(int i = 0; i < 16; i++)
    {
        setBitArray[i] = false;
        if(((regList >> i) & 0x1) != 0)
        {
            setBits++;
            setBitArray[i] = true;
        }
    }

    uint32_t startAddress = R[Rn];
    switch((P << 1) | U)
    {
        case 0: // Decrement After
            startAddress -= (setBits * 4);
            startAddress += 4;
        break;

        case 1: // Increment After

        break;

        case 2: // Decrement Before
            startAddress -= (setBits * 4);
        break;

        case 3: // Increment Before
            startAddress += 4;
        break;
    }

    uint8_t cpsrModeCurrent = cpsr.mode;
    if(S == 1 && setBitArray[15] == false)
    {
        ////ui.pauseEmulation = true;
        modeSwitch(0x10);
    }

    uint32_t endAddress = R[Rn] + (setBits * 4);
    if(P == 0)
    {
        endAddress -= 4;
    }


    for(int i = 0; i < 16; i++)
    {
        if(setBitArray[i] == true)
        {
            R[i] = ram.readMem(startAddress, 2); // Is this correct?
            startAddress += 4;
            if(i == 15)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        }
    }
    if(S == 1 && setBitArray[15] == false)
    {
        modeSwitch(cpsrModeCurrent);
    }
    if(W == 1 && setBitArray[Rn] != true)
    {
        switch(U)
        {
            case 0:
                R[Rn] = R[Rn] - (setBits * 4);
            break;

            case 1:
                R[Rn] = R[Rn] + (setBits * 4);
            break;
        }
    }
    if(S == 1 && setBitArray[15] == true)
    {
        cpsr = spsr;
    }
}

void armCPU::STMIA(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint16_t regList = (opcode & 0xFFFF);
    bool P,U,W,S;
    P = ((opcode >> 24) & 0x1);
    U = ((opcode >> 23) & 0x1);
    W = ((opcode >> 21) & 0x1);
    S = ((opcode >> 22) & 0x1);



    uint8_t setBits = 0;
    bool setBitArray[16];
    for(int i = 0; i < 16; i++)
    {
        setBitArray[i] = false;
        if(((regList >> i) & 0x1) != 0)
        {
            setBits++;
            setBitArray[i] = true;
        }
    }

    uint32_t startAddress = R[Rn];
    switch((P << 1) | U)
    {
        case 0: // Decrement After
            startAddress -= (setBits * 4);
            startAddress += 4;
        break;

        case 1: // Increment After

        break;

        case 2: // Decrement Before
            startAddress -= (setBits * 4);
        break;

        case 3: // Increment Before
            startAddress += 4;
        break;
    }

    uint8_t cpsrModeCurrent = cpsr.mode;
    if(S == 1)
    {
        modeSwitch(0x10);
    }

    uint32_t endAddress = R[Rn] + (setBits * 4);
    if(P == 0)
    {
        endAddress -= 4;
    }


    for(int i = 0; i < 16; i++)
    {
        if(setBitArray[i] == true)
        {
            if(i != 15)
            {
                ram.writeMem(startAddress, 2, R[i]);
            }
            if(i == 15)
            {
                ram.writeMem(startAddress, 2, R[i]);
            }
            startAddress += 4;
        }
    }

    //uint8_t cpsrModeCurrent = cpsr.mode;
    if(S == 1)
    {
        modeSwitch(cpsrModeCurrent);
    }
    if(W == 1)
    {
        switch(U)
        {
            case 0:
                R[Rn] = R[Rn] - (setBits * 4);
            break;

            case 1:
                R[Rn] = R[Rn] + (setBits * 4);
            break;
        }
    }
}

void armCPU::DPIS_AND(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] & aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPRS_SUB(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = R[((opcode >> 8) & 0xF)];
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] << (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] << ( (shiftAmount & 0xFF) - 1 ) ) & 0x80000000 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = (R[Rm] & 0x1);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 1: // LSR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 2: // ASR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = ((int32_t)R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0x1F) == 0)
            {
                aluVal = R[Rm];
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = rotr32(R[Rm],(shiftAmount & 0x1F) );
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0x1F) - 1 ) ) & 0x1 ) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] - aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)aluVal));
            cpsr.V = (( (uint64_t)R[Rn] ^ (uint64_t)aluVal ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPRS_ADD(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = R[((opcode >> 8) & 0xF)];
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] << (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] << ( (shiftAmount & 0xFF) - 1 ) ) & 0x80000000 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = (R[Rm] & 0x1);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 1: // LSR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 2: // ASR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = ((int32_t)R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0x1F) == 0)
            {
                aluVal = R[Rm];
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = rotr32(R[Rm],(shiftAmount & 0x1F) );
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0x1F) - 1 ) ) & 0x1 ) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] + aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)aluVal));
            cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ (uint64_t)R[Rm] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPRS_ADC(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = R[((opcode >> 8) & 0xF)];
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] << (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] << ( (shiftAmount & 0xFF) - 1 ) ) & 0x80000000 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = (R[Rm] & 0x1);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 1: // LSR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 2: // ASR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = ((int32_t)R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0x1F) == 0)
            {
                aluVal = R[Rm];
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = rotr32(R[Rm],(shiftAmount & 0x1F) );
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0x1F) - 1 ) ) & 0x1 ) != 0);
            }
        break;
    }

    uint32_t result = R[Rn] + aluVal + cpsr.C;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)aluVal + (uint64_t)cpsr.C));
            cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ ( (uint64_t)R[Rm] + (uint64_t)cpsr.C ) ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
}

void armCPU::DPRS_ORR(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = R[((opcode >> 8) & 0xF)];
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] << (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] << ( (shiftAmount & 0xFF) - 1 ) ) & 0x80000000 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = (R[Rm] & 0x1);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 1: // LSR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 2: // ASR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = ((int32_t)R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0x1F) == 0)
            {
                aluVal = R[Rm];
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = rotr32(R[Rm],(shiftAmount & 0x1F) );
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0x1F) - 1 ) ) & 0x1 ) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] | aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPRS_AND(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = R[((opcode >> 8) & 0xF)];
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] << (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] << ( (shiftAmount & 0xFF) - 1 ) ) & 0x80000000 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = (R[Rm] & 0x1);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 1: // LSR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 2: // ASR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = ((int32_t)R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0x1F) == 0)
            {
                aluVal = R[Rm];
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = rotr32(R[Rm],(shiftAmount & 0x1F) );
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0x1F) - 1 ) ) & 0x1 ) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] & aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPRS_TEQ(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = R[((opcode >> 8) & 0xF)];
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] << (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] << ( (shiftAmount & 0xFF) - 1 ) ) & 0x80000000 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = (R[Rm] & 0x1);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 1: // LSR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 2: // ASR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = ((int32_t)R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0x1F) == 0)
            {
                aluVal = R[Rm];
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = rotr32(R[Rm],(shiftAmount & 0x1F) );
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0x1F) - 1 ) ) & 0x1 ) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] ^ aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    //R[Rd] = result;
}

void armCPU::DPRS_BIC(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = R[((opcode >> 8) & 0xF)];
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] << (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] << ( (shiftAmount & 0xFF) - 1 ) ) & 0x80000000 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = (R[Rm] & 0x1);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 1: // LSR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 2: // ASR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = ((int32_t)R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0x1F) == 0)
            {
                aluVal = R[Rm];
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = rotr32(R[Rm],(shiftAmount & 0x1F) );
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0x1F) - 1 ) ) & 0x1 ) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] & (~aluVal);
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPRS_MOV(uint32_t opcode)
{
    R[15] += 4;
    ////ui.pauseEmulation = true;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = R[((opcode >> 8) & 0xF)];
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    if(Rm == 0xF)
    {
        R[Rm] += 8;
    }

    switch(addrMode)
    {
        case 0: // LSL
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] << (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] << ( (shiftAmount & 0xFF) - 1 ) ) & 0x80000000 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = (R[Rm] & 0x1);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 1: // LSR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = (R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else if((shiftAmount & 0xFF) == 32)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = 0;
                carryOut = 0;
            }
        break;

        case 2: // ASR
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0xFF) < 32)
            {
                aluVal = ((int32_t)R[Rm] >> (shiftAmount & 0xFF));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0xFF) - 1 ) ) & 0x1 ) != 0);
            }
            else
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if((shiftAmount & 0xFF) == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
            else if((shiftAmount & 0x1F) == 0)
            {
                aluVal = R[Rm];
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
            else
            {
                aluVal = rotr32(R[Rm],(shiftAmount & 0x1F));
                carryOut = ( ( ( R[Rm] >> ( (shiftAmount & 0x1F) - 1 ) ) & 0x1 ) != 0);
            }
        break;
    }


    if(Rm == 0xF)
    {
        R[Rm] -= 8;
    }
    uint32_t result = aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

/*
void armCPU::DPIS_MOV(uint32_t opcode)
{
    if(ui.allowPauseEmulation == true)
    {
        ////ui.pauseEmulation = true;
    }
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            //cpsr.Z = 1;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
    if(Rd != 0xF)
    {
        R[15] += 4; // Could be an issue?
    }
    if(Rd == 0xF)
    {
        if(cpsr.T == 0)
        {
            R[15] += 8;
        }
        if(cpsr.T == 1)
        {
            R[15] += 4;
            //printf("PC: 0x%X\n",R[15]);
            ////ui.pauseEmulation = true;
            //ui.runNoStep = false;
            //ui.useRunTo = false;
        }
    }
}
*/

void armCPU::DPIS_MOV(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;

    if(Rm == 0xF)
    {
        R[Rm] += 4;
    }
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = (aluVal);
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
        }
    }
    if(Rm == 0xF)
    {
        R[Rm] -= 4;
    }
    R[Rd] = result;
}

void armCPU::DPIS_MVN(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    if(Rm == 0xF)
    {
        R[Rm] += 4;
    }
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = (~aluVal);
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
        }
    }
    if(Rm == 0xF)
    {
        R[Rm] -= 4;
    }
    R[Rd] = result;
}

void armCPU::DPIS_TST(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] & aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
}

void armCPU::DPIS_BIC(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] & (~aluVal);
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPIS_ORR(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] | aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPIS_EOR(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] ^ aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
    R[Rd] = result;
}

void armCPU::DPIS_TEQ(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] ^ aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = carryOut;
            // MISSING V IMPLEMENTATION, SEE PG. 107
        }
    }
}

void armCPU::DPIS_ADD(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] + aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)aluVal));
            cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ (uint64_t)R[Rm] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
    if(Rd == 0xF)
    {
        R[0xF] += 4;
    }
}

void armCPU::DPIS_CMN(uint32_t opcode)
{
    R[15] += 4;
    ////ui.pauseEmulation = true;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] + aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)aluVal));
            cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ (uint64_t)R[Rm] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
}

void armCPU::DPIS_SUB(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] - aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)aluVal));
            cpsr.V = (( (uint64_t)R[Rn] ^ (uint64_t)aluVal ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
    if(Rd == 0xF)
    {
        // Superstar Saga moment
        R[0xF] += 4;
    }
}

void armCPU::DPIS_RSB(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = aluVal - R[Rn];
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)aluVal - (uint64_t)R[Rn]));
            cpsr.V = (( (uint64_t)aluVal ^ (uint64_t)R[Rn] ) &
                     ( ( (uint64_t)aluVal ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
    if(Rd == 0xF)
    {
        R[0xF] += 4;
    }
}

void armCPU::DPIS_RSC(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = aluVal - R[Rn] - (!cpsr.C);
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)aluVal - (uint64_t)R[Rn] - (uint64_t)(!cpsr.C)));
            cpsr.V = ( ( (uint64_t)aluVal ^ ( (uint64_t)R[Rn] - (uint64_t)(!cpsr.C) ) ) &
                     ( ( (uint64_t)aluVal ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
}

void armCPU::DPIS_CMP(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] - aluVal;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)aluVal));
            cpsr.V = (( (uint64_t)R[Rn] ^ (uint64_t)aluVal ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
}

void armCPU::DPIS_SBC(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] - aluVal - (!cpsr.C);
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)aluVal - (uint64_t)(!cpsr.C)));
            cpsr.V = ( ( (uint64_t)R[Rn] ^ ( (uint64_t)aluVal + (uint64_t)(!cpsr.C) ) ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
}

void armCPU::DPIS_ADC(uint32_t opcode)
{
    R[15] += 4;
    uint32_t value = (opcode & 0xFF);
    uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t addrMode = ((opcode >> 5) & 0x3);
    uint32_t aluVal = 0;
    bool carryOut = 0;
    switch(addrMode)
    {
        case 0: // LSL
            aluVal = (R[Rm] << shiftAmount);
            carryOut = ( ( ( R[Rm] << ( shiftAmount - 1 ) ) & 0x80000000 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = R[Rm];
                carryOut = cpsr.C;
            }
        break;

        case 1: // LSR
            aluVal = (R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                aluVal = 0;
                carryOut = ((R[Rm] & 0x80000000) != 0);
            }
        break;

        case 2: // ASR
            aluVal = ((int32_t)R[Rm] >> shiftAmount);
            carryOut = ( ( ( R[Rm] >> ( shiftAmount - 1 ) ) & 0x1 ) != 0);
            if(shiftAmount == 0)
            {
                switch((R[Rm] & 0x80000000))
                {
                    case 0:
                        aluVal = 0;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;

                    case 0x80000000:
                        aluVal = 0xFFFFFFFF;
                        carryOut = ((R[Rm] & 0x80000000) != 0);
                    break;
                }
            }
        break;

        case 3: // RR or RRX
            if(shiftAmount == 0) // RRX
            {
                aluVal = ((cpsr.C << 31) | (R[Rm] >> 1));
                carryOut = ((R[Rm] & 0x1) != 0);
            }
            if(shiftAmount != 0) // RX
            {
                aluVal = rotr32(R[Rm],shiftAmount);
                carryOut = ((aluVal & 0x80000000) != 0);
            }
        break;
    }


    uint32_t result = R[Rn] + aluVal + cpsr.C;
    if(((opcode >> 20) & 0x1) != 0) // If bit 20 is 1
    {
        if(Rd == 0xF)
        {
            //cpsr = spsr;
            cpsr = writeCPSR(cpsr, readCPSR(spsr),true);
        }
        if(Rd != 0xF)
        {
            cpsr.N = ((result & 0x80000000) != 0);
            cpsr.Z = (result == 0);
            cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)aluVal + (uint64_t)cpsr.C));
            cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ ( (uint64_t)R[Rm] + (uint64_t)cpsr.C ) ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
        }
    }
    R[Rd] = result;
}

void armCPU::MUL(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t Rs = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 16) & 0xF);
    uint32_t result = 0;

    result = (R[Rm] * R[Rs]);

    bool S = ((opcode >> 20) & 0x1);
    if(S == 1)
    {
        cpsr.N = ((result & 0x80000000) != 0);
        cpsr.Z = (result == 0);
    }
    R[Rd] = result;
}

void armCPU::SWP(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint32_t memData = ram.readMem(R[Rn],2);
    ram.writeMem(R[Rn], 2, R[Rm]);
    R[Rd] = memData;
}

void armCPU::SWPB(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint32_t memData = ram.readMem(R[Rn],0);
    ram.writeMem(R[Rn], 0, R[Rm]);
    R[Rd] = memData;
}

void armCPU::UMULL(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t Rs = ((opcode >> 8) & 0xF);
    uint8_t RdHi = ((opcode >> 16) & 0xF);
    uint8_t RdLo = ((opcode >> 12) & 0xF);
    uint64_t result = 0;

    result = ((uint64_t)R[Rm] * (uint64_t)R[Rs]);

    uint64_t andValue = (0x1 << 63);

    bool S = ((opcode >> 20) & 0x1);
    R[RdHi] = result >> 32;
    R[RdLo] = result;
    if(S == 1)
    {
        cpsr.N = (((result >> 32) & 0x80000000) != 0);
        cpsr.Z = (result == 0);
    }
}

void armCPU::UMLAL(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t Rs = ((opcode >> 8) & 0xF);
    uint8_t RdHi = ((opcode >> 16) & 0xF);
    uint8_t RdLo = ((opcode >> 12) & 0xF);
    uint64_t result = 0;

    result = ((uint64_t)R[Rm] * (uint64_t)R[Rs]);

    uint64_t addVal = ((R[RdHi] << 32) | R[RdLo]);

    //result += addVal;

    uint64_t andValue = (0x1 << 63);

    uint64_t carryFrom = (result & 0xFFFFFFFF) + R[RdLo];
    R[RdLo] = result + R[RdLo];
    R[RdHi] = (result >> 32) + R[RdHi] + (carryFrom > 0xFFFFFFFF);
    //R[RdHi] = (result >> 32) + R[RdHi] + (0xFFFFFFFF <= ((uint64_t)R[RdLo] + (uint64_t)result));

    bool S = ((opcode >> 20) & 0x1);
    if(S == 1)
    {
        cpsr.N = ((R[RdHi] & 0x80000000) != 0); // This looks weird lol
        cpsr.Z = (R[RdHi] == 0 && R[RdLo] == 0);
    }
}

void armCPU::SMLAL(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t Rs = ((opcode >> 8) & 0xF);
    uint8_t RdHi = ((opcode >> 16) & 0xF);
    uint8_t RdLo = ((opcode >> 12) & 0xF);
    int64_t result = 0;
    int64_t signExtend, signExtend2;
    signExtend = R[Rm];
    signExtend2 = R[Rs];
    signExtend = signExtend << 32;
    signExtend = signExtend >> 32;
    signExtend2 = signExtend2 << 32;
    signExtend2 = signExtend2 >> 32;

    result = (signExtend2 * signExtend);

    uint64_t carryFrom = (result & 0xFFFFFFFF) + R[RdLo];
    R[RdLo] = result + R[RdLo];
    R[RdHi] = (result >> 32) + R[RdHi] + (carryFrom > 0xFFFFFFFF);

    uint64_t andValue = (0x1 << 63);

    bool S = ((opcode >> 20) & 0x1);
    if(S == 1)
    {
        cpsr.N = ((R[RdHi] & 0x80000000) != 0); // This looks weird lol
        cpsr.Z = (R[RdHi] == 0 && R[RdLo] == 0);
    }
    //R[RdHi] = result >> 32;
    //R[RdLo] = result;
}

void armCPU::SMULL(uint32_t opcode)
{
    R[15] += 4;
    //if(ui.allowPauseEmulation == true)
    //{
        ////ui.pauseEmulation = true;
    //}
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t Rs = ((opcode >> 8) & 0xF);
    uint8_t RdHi = ((opcode >> 16) & 0xF);
    uint8_t RdLo = ((opcode >> 12) & 0xF);
    int64_t result = 0;
    int64_t signExtend, signExtend2;
    signExtend = R[Rm];
    signExtend2 = R[Rs];
    signExtend = signExtend << 32;
    signExtend = signExtend >> 32;
    signExtend2 = signExtend2 << 32;
    signExtend2 = signExtend2 >> 32;

    result = (signExtend2 * signExtend);

    uint64_t andValue = (0x1 << 63);

    bool S = ((opcode >> 20) & 0x1);
    if(S == 1)
    {
        cpsr.N = ((result & 0x8000000000000000) != 0); // This looks weird lol
        cpsr.Z = (result == 0);
    }
    R[RdHi] = result >> 32;
    R[RdLo] = result;
}

void armCPU::MLA(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rm = ((opcode) & 0xF);
    uint8_t Rs = ((opcode >> 8) & 0xF);
    uint8_t Rd = ((opcode >> 16) & 0xF);
    uint8_t Rn = ((opcode >> 12) & 0xF);
    uint32_t result = 0;

    result = ((R[Rm] * R[Rs]) + R[Rn]);

    bool S = ((opcode >> 20) & 0x1);
    if(S == 1)
    {
        cpsr.N = ((result & 0x80000000) != 0);
        cpsr.Z = (result == 0);
    }
    R[Rd] = result;
}

void armCPU::LDST_REG(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint32_t offset = R[Rm];
    if(Rm == 0xF)
    {
        offset += 4;
    }
    uint32_t scaledReg = ((opcode >> 4) & 0xFF);
    bool U, B, L;
    U = ((opcode >> 23) & 0x1);
    B = ((opcode >> 22) & 0x1);
    L = ((opcode >> 20) & 0x1);
    uint32_t address;
    if(scaledReg != 0)
    {
        uint8_t shiftType = ((opcode >> 5) & 0x3);
        uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
        switch(shiftType)
        {
            case 0: // LSL
                offset = offset << shiftAmount;
            break;

            case 1: // LSR
                offset = offset >> shiftAmount;
                if(shiftAmount == 0)
                {
                    offset = 0;
                }
            break;

            case 2: // ASR
                if(shiftAmount == 0)
                {
                    if((offset & 0x80000000) != 0)
                    {
                        offset = 0xFFFFFFFF;
                    }
                    if((offset & 0x80000000) == 0)
                    {
                        offset = 0;
                    }
                }
                if(shiftAmount != 0)
                {
                    offset = (int32_t)offset >> shiftAmount;
                }
            break;

            case 3:
                if(shiftAmount == 0) // RRX
                {
                    offset = (cpsr.C << 31) | (offset >> 1);
                }
                if(shiftAmount != 0) // ROR
                {
                    offset = rotr32(offset,shiftAmount);
                }
            break;
        }
    }
    switch(U)
    {
        case 0:
            address = R[Rn] - offset;
            if(Rn == 0xF)
            {
                address += 4;
            }
        break;

        case 1:
            address = R[Rn] + offset;
            if(Rn == 0xF)
            {
                address += 4;
            }
        break;
    }
    switch(B << 1 | L)
    {
        case 0: // Store Word (32 bit)
            if(Rd != 15)
            {
                ram.writeMem(address,2,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,2,R[Rd] + 4);
            }
        break;

        case 1: // Load Word (32 bit)
            R[Rd] = ram.readMem(address,2); // TODO, ADD ADDRESS ROTATION
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;

        case 2: // Store Byte
            if(Rd != 15)
            {
                ram.writeMem(address,0,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,0,R[Rd] + 4);
            }
        break;

        case 3: // Load Byte
            R[Rd] = ram.readMem(address,0);
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;
    }
}

void armCPU::LDST_REG_PRE(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint32_t offset = R[Rm];
    if(Rm == 0xF)
    {
        offset += 4;
    }
    uint32_t scaledReg = ((opcode >> 4) & 0xFF);
    bool U, B, L;
    U = ((opcode >> 23) & 0x1);
    B = ((opcode >> 22) & 0x1);
    L = ((opcode >> 20) & 0x1);
    uint32_t address;
    if(scaledReg != 0)
    {
        uint8_t shiftType = ((opcode >> 5) & 0x3);
        uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
        switch(shiftType)
        {
            case 0: // LSL
                offset = offset << shiftAmount;
            break;

            case 1: // LSR
                offset = offset >> shiftAmount;
                if(shiftAmount == 0)
                {
                    offset = 0;
                }
            break;

            case 2: // ASR
                if(shiftAmount == 0)
                {
                    if((offset & 0x80000000) != 0)
                    {
                        offset = 0xFFFFFFFF;
                    }
                    if((offset & 0x80000000) == 0)
                    {
                        offset = 0;
                    }
                }
                if(shiftAmount != 0)
                {
                    offset = (int32_t)offset >> shiftAmount;
                }
            break;

            case 3:
                if(shiftAmount == 0) // RRX
                {
                    offset = (cpsr.C << 31) | (offset >> 1);
                }
                if(shiftAmount != 0) // ROR
                {
                    offset = rotr32(offset,shiftAmount);
                }
            break;
        }
    }
    switch(U)
    {
        case 0:
            address = R[Rn] - offset;
            if(Rn == 0xF)
            {
                address += 4;
            }
            R[Rn] = address;
        break;

        case 1:
            address = R[Rn] + offset;
            if(Rn == 0xF)
            {
                address += 4;
            }
            R[Rn] = address;
        break;
    }
    switch(B << 1 | L)
    {
        case 0: // Store Word (32 bit)
            if(Rd != 15)
            {
                ram.writeMem(address,2,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,2,R[Rd] + 4);
            }
        break;

        case 1: // Load Word (32 bit)
            R[Rd] = ram.readMem(address,2); // TODO, ADD ADDRESS ROTATION
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;

        case 2: // Store Byte
            if(Rd != 15)
            {
                ram.writeMem(address,0,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,0,R[Rd] + 4);
            }
        break;

        case 3: // Load Byte
            R[Rd] = ram.readMem(address,0);
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;
    }
}

void armCPU::LDST_REG_POST(uint32_t opcode)
{
    R[15] += 4;
    uint8_t Rn = ((opcode >> 16) & 0xF);
    uint8_t Rd = ((opcode >> 12) & 0xF);
    uint8_t Rm = ((opcode) & 0xF);
    uint32_t offset = R[Rm];
    if(Rm == 0xF)
    {
        offset += 4;
    }
    uint32_t scaledReg = ((opcode >> 4) & 0xFF);
    bool U, B, L;
    U = ((opcode >> 23) & 0x1);
    B = ((opcode >> 22) & 0x1);
    L = ((opcode >> 20) & 0x1);
    uint32_t address;
    if(scaledReg != 0)
    {
        uint8_t shiftType = ((opcode >> 5) & 0x3);
        uint8_t shiftAmount = ((opcode >> 7) & 0x1F);
        switch(shiftType)
        {
            case 0: // LSL
                offset = offset << shiftAmount;
            break;

            case 1: // LSR
                offset = offset >> shiftAmount;
                if(shiftAmount == 0)
                {
                    offset = 0;
                }
            break;

            case 2: // ASR
                if(shiftAmount == 0)
                {
                    if((offset & 0x80000000) != 0)
                    {
                        offset = 0xFFFFFFFF;
                    }
                    if((offset & 0x80000000) == 0)
                    {
                        offset = 0;
                    }
                }
                if(shiftAmount != 0)
                {
                    offset = (int32_t)offset >> shiftAmount;
                }
            break;

            case 3:
                if(shiftAmount == 0) // RRX
                {
                    offset = (cpsr.C << 31) | (offset >> 1);
                }
                if(shiftAmount != 0) // ROR
                {
                    offset = rotr32(offset,shiftAmount);
                }
            break;
        }
    }
    switch(U)
    {
        case 0:
            address = R[Rn];
            if(Rn == 0xF)
            {
                R[Rn] += 4;
            }
            R[Rn] -= offset;
        break;

        case 1:
            address = R[Rn];
            if(Rn == 0xF)
            {
                R[Rn] += 4;
            }
            R[Rn] += offset;
        break;
    }
    switch(B << 1 | L)
    {
        case 0: // Store Word (32 bit)
            if(Rd != 15)
            {
                ram.writeMem(address,2,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,2,R[Rd] + 4);
            }
        break;

        case 1: // Load Word (32 bit)
            R[Rd] = ram.readMem(address,2); // TODO, ADD ADDRESS ROTATION
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;

        case 2: // Store Byte
            if(Rd != 15)
            {
                ram.writeMem(address,0,R[Rd]);
            }
            if(Rd == 15)
            {
                ram.writeMem(address,0,R[Rd] + 4);
            }
        break;

        case 3: // Load Byte
            R[Rd] = ram.readMem(address,0);
            if(Rd == 0xF)
            {
                R[15] = R[15] & 0xFFFFFFFC;
            }
        break;
    }
}

void armCPU::A9_MRC(uint32_t opcode)
{
    R[15] += 4;
    // TODO
}
