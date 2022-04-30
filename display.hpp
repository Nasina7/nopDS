#include <SDL2/SDL.h>
#include <string>
class ndsDisplay {
    public:
    SDL_Window* win;
    SDL_Renderer* sdlRend;
    SDL_Texture* sdlTex;
    SDL_Event e;
    uint32_t pixArray[192*2][256];

    void initDisplay();

    void setWindowTitle(std::string title);

    void mainDisplayFunc();

    void engineAVramDisplay();

    int hackBitmapRender();

    int pollSDL2()
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                return 1;
            }
            else if(e.type == SDL_KEYUP)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_p:
                        return 2;
                    break;
                }
            }
        }
    }
};

extern ndsDisplay display;