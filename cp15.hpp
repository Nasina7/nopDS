class nds9Coprocessor {
    public:

    unsigned int readCPReg(unsigned char opcode1, unsigned char CRn, unsigned char CRm, unsigned char opcode2);
    void writeCPReg(unsigned char opcode1, unsigned char CRn, unsigned char CRm, unsigned char opcode2, unsigned int value);

    private:
        unsigned int mainID;
        unsigned int cacheTypeSize;
        unsigned int TCMSize;

        unsigned int controlRegister;
};

extern nds9Coprocessor cp15;