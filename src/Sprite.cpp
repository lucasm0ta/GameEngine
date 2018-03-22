#include "../include/Sprite.h"
#include "../include/Game.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Sprite::Sprite() : texture(nullptr){
}

Sprite::Sprite(std::string file) : texture(nullptr) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture == nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    const char *dir = file.c_str();
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), dir);
    if (texture == nullptr) { // error
        std::cerr << "Error Sprite SDL: " << SDL_GetError() << std::endl;
        return;
    }
    int w, h;
    if (SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) != 0) { // error
        SDL_DestroyTexture(texture);
        std::cerr << "Error Sprite SDL: " << SDL_GetError() << std::endl;
        return;
    }
    height = h;
    width = w;
    SetClip(0, 0, w, h);

}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h;
    clipRect.w = w;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;
    if (texture == nullptr) {
        std::cerr << "Error Sprite: Trying to render null texture." <<std::endl;
    }
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}
