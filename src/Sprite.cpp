#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Sprite::Sprite(GameObject &associated) : Component(associated), texture(nullptr), scale(1, 1) {

}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() {
}

int Sprite::GetWidth() {
    // std::cerr << "Factor X:"<< scale.GetX()<< std::endl;
    return width*scale.GetX();
}

int Sprite::GetHeight() {
    // std::cerr << "Factor Y:"<< scale.GetY()<< std::endl;
    return height*scale.GetY();
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
    Vec2 camPos = Camera::pos;
    // std::cout <<'('<< associated.box.GetX() + camPos.GetX()<<','<<associated.box.GetY() + camPos.GetY()<<')'<<std::endl;
    dstRect.x = associated.box.GetX() + camPos.GetX();
    dstRect.y = associated.box.GetY() + camPos.GetY();
    dstRect.w = clipRect.w*scale.GetX();
    dstRect.h = clipRect.h*scale.GetY();

    // std::cout<<"Render at ("<<dstRect.x<<','<<dstRect.y<<')'<<std::endl;
    if (texture == nullptr) {
        std::cerr << "Error Sprite: Trying to render null texture." <<std::endl;
    }

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angle*180/PI, nullptr, SDL_FLIP_NONE);
}

void Sprite::Render(float x, float y) {
    SDL_Rect dstRect;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w*scale.GetX();
    dstRect.h = clipRect.h*scale.GetY();
    if (texture == nullptr) {
        std::cerr << "Error Sprite: Trying to render null texture." <<std::endl;
    }
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angle*180/PI, nullptr, SDL_FLIP_NONE);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h;
    clipRect.w = w;
}

void Sprite::SetClip(Rect rec) {
    clipRect.x = rec.GetX();
    clipRect.y = rec.GetY();
    clipRect.h = rec.GetH();
    clipRect.w = rec.GetW();
}

void Sprite::SetScale (float scaleX, float scaleY) {
    if (scaleX != 0 && scaleY != 0) {
        scale.Set(scaleX, scaleY);
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::Update(float) {
}
