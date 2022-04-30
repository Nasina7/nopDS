#include "display.hpp"
#include "ram.hpp"
#include <iostream>

ndsDisplay display;

using namespace std;

void ndsDisplay::initDisplay()
{
    win = SDL_CreateWindow("nopDS :>", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 192*2, SDL_WINDOW_RESIZABLE);
    sdlRend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    sdlTex = SDL_CreateTexture(sdlRend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 256,192*2);
}

void ndsDisplay::setWindowTitle(std::string title)
{
    SDL_SetWindowTitle(win, title.c_str());
}

int ndsDisplay::hackBitmapRender()
{
    SDL_RenderClear(sdlRend);
    uint32_t location = 0x06800000;
    for(int y = 0; y < 192; y++)
    {
        for(int x = 0; x < 256; x++)
        {
            uint32_t color = ram.readMem(location, 1);

            pixArray[y][x] = 0xFF << 24 | 
                             (((color) & 0x1F) << 3) << 16 | 
                             (((color >> 5) & 0x1F) << 3) << 8 |
                             (((color >> 10) & 0x1F) << 3);
            //SDL_SetRenderDrawColor(sdlRend, (((color) & 0x1F) << 3), (((color >> 5) & 0x1F) << 3), (((color >> 10) & 0x1F) << 3), 255);
            //SDL_RenderDrawPoint(sdlRend, x, y);
            location += 2;
        }
    }
    SDL_UpdateTexture(sdlTex, NULL, pixArray, 256 * 4);
    SDL_RenderCopy(sdlRend, sdlTex, NULL, NULL);
    SDL_RenderPresent(sdlRend);
    return 0;
}



void ndsDisplay::engineAVramDisplay()
{
    
    uint32_t location = 0x06800000;
    for(int y = 0; y < 192; y++)
    {
        for(int x = 0; x < 256; x++)
        {
            uint32_t color = ram.readMem(location, 1);

            pixArray[y][x] = 0xFF << 24 | 
                             (((color) & 0x1F) << 3) << 16 | 
                             (((color >> 5) & 0x1F) << 3) << 8 |
                             (((color >> 10) & 0x1F) << 3);
            //SDL_SetRenderDrawColor(sdlRend, (((color) & 0x1F) << 3), (((color >> 5) & 0x1F) << 3), (((color >> 10) & 0x1F) << 3), 255);
            //SDL_RenderDrawPoint(sdlRend, x, y);
            location += 2;
        }
    }
    return;
}

void ndsDisplay::mainDisplayFunc()
{
    uint8_t dispMode = (ram.ENG_A_DISPCNT >> 16) & 0x3;

    SDL_RenderClear(sdlRend);   
    switch(dispMode)
    {
        case 0:
            //cout<<"Display Off not Implemented!"<<endl;
        break;

        case 1:
            //cout<<"Graphics Display not Implemented!"<<endl;
        break;

        case 2:
            engineAVramDisplay();
        break;

        case 3:
            //cout<<"Main Memory Display not Implemented!"<<endl;
        break;  
    }
    SDL_UpdateTexture(sdlTex, NULL, pixArray, 256 * 4);
    SDL_RenderCopy(sdlRend, sdlTex, NULL, NULL);
    SDL_RenderPresent(sdlRend);
}