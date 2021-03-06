#include "cpu.hpp"
#include <stdio.h>
#include "ram.hpp"

void armCPU::decodeAndRunTHUMB()
{
    //uint16_t opcode = io.readMem(cpu.R[15], 1);
    //cpu.lastOpcodeRan = io.readMem(cpu.R[15], 1);
    //printf("Opcode: 0x%X\n",opcode);
    runTHUMB(ram.readMem(R[15], 1));
}
typedef void (armCPU::*thumbLookup2)(short unsigned int);

thumbLookup2 thumbLookupTable[0x10000];

thumbLookup2 getThumbOpcode(uint16_t opcode)
{
    switch((opcode) & 0xE000)
    {
        case 0x0:
            switch((opcode >> 10) & 0x7)
            {
                case 0 ... 5: // 000-??X Shift by Immediate
                    switch((opcode >> 11) & 0x3)
                    {
                        case 0: // LSL
                            return &armCPU::T_LSL_IMD;
                        break;

                        case 1: // LSR
                            return &armCPU::T_LSR_IMD;
                        break;

                        case 2: // ASR
                            return &armCPU::T_ASR_IMD;
                        break;

                        default:
                            return &armCPU::T_INVALID;
                        break;
                    }
                break;

                case 6: // 000-110 Add Subtract Register
                    switch((opcode >> 9) & 0x1)
                    {
                        case 0: // Add
                            return &armCPU::T_ADD_REG;
                        break;

                        case 1: // Sub
                            return &armCPU::T_SUB_REG;
                        break;
                    }
                break;

                case 7: // 000-111 Add Subtract Immediate
                    switch((opcode >> 9) & 0x1)
                    {
                        case 0: // Add
                            return &armCPU::T_ADD_SIMD;
                        break;

                        case 1: // Sub
                            return &armCPU::T_SUB_SIMD;
                        break;
                    }
                break;
            }
        break;

        case 0x2000:
            switch((opcode >> 11) & 0x3)
            {
                case 0: // MOV
                    return &armCPU::T_MOV_IMD;
                break;

                case 1: // CMP
                    return &armCPU::T_CMP_IMD;
                break;

                case 2: // ADD
                    return &armCPU::T_ADD_IMD;
                break;

                case 3: // SUB
                    return &armCPU::T_SUB_IMD;
                break;
            }
        break;

        case 0x4000: // 010
            switch((opcode >> 10) & 0x7)
            {
                case 0: // 010-000  Data Processing Register
                    switch((opcode >> 6) & 0xF)
                    {
                        case 0:
                            return &armCPU::T_AND_ALU;
                        break;

                        case 1:
                            return &armCPU::T_EOR_ALU;
                        break;

                        case 2:
                            return &armCPU::T_LSL_ALU;
                        break;

                        case 3:
                            return &armCPU::T_LSR_ALU;
                        break;

                        case 4:
                            return &armCPU::T_ASR_ALU;
                        break;

                        case 5:
                            return &armCPU::T_ADC_ALU;
                        break;

                        case 6:
                            return &armCPU::T_SBC_ALU;
                        break;

                        case 7:
                            return &armCPU::T_ROR_ALU;
                        break;

                        case 8:
                            return &armCPU::T_TST_ALU;
                        break;

                        case 9:
                            return &armCPU::T_NEG_ALU;
                        break;

                        case 0xA:
                            return &armCPU::T_CMP_ALU;
                        break;

                        case 0xB:
                            return &armCPU::T_CMN_ALU;
                        break;

                        case 0xC:
                            return &armCPU::T_ORR_ALU;
                        break;

                        case 0xD:
                            return &armCPU::T_MUL_ALU;
                        break;

                        case 0xE:
                            return &armCPU::T_BIC_ALU;
                        break;

                        case 0xF:
                            return &armCPU::T_MVN_ALU;
                        break;
                    }
                break;

                case 1: // 010-001  Special Data Processing or Branch Exchange
                    switch((opcode >> 8) & 0x3)
                    {
                        case 0:
                            return &armCPU::T_SDP_ADD;
                        break;

                        case 1:
                            return &armCPU::T_SDP_CMP;
                        break;

                        case 2:
                            return &armCPU::T_SDP_MOV;
                        break;

                        case 3:
                            return &armCPU::T_BX;
                        break;

                        default:
                            return &armCPU::T_INVALID;
                        break;
                    }
                break;

                case 2 ... 3: // 010-01X  Load from Literal Pool
                    return &armCPU::T_LD_LP;
                break;

                case 4 ... 7: // 010-1XX  Load Store Register Offset
                    switch((opcode >> 9) & 0x1)
                    {
                        case 0:
                            return &armCPU::T_LDST_REG;
                        break;

                        case 1:
                            return &armCPU::T_LDSTSBH_REG;
                        break;
                    }

                break;
            }
        break;

        case 0x6000: // Lost store word/byte immediate offset
            switch((opcode >> 11) & 0x3)
            {
                case 0: // STR
                    return &armCPU::T_STR_IMD;
                break;

                case 1: // LDR
                    return &armCPU::T_LDR_IMD;
                break;

                case 2: // STRB
                    return &armCPU::T_STRB_IMD;
                break;

                case 3: // LDRB
                    return &armCPU::T_LDRB_IMD;
                break;
            }
        break;

        case 0x8000:
            switch((opcode >> 11) & 0x3)
            {
                case 0:
                    return &armCPU::T_STRH_IMD;
                break;

                case 1:
                    return &armCPU::T_LDRH_IMD;
                break;

                case 2:
                    return &armCPU::T_STR_SP;
                break;

                case 3:
                    return &armCPU::T_LDR_SP;
                break;
            }
        break;

        case 0xA000:
            switch((opcode >> 12) & 0x1)
            {
                case 0: // Add to SP or PC
                    switch((opcode >> 11) & 0x1)
                    {
                        case 0: // Add to PC and store in Rd
                            return &armCPU::T_ADD_PC;
                        break;

                        case 1: // Add to SP and store in Rd
                            return &armCPU::T_ADD_SP;
                        break;
                    }
                break;

                case 1: // Misc Instructions
                    switch((opcode >> 9) & 0x3)
                    {
                        case 0:
                            return &armCPU::T_ADJ_STACK;
                        break;

                        case 2: // Push/Pop Register List
                            switch((opcode >> 11) & 0x1)
                            {
                                case 0: // PUSH
                                    return &armCPU::T_PUSH;
                                break;

                                case 1: // POP
                                    return &armCPU::T_POP;
                                break;
                            }
                        break;

                        case 3:
                            return &armCPU::T_INVALID;
                        break;

                        default:
                            return &armCPU::T_INVALID;
                        break;
                    }
                break;
            }
        break;

        case 0xC000: // 110
            switch((opcode >> 8) & 0x1F)
            {
                case 0x0 ... 0xF: // 110-0XXXX Load Store Multiple
                    switch((opcode >> 11) & 0x1)
                    {
                        case 0: // STMIA
                            return &armCPU::T_STMIA;
                        break;

                        case 1: // LDMIA
                            return &armCPU::T_LDMIA;
                        break;
                    }
                break;

                case 0x10 ... 0x1D: // Conditional Branch
                    switch((opcode >> 8) & 0xF)
                    {
                        case 0:
                            return &armCPU::T_B_EQ;
                        break;

                        case 1:
                            return &armCPU::T_B_NE;
                        break;

                        case 2:
                            return &armCPU::T_B_CS;
                        break;

                        case 3:
                            return &armCPU::T_B_CC;
                        break;

                        case 4:
                            return &armCPU::T_B_MI;
                        break;

                        case 5:
                            return &armCPU::T_B_PL;
                        break;

                        case 6:
                            return &armCPU::T_B_VS;
                        break;

                        case 7:
                            return &armCPU::T_B_VC;
                        break;

                        case 8:
                            return &armCPU::T_B_HI;
                        break;

                        case 9:
                            return &armCPU::T_B_LS;
                        break;

                        case 0xA:
                            return &armCPU::T_B_GE;
                        break;

                        case 0xB:
                            return &armCPU::T_B_LT;
                        break;

                        case 0xC:
                            return &armCPU::T_B_GT;
                        break;

                        case 0xD:
                            return &armCPU::T_B_LE;
                        break;

                        default:
                            return &armCPU::T_INVALID;
                        break;
                    }
                break;

                case 0x1E: // Undefined Instruction
                    return &armCPU::T_INVALID;
                break;

                case 0x1F: // Software Interrupt
                    return &armCPU::T_SWI;
                break;
            }
        break;

        case 0xE000:
            switch((opcode >> 11) & 3)
            {
                case 0: // Unconditional Branch
                    return &armCPU::T_B;
                break;

                case 1: // BLX Suffix or Undefined Instruction
                    return &armCPU::T_INVALID;
                break;

                case 2: // BL Prefix
                    return &armCPU::T_BL;
                break;

                case 3: // BL Suffix
                    return &armCPU::T_INVALID;
                break;
            }
        break;

        default:
            return &armCPU::T_INVALID;
        break;
    }
}

void armCPU::generateThumbLookup()
{
    for(uint32_t i = 0; i < 0x10000; i++)
    {
        thumbLookupTable[i] = getThumbOpcode(i);
    }
    //(cpu.*thumbLookupTable[0x5E32])(0x5E32);
}

void armCPU::runTHUMB(uint16_t opcode)
{
    ((*this).*thumbLookupTable[opcode])(opcode);
    //(cpu->(*thumbLookupTable[opcode]))(opcode);
    return;
    /*
    switch((opcode) & 0xE000)
    {
        case 0x0:
            switch((opcode >> 10) & 0x7)
            {
                case 0 ... 5: // 000-??X Shift by Immediate
                    switch((opcode >> 11) & 0x3)
                    {
                        case 0: // LSL
                            cpu.T_LSL_IMD(opcode);
                        break;

                        case 1: // LSR
                            cpu.T_LSR_IMD(opcode);
                        break;

                        case 2: // ASR
                            cpu.T_ASR_IMD(opcode);
                        break;

                        default:
                            printf("BAD_ERROR: Impossible Code Path!\n");
                            //ui.pauseEmulation = true;
                        break;
                    }
                break;

                case 6: // 000-110 Add Subtract Register
                    switch((opcode >> 9) & 0x1)
                    {
                        case 0: // Add
                            cpu.T_ADD_REG(opcode);
                        break;

                        case 1: // Sub
                            cpu.T_SUB_REG(opcode);
                        break;
                    }
                break;

                case 7: // 000-111 Add Subtract Immediate
                    switch((opcode >> 9) & 0x1)
                    {
                        case 0: // Add
                            cpu.T_ADD_SIMD(opcode);
                        break;

                        case 1: // Sub
                            cpu.T_SUB_SIMD(opcode);
                        break;
                    }
                break;
            }
        break;

        case 0x2000:
            switch((opcode >> 11) & 0x3)
            {
                case 0: // MOV
                    cpu.T_MOV_IMD(opcode);
                break;

                case 1: // CMP
                    cpu.T_CMP_IMD(opcode);
                break;

                case 2: // ADD
                    cpu.T_ADD_IMD(opcode);
                break;

                case 3: // SUB
                    cpu.T_SUB_IMD(opcode);
                break;
            }
        break;

        case 0x4000: // 010
            switch((opcode >> 10) & 0x7)
            {
                case 0: // 010-000  Data Processing Register
                    switch((opcode >> 6) & 0xF)
                    {
                        case 0:
                            cpu.T_AND_ALU(opcode);
                        break;

                        case 1:
                            cpu.T_EOR_ALU(opcode);
                        break;

                        case 2:
                            cpu.T_LSL_ALU(opcode);
                        break;

                        case 3:
                            cpu.T_LSR_ALU(opcode);
                        break;

                        case 4:
                            cpu.T_ASR_ALU(opcode);
                        break;

                        case 5:
                            cpu.T_ADC_ALU(opcode);
                        break;

                        case 6:
                            cpu.T_SBC_ALU(opcode);
                        break;

                        case 7:
                            cpu.T_ROR_ALU(opcode);
                        break;

                        case 8:
                            cpu.T_TST_ALU(opcode);
                        break;

                        case 9:
                            cpu.T_NEG_ALU(opcode);
                        break;

                        case 0xA:
                            cpu.T_CMP_ALU(opcode);
                        break;

                        case 0xB:
                            cpu.T_CMN_ALU(opcode);
                        break;

                        case 0xC:
                            cpu.T_ORR_ALU(opcode);
                        break;

                        case 0xD:
                            cpu.T_MUL_ALU(opcode);
                        break;

                        case 0xE:
                            cpu.T_BIC_ALU(opcode);
                        break;

                        case 0xF:
                            cpu.T_MVN_ALU(opcode);
                        break;
                    }
                break;

                case 1: // 010-001  Special Data Processing or Branch Exchange
                    switch((opcode >> 8) & 0x3)
                    {
                        case 0:
                            T_SDP_ADD(opcode);
                        break;

                        case 1:
                            T_SDP_CMP(opcode);
                        break;

                        case 2:
                            T_SDP_MOV(opcode);
                        break;

                        case 3:
                            T_BX(opcode);
                        break;

                        default:
                            printf("BAD_ERROR: IMPOSSIBLE CODE PATH!\n");
                            //ui.pauseEmulation = true;
                        break;
                    }
                break;

                case 2 ... 3: // 010-01X  Load from Literal Pool
                    T_LD_LP(opcode);
                break;

                case 4 ... 7: // 010-1XX  Load Store Register Offset
                    switch((opcode >> 9) & 0x1)
                    {
                        case 0:
                            T_LDST_REG(opcode);
                        break;

                        case 1:
                            T_LDSTSBH_REG(opcode);
                        break;
                    }

                break;
            }
        break;

        case 0x6000: // Lost store word/byte immediate offset
            switch((opcode >> 11) & 0x3)
            {
                case 0: // STR
                    T_STR_IMD(opcode);
                break;

                case 1: // LDR
                    T_LDR_IMD(opcode);
                break;

                case 2: // STRB
                    T_STRB_IMD(opcode);
                break;

                case 3: // LDRB
                    T_LDRB_IMD(opcode);
                break;
            }
        break;

        case 0x8000:
            switch((opcode >> 11) & 0x3)
            {
                case 0:
                    cpu.T_STRH_IMD(opcode);
                break;

                case 1:
                    cpu.T_LDRH_IMD(opcode);
                break;

                case 2:
                    cpu.T_STR_SP(opcode);
                break;

                case 3:
                    cpu.T_LDR_SP(opcode);
                break;
            }
        break;

        case 0xA000:
            switch((opcode >> 12) & 0x1)
            {
                case 0: // Add to SP or PC
                    switch((opcode >> 11) & 0x1)
                    {
                        case 0: // Add to PC and store in Rd
                            cpu.T_ADD_PC(opcode);
                        break;

                        case 1: // Add to SP and store in Rd
                            cpu.T_ADD_SP(opcode);
                        break;
                    }
                break;

                case 1: // Misc Instructions
                    switch((opcode >> 9) & 0x3)
                    {
                        case 0:
                            T_ADJ_STACK(opcode);
                        break;

                        case 2: // Push/Pop Register List
                            switch((opcode >> 11) & 0x1)
                            {
                                case 0: // PUSH
                                    T_PUSH(opcode);
                                break;

                                case 1: // POP
                                    T_POP(opcode);
                                break;
                            }
                        break;

                        case 3:
                            printf("THUMB: Unimplemented 101 Software Interrupt!\n");
                            // Does this even exist on the GBA?  Need to check later.
                            //ui.pauseEmulation = true;
                        break;

                        default:
                            printf("BAD_ERROR: Invalid Instruction!\n");
                            //ui.pauseEmulation = true;
                        break;
                    }
                break;
            }
        break;

        case 0xC000: // 110
            switch((opcode >> 8) & 0x1F)
            {
                case 0x0 ... 0xF: // 110-0XXXX Load Store Multiple
                    switch((opcode >> 11) & 0x1)
                    {
                        case 0: // STMIA
                            T_STMIA(opcode);
                        break;

                        case 1: // LDMIA
                            T_LDMIA(opcode);
                        break;
                    }
                break;

                case 0x10 ... 0x1D: // Conditional Branch
                    switch((opcode >> 8) & 0xF)
                    {
                        case 0:
                            cpu.T_B_EQ(opcode);
                        break;

                        case 1:
                            cpu.T_B_NE(opcode);
                        break;

                        case 2:
                            cpu.T_B_CS(opcode);
                        break;

                        case 3:
                            cpu.T_B_CC(opcode);
                        break;

                        case 4:
                            cpu.T_B_MI(opcode);
                        break;

                        case 5:
                            cpu.T_B_PL(opcode);
                        break;

                        case 6:
                            cpu.T_B_VS(opcode);
                        break;

                        case 7:
                            cpu.T_B_VC(opcode);
                        break;

                        case 8:
                            cpu.T_B_HI(opcode);
                        break;

                        case 9:
                            cpu.T_B_LS(opcode);
                        break;

                        case 0xA:
                            cpu.T_B_GE(opcode);
                        break;

                        case 0xB:
                            cpu.T_B_LT(opcode);
                        break;

                        case 0xC:
                            cpu.T_B_GT(opcode);
                        break;

                        case 0xD:
                            cpu.T_B_LE(opcode);
                        break;

                        default:
                            printf("BAD_ERROR: Impossible Code Path!\n");
                            //ui.pauseEmulation = true;
                        break;
                    }
                break;

                case 0x1E: // Undefined Instruction
                    printf("THUMB ERROR: Invalid opcode 0x%X!\n",opcode);
                    //ui.pauseEmulation = true;
                break;

                case 0x1F: // Software Interrupt
                    cpu.T_SWI(opcode);
                break;
            }
        break;

        case 0xE000:
            switch((opcode >> 11) & 3)
            {
                case 0: // Unconditional Branch
                    cpu.T_B(opcode);
                break;

                case 1: // BLX Suffix or Undefined Instruction
                    printf("THUMB: THIS SHOULD NOT HAPPEN! 0x%X\n",opcode);
                    //ui.pauseEmulation = true;
                break;

                case 2: // BL Prefix
                    cpu.T_BL(opcode);
                break;

                case 3: // BL Suffix
                    printf("THUMB: THIS SHOULD NOT HAPPEN! 0x%X\n",opcode);
                    //ui.pauseEmulation = true;
                break;
            }
        break;

        default:
            printf("Unimplemented opcode 0x%X\n",opcode);
            //ui.pauseEmulation = true;
        break;
    }
    */
}

// BEGINNING OF THUMB OPCODES
void armCPU::T_STMIA(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rn = ((opcode >> 8) & 0x7);
    uint8_t regList = (opcode & 0xFF);
    uint32_t startAddress = R[Rn];
    uint8_t setBits = 0;
    bool setBitArray[8];
    for(int i = 0; i < 8; i++)
    {
        setBitArray[i] = false;
        if(((regList >> i) & 0x1) != 0)
        {
            setBits++;
            setBitArray[i] = true;
        }
    }
    for(int i = 0; i < 8; i++)
    {
        if(setBitArray[i] == true)
        {
            if(i == Rn)
            {
                if(R[Rn] != startAddress) // Thumb.gba test 230
                {
                    ram.writeMem(startAddress, 2, R[i] + (setBits * 4));
                    startAddress += 4;
                }
                else // Thumb.gba test 232
                {
                    ram.writeMem(startAddress, 2, R[i]);
                    startAddress += 4;
                }
            }
            else
            {
                ram.writeMem(startAddress, 2, R[i]);
                startAddress += 4;
            }

        }
    }
    if(setBits == 0) // Thumb.gba test 229
    {
        ram.writeMem(startAddress, 2, R[15] + 4);
        setBits = 0x10;
    }
    R[Rn] = R[Rn] + (setBits * 4);
}

void armCPU::T_LDMIA(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rn = ((opcode >> 8) & 0x7);
    uint8_t regList = (opcode & 0xFF);
    uint32_t startAddress = R[Rn];
    uint8_t setBits = 0;
    bool setBitArray[8];
    for(int i = 0; i < 8; i++)
    {
        setBitArray[i] = false;
        if(((regList >> i) & 0x1) != 0)
        {
            setBits++;
            setBitArray[i] = true;
        }
    }
    for(int i = 0; i < 8; i++)
    {
        if(setBitArray[i] == true)
        {
            R[i] = ram.readMem(startAddress, 2); // Is this correct?
            startAddress += 4;
        }
    }
    if(setBits == 0) // Thumb.gba test 227
    {
        R[15] = ram.readMem(startAddress, 2);
        setBits = 0x10;
    }
    R[Rn] = R[Rn] + (setBits * 4);
}

void armCPU::T_LD_LP(uint16_t opcode)
{
    R[15] += 2;
    R[15] += 2;
    uint32_t location = R[15] & 0xFFFFFFFC;
    location += ((opcode & 0x00FF) * 4);
    uint8_t Rd = ((opcode >> 8) & 0x7);
    R[15] -= 2;
    R[Rd] = ram.readMem(location, 2);
}

void armCPU::T_LSL_IMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint8_t shiftVal = ((opcode >> 6) & 0x1F);

    if(shiftVal == 0)
    {
        R[Rd] = R[Rm];
    }
    if(shiftVal != 0)
    {
        cpsr.C = ( ( ( R[Rm] >> (32 - shiftVal) ) & 0x1 ) != 0); // != 0 might be unneeded
        R[Rd] = (R[Rm] << shiftVal);
    }
    cpsr.N = ((R[Rd] & 0x80000000) != 0);
    cpsr.Z = (R[Rd] == 0);
}

void armCPU::T_LSR_IMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint8_t shiftVal = ((opcode >> 6) & 0x1F);

    if(shiftVal == 0)
    {
        cpsr.C = ((R[Rm] & 0x80000000) != 0);
        R[Rd] = 0;
    }
    if(shiftVal != 0)
    {
        cpsr.C = ( ( ( R[Rm] >> (shiftVal - 1) ) & 0x1 ) != 0); // != 0 might be unneeded
        R[Rd] = (R[Rm] >> shiftVal);
    }
    cpsr.N = ((R[Rd] & 0x80000000) != 0);
    cpsr.Z = (R[Rd] == 0);
}

void armCPU::T_ASR_IMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint8_t shiftVal = ((opcode >> 6) & 0x1F);

    if(shiftVal == 0)
    {
        cpsr.C = ((R[Rd] & 0x80000000) != 0);
        if(cpsr.C == 0)
        {
            R[Rd] = 0;
        }
        if(cpsr.C == 1)
        {
            R[Rd] = 0xFFFFFFFF;
        }
    }
    if(shiftVal != 0)
    {
        cpsr.C = ( ( ( R[Rd] >> (shiftVal - 1) ) & 0x1 ) != 0); // != 0 might be unneeded
        R[Rd] = ((int32_t)R[Rm] >> shiftVal);
    }
    cpsr.N = ((R[Rd] & 0x80000000) != 0);
    cpsr.Z = (R[Rd] == 0);
}

void armCPU::T_B_EQ(uint16_t opcode)
{
    if(cpsr.Z == 1)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 4;
    }
    if(cpsr.Z == 0)
    {
        R[15] += 2;
    }
}
void armCPU::T_B(uint16_t opcode)
{
    int32_t jumpVal = (opcode & 0x7FF);
    jumpVal = jumpVal << 1;
    jumpVal = jumpVal << 20;
    jumpVal = jumpVal >> 20;
    R[15] += jumpVal;
    R[15] += 4;

}
void armCPU::T_B_NE(uint16_t opcode)
{
    if(cpsr.Z == 0)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 4;
    }
    if(cpsr.Z == 1)
    {
        R[15] += 2;
    }
}
void armCPU::T_B_CS(uint16_t opcode)
{
    if(cpsr.C == 1)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 4;
    }
    if(cpsr.C == 0)
    {
        R[15] += 2;
    }
}
void armCPU::T_B_CC(uint16_t opcode)
{
    if(cpsr.C == 0)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 4;
    }
    if(cpsr.C == 1)
    {
        R[15] += 2;
    }
}
void armCPU::T_B_MI(uint16_t opcode)
{
    if(cpsr.N == 1)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 4;
    }
    if(cpsr.N == 0)
    {
        R[15] += 2;
    }
}
void armCPU::T_B_PL(uint16_t opcode)
{
    if(cpsr.N == 0)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 4;
    }
    if(cpsr.N == 1)
    {
        R[15] += 2;
    }
}
void armCPU::T_B_VS(uint16_t opcode)
{
    if(cpsr.V == 1)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 4;
    }
    if(cpsr.V == 0)
    {
        R[15] += 2;
    }
}
void armCPU::T_B_VC(uint16_t opcode)
{
    if(cpsr.V == 0)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 4;
    }
    if(cpsr.V == 1)
    {
        R[15] += 2;
    }
}
void armCPU::T_B_HI(uint16_t opcode)
{
    if(cpsr.C == 1 && cpsr.Z == 0)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 2;
    }
    R[15] += 2;
}
void armCPU::T_B_LS(uint16_t opcode)
{
    if(cpsr.C == 0 || cpsr.Z == 1)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 2;
    }
    R[15] += 2;
}
void armCPU::T_B_GE(uint16_t opcode)
{
    if(cpsr.N == cpsr.V)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 2;
    }
    R[15] += 2;
}
void armCPU::T_B_LT(uint16_t opcode)
{
    if(cpsr.N != cpsr.V)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 2;
    }
    R[15] += 2;
}
void armCPU::T_B_GT(uint16_t opcode)
{
    if(cpsr.N == cpsr.V && cpsr.Z == 0)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 2;
    }
    R[15] += 2;
}
void armCPU::T_B_LE(uint16_t opcode)
{
    if(cpsr.N != cpsr.V || cpsr.Z == 1)
    {
        int8_t jumpVal = (opcode & 0xFF);
        R[15] += (jumpVal);
        R[15] += (jumpVal);
        R[15] += 2;
    }
    R[15] += 2;
}

void armCPU::T_CMP_IMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rn = ((opcode >> 8) & 0x7);
    uint8_t imdVal = (opcode & 0xFF);

    uint32_t result = R[Rn] - imdVal;


    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = ((uint64_t)0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)imdVal));
    cpsr.V = (( (uint64_t)R[Rn] ^ (uint64_t)imdVal ) &
                     ( ( (uint64_t)R[Rn] ^ result ) ) &
                     0x80000000 ) != 0;
}
void armCPU::T_SUB_IMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode >> 8) & 0x7);
    uint8_t imdVal = (opcode & 0xFF);

    uint32_t result = R[Rd] - imdVal;


    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = ((uint64_t)0xFFFFFFFF >= ((uint64_t)R[Rd] - (uint64_t)imdVal));
    cpsr.V = (( (uint64_t)R[Rd] ^ (uint64_t)imdVal ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
    R[Rd] = result;
    // MISSING V IMPLEMENTATION, SEE PG. 339
}
void armCPU::T_ADD_IMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode >> 8) & 0x7);
    uint8_t imdVal = (opcode & 0xFF);

    uint32_t result = R[Rd] + imdVal;


    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = ((uint64_t)0xFFFFFFFF < ((uint64_t)R[Rd] + (uint64_t)imdVal));

    cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ (uint64_t)imdVal ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;

    R[Rd] = result;
    // MISSING V IMPLEMENTATION, SEE PG. 339
}

void armCPU::T_ADD_PC(uint16_t opcode)
{
    //ui.pauseEmulation = true;
    R[15] += 2;
    R[15] += 2;
    uint8_t Rd = ((opcode >> 8) & 0x7);
    uint8_t imdVal = (opcode & 0xFF);
    //printf("ImdVal: 0x%X\n", imdVal);
    //printf("The pC: 0x%X\n", R[15]);

    R[Rd] = ((R[15] & 0xFFFFFFFC) + (imdVal << 2));
    R[15] -= 2;
}
void armCPU::T_ADD_SP(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode >> 8) & 0x7);
    uint8_t imdVal = (opcode & 0xFF);

    R[Rd] = R[13] + (imdVal << 2);
}
void armCPU::T_ADD_SIMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t imdVal = ((opcode >> 6) & 0x7);


    uint32_t result = R[Rn] + imdVal;


    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)imdVal));
    cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ (uint64_t)imdVal ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
    R[Rd] = result;
    // MISSING V IMPLEMENTATION, SEE PG. 309
}
void armCPU::T_SUB_SIMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t imdVal = ((opcode >> 6) & 0x7);


    uint32_t result = R[Rn] - imdVal;


    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)imdVal));
    cpsr.V = (( (uint64_t)R[Rd] ^ (uint64_t)imdVal ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
    R[Rd] = result;
    // MISSING V IMPLEMENTATION, SEE PG. 309
}
void armCPU::T_ADD_REG(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t Rm = ((opcode >> 6) & 0x7);

    uint32_t result = R[Rn] + R[Rm];


    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rn] + (uint64_t)R[Rm]));
    cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ (uint64_t)R[Rm] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;

    R[Rd] = result;
    // MISSING V IMPLEMENTATION, SEE PG. 339
}
void armCPU::T_SUB_REG(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t Rm = ((opcode >> 6) & 0x7);

    uint32_t result = R[Rn] - R[Rm];


    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rn] - (uint64_t)R[Rm]));
    cpsr.V = (( (uint64_t)R[Rd] ^ (uint64_t)R[Rm] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
    R[Rd] = result;
    // MISSING V IMPLEMENTATION, SEE PG. 339
}
void armCPU::T_MOV_IMD(uint16_t opcode)
{
    R[15] += 2;
    uint8_t Rd = ((opcode >> 8) & 0x7);
    uint8_t imdVal = (opcode & 0xFF);

    uint32_t result = imdVal;


    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    R[Rd] = result;
    // MISSING V IMPLEMENTATION, SEE PG. 339
}

void armCPU::T_BL(uint16_t opcode)
{
    R[14] = (R[15] + 4) | cpsr.T;
    uint32_t fullOpcode = (ram.readMem(R[15],1) << 16) | ram.readMem(R[15] + 2,1);
    int32_t offset = opcode & 0x7FF;
    offset = offset << 12;
    offset = offset << 9; // Sign Extend
    offset = offset >> 9;
    R[15] += offset;
    uint32_t offset2 = fullOpcode & 0x7FF;
    R[15] += offset2;
    R[15] += offset2;
    R[15] += 4;
}

void armCPU::T_BX(uint16_t opcode)
{
    // Does this cause error?
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint8_t highReg = ((opcode >> 6) & 0x1);
    Rm = Rm + (highReg * 8);
    //printf("Loaded Location: 0x%X\n", R[Rm]);
    cpsr.T = (R[Rm] & 0x1);
    //printf("Chosen Thumb Mode: 0x%X\n", cpsr.T);
    R[15] = (R[Rm] & 0xFFFFFFFE);
    //printf("Jumped To 0x%X\n", R[15]);
    if(Rm == 15)
    {
        if(cpsr.T == 1)
        {
            R[15] += 2;
        }
        else
        {
            R[15] += 4;
        }
    }
}

void armCPU::T_AND_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = R[Rd] & R[Rm];

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_BIC_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = R[Rd] & (~R[Rm]);

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_MVN_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = (~R[Rm]);

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_ORR_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = R[Rd] | R[Rm];

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_MUL_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = R[Rd] * R[Rm];

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_TST_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = R[Rd] & R[Rm];

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    //R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_EOR_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = R[Rd] ^ R[Rm];

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}


void armCPU::T_LSL_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = 0;

    if((R[Rm] & 0xFF) == 0)
    {
        result = R[Rd];
    }
    if((R[Rm] & 0xFF) < 32 && (R[Rm] & 0xFF) != 0)
    {
        cpsr.C =  ( ( ( R[Rd] >> ( 32 - ( R[Rm] & 0xFF ) ) ) & 0x1 ) != 0); // != 0 Might be unneeded
        result = R[Rd] << (R[Rm] & 0xFF);
    }
    if((R[Rm] & 0xFF) == 32)
    {
        cpsr.C = (R[Rd] & 0x1);
        result = 0;
    }
    if((R[Rm] & 0xFF) > 32)
    {
        cpsr.C = 0;
        result = 0;
    }

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_LSR_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result = 0;

    if((R[Rm] & 0xFF) == 0)
    {
        result = R[Rd];
    }
    if((R[Rm] & 0xFF) < 32 && (R[Rm] & 0xFF) != 0)
    {
        cpsr.C =  ( ( ( R[Rd] >> ( R[Rm] - 1) ) & 0x1 ) != 0); // != 0 Might be unneeded
        result = R[Rd] >> (R[Rm] & 0xFF);
    }
    if((R[Rm] & 0xFF) == 32)
    {
        cpsr.C = ((R[Rd] & 0x80000000) != 0);
        result = 0;
    }
    if((R[Rm] & 0xFF) > 32)
    {
        cpsr.C = 0;
        result = 0;
    }

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_ASR_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result;

    if((R[Rm] & 0xFF) == 0)
    {
        result = R[Rd];
    }
    if((R[Rm] & 0xFF) < 32 && (R[Rm] & 0xFF) != 0)
    {
        cpsr.C =  ( ( ( R[Rd] >> ( R[Rm] - 1) ) & 0x1 ) != 0); // != 0 Might be unneeded
        result = (int32_t)R[Rd] >> (R[Rm] & 0xFF);
    }
    if((R[Rm] & 0xFF) >= 32)
    {
        cpsr.C = ((R[Rd] & 0x80000000) != 0);
        if((R[Rd] & 0x80000000) != 0)
        {
            result = 0xFFFFFFFF;
        }
        if((R[Rd] & 0x80000000) == 0)
        {
            result = 0;
        }
    }

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);

    R[Rd] = result;
    R[15] += 2;
}


void armCPU::T_ADC_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result;

    result = R[Rd] + R[Rm] + cpsr.C;

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = (0xFFFFFFFF < ((uint64_t)R[Rd] + (uint64_t)R[Rm] + (uint64_t)cpsr.C));
    cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ ( (uint64_t)R[Rm] + (uint64_t)cpsr.C ) ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_SBC_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result;

    result = R[Rd] - R[Rm] - (!cpsr.C);

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = (0xFFFFFFFF >= ((uint64_t)R[Rd] - (uint64_t)R[Rm] - (uint64_t)(!cpsr.C)));
    cpsr.V = ( ( (uint64_t)R[Rd] ^ ( (uint64_t)R[Rm] + (uint64_t)(!cpsr.C) ) ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_CMP_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result;

    result = R[Rd] - R[Rm];

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = ((uint64_t)0xFFFFFFFF >= ((uint64_t)R[Rd] - (uint64_t)R[Rm]));
    cpsr.V = (( (uint64_t)R[Rd] ^ (uint64_t)R[Rm] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;

    //R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_CMN_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result;

    result = R[Rd] + R[Rm];

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = ((uint64_t)0xFFFFFFFF < ((uint64_t)R[Rd] + (uint64_t)R[Rm]));
    cpsr.V = ( ~ ( (uint64_t)R[Rd] ^ (uint64_t)R[Rm] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;

    //R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_NEG_ALU(uint16_t opcode)
{
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint32_t result;

    result = 0 - R[Rm];

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = (0xFFFFFFFF >= ((uint64_t)0 - (uint64_t)R[Rm]));
    // MISSING V FLAG IMPLEMENTATION SEE PG. 377

    R[Rd] = result;
    R[15] += 2;
}

void armCPU::T_ROR_ALU(uint16_t opcode)
{
    //ui.pauseEmulation = true;
    uint8_t Rd = (opcode & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    //printf("RD: 0x%X\n", Rd);
    //printf("RM: 0x%X\n", Rm);
    //printf("RDval: 0x%X\n", R[Rd]);
    //printf("RMval: 0x%X\n", R[Rm]);
    uint32_t result;

    if((R[Rm] & 0xFF) == 0)
    {
        result = R[Rd];
        //printf("PATH 1 CHOSEN\n");
    }
    //if((R[Rm] & 0xF) == 0 && (R[Rm] & 0xFF) != 0)
    //{
    //    cpsr.C = ( ( R[Rd] & 0x80000000 ) != 0);
    //    result = R[Rd];
    //}
    else
    {
        //printf("PATH 2 CHOSEN\n");
        cpsr.C = (((R[Rd] >> ((R[Rm] & 0x1F) - 1) ) & 0x1) != 0);
        result = rotr32(R[Rd],(R[Rm] & 0x1F));
    }

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    //cpsr.N = 1;

    R[Rd] = result;
    //printf("RESULT: 0x%X\n", result);
    R[15] += 2;
}


void armCPU::T_LDR_IMD(uint16_t opcode)
{
    //ui.pauseEmulation =true;
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t imdVal = ((opcode >> 6) & 0x1F);

    uint32_t address = R[Rn] + (imdVal * 4);
    //address = address & 0xFFFFFFFC;
    R[Rd] = ram.readMem(address,2);
    R[15] += 2;
}
void armCPU::T_LDST_REG(uint16_t opcode)
{
    uint8_t Ro = ((opcode >> 6) & 0x7);
    uint8_t Rb = ((opcode >> 3) & 0x7);
    uint8_t Rd = ((opcode) & 0x7);
    bool L,B;
    L = ((opcode >> 11) & 0x1);
    B = ((opcode >> 10) & 0x1);

    uint32_t address = R[Rb] + R[Ro];
    switch((L << 1) | B)
    {
        case 0: // Store Word
            ram.writeMem(address, 2, R[Rd]);
        break;

        case 1: // Store Byte
            ram.writeMem(address, 0, R[Rd]);
        break;

        case 2: // Load Word
            R[Rd] = ram.readMem(address,2);
        break;

        case 3: // Load Byte
            R[Rd] = ram.readMem(address,0);
        break;
    }
    R[15] += 2;
}

void armCPU::T_LDSTSBH_REG(uint16_t opcode)
{
    uint8_t Ro = ((opcode >> 6) & 0x7);
    uint8_t Rb = ((opcode >> 3) & 0x7);
    uint8_t Rd = ((opcode) & 0x7);
    bool H,S;
    H = ((opcode >> 11) & 0x1);
    S = ((opcode >> 10) & 0x1);

    uint32_t address = R[Rb] + R[Ro];
    if((address & 0x1) == 1 && ((S << 1) | H) == 3) // thumb.gba edge case from test 212?
    {
        H = false;
    }
    switch((S << 1) | H)
    {
        case 0:
            ram.writeMem(address, 1, R[Rd]);
        break;

        case 1:
            R[Rd] = ram.readMem(address,1);
            //ram.writeMem(address, 0, R[Rd]);
        break;

        case 2:
            {
                int32_t signExtend = ram.readMem(address,0);
                signExtend = signExtend << 24;
                signExtend = signExtend >> 24;
                R[Rd] = signExtend;
            }
        break;

        case 3:
            {
                int32_t signExtend = ram.readMem(address,1);
                signExtend = signExtend << 16;
                signExtend = signExtend >> 16;
                R[Rd] = signExtend;
            }
        break;
    }
    R[15] += 2;
}

void armCPU::T_LDR_SP(uint16_t opcode)
{
    uint8_t Rd = ((opcode >> 8) & 0x7);
    uint8_t imdVal = ((opcode) & 0xFF);

    uint32_t address = R[13] + (imdVal * 4);
    R[Rd] = ram.readMem(address,2);
    R[15] += 2;
}

void armCPU::T_LDRH_IMD(uint16_t opcode)
{
    register uint8_t Rn = ((opcode >> 3) & 0x7);
    register uint8_t Rd = ((opcode) & 0x7);
    register uint8_t imdVal = ((opcode >> 6) & 0x1F);
//printf("0x%X\n", R[Rn] + (imdVal << 1));
    //uint32_t address = R[Rn] + (imdVal * 2);
    R[Rd] = ram.readMem(R[Rn] + (imdVal << 1),1);
    R[15] += 2;
}
void armCPU::T_LDRB_IMD(uint16_t opcode)
{
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t imdVal = ((opcode >> 6) & 0x1F);
    //printf("imdVAL: 0x%X\n", imdVal);

    uint32_t address = R[Rn] + (imdVal);
    R[Rd] = ram.readMem(address,0);
    R[15] += 2;
}
void armCPU::T_STR_IMD(uint16_t opcode)
{
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t imdVal = ((opcode >> 6) & 0x1F);

    uint32_t address = R[Rn] + (imdVal * 4);
    ram.writeMem(address,2,R[Rd]);
    R[15] += 2;
}

void armCPU::T_STR_SP(uint16_t opcode)
{
    uint8_t Rd = ((opcode >> 8) & 0x7);
    uint8_t imdVal = ((opcode) & 0xFF);

    uint32_t address = R[13] + (imdVal * 4);
    ram.writeMem(address,2,R[Rd]);
    if(Rd == 15)
    {
        ram.writeMem(address,2,R[Rd] - 8);
    }
    R[15] += 2;
}

void armCPU::T_STRH_IMD(uint16_t opcode)
{
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t imdVal = ((opcode >> 6) & 0x1F);

    uint32_t address = R[Rn] + (imdVal * 2);
    ram.writeMem(address,1,R[Rd]);
    R[15] += 2;
}
void armCPU::T_STRB_IMD(uint16_t opcode)
{
    uint8_t Rn = ((opcode >> 3) & 0x7);
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t imdVal = ((opcode >> 6) & 0x1F);

    uint32_t address = R[Rn] + (imdVal);
    ram.writeMem(address,0,R[Rd]);
    R[15] += 2;
}

void armCPU::T_PUSH(uint16_t opcode)
{
    uint16_t regList = (opcode & 0x1FF);

    uint8_t setBits = 0;
    bool setBitArray[9];
    for(int i = 0; i < 9; i++)
    {
        setBitArray[i] = false;
        if(((regList >> i) & 0x1) != 0)
        {
            setBits++;
            setBitArray[i] = true;
        }
    }
    uint32_t startAddress = (R[13] - 4 *(setBits));
    //uint32_t endAddress = R[13] - 4;


    for(int i = 0; i < 9; i++)
    {
        if(setBitArray[i] == true && i != 8)
        {
            ram.writeMem(startAddress, 2, R[i]);
            startAddress += 4;
        }
        if(setBitArray[i] == true && i == 8)
        {
            ram.writeMem(startAddress, 2, R[14]);
            startAddress += 4;
        }
    }
    R[13] = R[13] - 4*(setBits);
    R[15] += 2;
}

void armCPU::T_POP(uint16_t opcode)
{
    uint16_t regList = (opcode & 0x1FF);

    uint8_t setBits = 0;
    bool setBitArray[9];
    for(int i = 0; i < 9; i++)
    {
        setBitArray[i] = false;
        if(((regList >> i) & 0x1) != 0)
        {
            setBits++;
            setBitArray[i] = true;
        }
    }
    uint32_t startAddress = R[13];
    uint32_t endAddress = R[13] + 4 * (setBits);

    for(int i = 0; i < 9; i++)
    {
        if(setBitArray[i] == true && i != 8)
        {
            R[i] = ram.readMem(startAddress, 2);
            startAddress += 4;
        }
        if(setBitArray[i] == true && i == 8)
        {
            R[15] = ram.readMem(startAddress, 2);
            startAddress += 4;
        }
    }
    R[13] = endAddress;
    if(setBitArray[8] == false)
    {
        R[15] += 2;
    }
}

void armCPU::T_SDP_ADD(uint16_t opcode)
{
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint8_t H2 = ((opcode >> 6) & 0x1);
    uint8_t H1 = ((opcode >> 7) & 0x1);
    Rd = Rd + (H1 * 8);
    Rm = Rm + (H2 * 8);
    R[Rd] = R[Rd] + R[Rm];
    if(Rm == 0xF)
    {
        R[Rd] += 4;
    }
    if(Rd == 0xF)
    {
        R[Rd] += 4;
    }
    if(Rd != 0xF)
    {
        R[15] += 2;
    }
}

void armCPU::T_SDP_CMP(uint16_t opcode)
{
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint8_t H2 = ((opcode >> 6) & 0x1);
    uint8_t H1 = ((opcode >> 7) & 0x1);
    Rd = Rd + (H1 * 8);
    Rm = Rm + (H2 * 8);
    uint32_t result = R[Rd] - R[Rm];
    if(Rm == 0xF)
    {
        result -= 4;
    }
    if(Rd == 0xF)
    {
        result += 4;
    }

    cpsr.N = ((result & 0x80000000) != 0);
    cpsr.Z = (result == 0);
    cpsr.C = ((uint64_t)0xFFFFFFFF >= ((uint64_t)R[Rd] - (uint64_t)R[Rm]));
    cpsr.V = (( (uint64_t)R[Rd] ^ (uint64_t)R[Rm] ) &
                     ( ( (uint64_t)R[Rd] ^ result ) ) &
                     0x80000000 ) != 0;
    R[15] += 2;
}

void armCPU::T_SDP_MOV(uint16_t opcode)
{
    //printf("PC: 0x%X\n", R[15]);
    R[15] += 2;
    uint8_t Rd = ((opcode) & 0x7);
    uint8_t Rm = ((opcode >> 3) & 0x7);
    uint8_t H2 = ((opcode >> 6) & 0x1);
    uint8_t H1 = ((opcode >> 7) & 0x1);
    Rd = Rd + (H1 * 8);
    Rm = Rm + (H2 * 8);
    R[Rd] = R[Rm];
    if(Rm == 0xF)
    {
        R[Rd] += 2;
    }
}

void armCPU::T_ADJ_STACK(uint16_t opcode)
{
    bool S = ((opcode >> 7) & 0x1);
    uint16_t offset = (opcode & 0x7F);
    offset = offset << 2;
    switch(S)
    {
        case 0:
            R[13] += offset;
        break;

        case 1:
            R[13] -= offset;
        break;
    }
    R[15] += 2;
}

void armCPU::T_SWI(uint16_t opcode)
{
    R1314_svc[1] = (R[15] + 2);
    //printf("Return Address: 0x%X\n", (R[15] + 2));
    //printf("R14: 0x%X\n", R[14]);
    spsr_svc = cpsr;
    //printf("R14: 0x%X\n", R[14]);
    modeSwitch(0x13);
    //printf("R14: 0x%X\n", R[14]);
    cpsr.T = false;
    cpsr.I = true;
    R[15] = 0x8;
    //printf("R14: 0x%X\n", R[14]);
    //cpsr.mode = 0x13;

    //if((opcode & 0xFF) == 0xC)
    //{
    //    return;
    //}
    //printf("RUNNING SOFTWARE INTERRUPT 0x%X\n",(opcode & 0xFF));
    //ui.pauseEmulation = true;
}

void armCPU::T_INVALID(uint16_t opcode)
{
    printf("Unknown Thumb Opcode 0x%X\n", opcode);
    //ui.pauseEmulation = true;
    //printf("RUNNING SOFTWARE INTERRUPT 0x%X\n",(opcode & 0xFF));
    //ui.pauseEmulation = true;
}
