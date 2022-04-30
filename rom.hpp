#include <string>

class romFile {
    public:
        bool loadROM(std::string filename);

    private:
        
        uint8_t* romPointer;
};

