#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Sprite::Sprite(GameObject &associated) : Component(associated), texture(nullptr){
}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() {
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

std::string Sprite::Type() {
    return "Sprite";
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
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
    Vec2 pos = Camera::pos;
    dstRect.x = associated.box.GetX() + pos.GetX();
    dstRect.y = associated.box.GetY() + pos.GetY();
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    // std::cout<<"Render at ("<<dstRect.x<<','<<dstRect.y<<')'<<std::endl;
    if (texture == nullptr) {
        std::cerr << "Error Sprite: Trying to render null texture." <<std::endl;
    }
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

void Sprite::Render(float x, float y) {
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

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h;
    clipRect.w = w;
}

void Sprite::Update(float) {
}
