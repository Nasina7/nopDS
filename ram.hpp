class ramMap {
    public:
        unsigned int readMem(unsigned int address, unsigned int mode);
        void writeMem(unsigned int address, unsigned int mode, unsigned int value);

        unsigned int readMem7(unsigned int address, unsigned int mode);
        unsigned int readMem9(unsigned int address, unsigned int mode);

        void writeMem7(unsigned int address, unsigned int value, unsigned int mode);
        void writeMem9(unsigned int address, unsigned int value, unsigned int mode);

        unsigned int arm9IORead(unsigned int address, unsigned int mode);
        void arm9IOWrite(unsigned int address, unsigned int value, unsigned int mode);

        unsigned int wRamMode7;
        unsigned int wRamMode9;

        unsigned int wRamModeLookup7[4] = 
        {
            0x10000,
            0x4000,
            0x4000,
            0x8000
        };

        unsigned int ramMask[3] = 
        {
            0xFF,
            0xFFFF,
            0xFFFFFFFF
        };


        bool cpuIsArm9;



        // I/O

        // ARM9 Specific
        uint16_t dispStat;
        uint32_t POWCNT1;

        uint32_t ENG_A_DISPCNT;
        uint8_t WRAMCNT;
        uint8_t VRAMCNT;
        uint16_t KEYINPUT;

        // ARM7 Specific

        // Both



        unsigned char arm7bios[0x4000];
        unsigned char arm9bios[0x8000];

    private:
        unsigned char mRAM[0x400000];
        unsigned char wRAM[0x18000];
        unsigned char tcmCache[0xF000];
        unsigned char vRAM[0xA4000];
        unsigned char oamPAL[0x1000];
        unsigned char dRAM[0x3E000];
        // Matrix Stack? (GBATEK doesn't specify size)
        unsigned char wiRAM[0x2000];
        unsigned char firmFLASH[0x40000];

        unsigned char dataTCM[0x4000];
        unsigned char instTSM[0x8000];
        


        

        
};

extern ramMap ram;