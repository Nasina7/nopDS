#include <SDL2/SDL.h>


class ndsInput {
    public:
        int handleInput();
    private:
        SDL_Event e;
        int handleControls();
        int handleControlsr();
};

extern ndsInput input;
