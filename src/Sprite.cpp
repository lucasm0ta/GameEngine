#include "../include/Sprite.h"
#include "../include/Game.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Sprite::Sprite(GameObject &associated) : Component(associated), texture(nullptr){
}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture == nullptr) {
        SDL_DestroyTexture(texture);
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
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

void Sprite::Render() {
    SDL_Rect dstRect;

    dstRect.x = associated.box.x;
    dstRect.y = associated.box.y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;
    if (texture == nullptr) {
        std::cerr << "Error Sprite: Trying to render null texture." <<std::endl;
    }
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h;
    clipRect.w = w;
}

void Sprite::Update(float) {
}
