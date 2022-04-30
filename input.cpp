#include "input.hpp"
#include "ram.hpp"
#include <iostream>
#include "cpu.hpp"
using namespace std;
/*
#include "io.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "ui.hpp"

gbaInput input;

*/

ndsInput input;
int ndsInput::handleControlsr()
{
    switch( e.key.keysym.sym )
        {

        case SDLK_p:
            cout<<"ARM9 PC: "<<hex<<arm9.R[15]<<endl;
            cout<<"ARM7 PC: "<<hex<<arm7.R[15]<<endl;
        break;

        case SDLK_z:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 1);
        break;

        case SDLK_x:
            ram.KEYINPUT = ram.KEYINPUT | (0x1);
        break;

        case SDLK_SPACE:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 2);
        break;

        case SDLK_RETURN:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 3);
        break;

        case SDLK_UP:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 6);
        break;

        case SDLK_DOWN:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 7);
        break;

        case SDLK_LEFT:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 5);
        break;

        case SDLK_RIGHT:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 4);
        break;

        case SDLK_a:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 9);
        break;

        case SDLK_s:
            ram.KEYINPUT = ram.KEYINPUT | (0x1 << 8);
        break;

        }
    return 0;
}
int ndsInput::handleControls()
{
    switch( e.key.keysym.sym )
        {

        case SDLK_z:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 1));
        break;

        case SDLK_x:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1));
        break;

        case SDLK_SPACE:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 2));
        break;

        case SDLK_RETURN:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 3));
        break;

        case SDLK_UP:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 6));
        break;

        case SDLK_DOWN:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 7));
        break;

        case SDLK_LEFT:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 5));
        break;

        case SDLK_RIGHT:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 4));
        break;

        case SDLK_a:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 9));
        break;

        case SDLK_s:
            ram.KEYINPUT = ram.KEYINPUT & (~(0x1 << 8));
        break;

        }
    return 0;
}

int ndsInput::handleInput()
{
    while( SDL_PollEvent( &e)) // While Event to handle Random Stuff
    {
        //ImGui_ImplSDL2_ProcessEvent(&e);
        if (e.type == SDL_KEYDOWN) // If a key is being pressed, handle controls.
        {   // Handle Controls
            handleControls();
        }
        if (e.type == SDL_KEYUP)
        {
            handleControlsr();
        }
        if(e.type == SDL_QUIT)
        {
            return 1;
        }
    }
    return 0;
}
