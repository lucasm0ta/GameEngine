#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Sprite::Sprite(GameObject &associated, int frameCount, float frameTime, float secondsToSelfDestruct) :
    Component(associated), texture(nullptr), scale(1, 1), frameCount(frameCount),
    frameTime(frameTime), secondsToSelfDestruct(secondsToSelfDestruct) {
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCount, float frameTime,
    float secondsToSelfDestruct) : Sprite(associated, frameCount, frameTime, secondsToSelfDestruct) {
    Open(file);
}

Sprite::~Sprite() {
}

int Sprite::GetWidth() {
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
    width = w / frameCount;
    SetClip(0, 0, width, height);
}

void Sprite::Render() {
    Vec2 camPos = Camera::pos;
    // std::cout <<'('<< associated.box.GetX() + camPos.GetX()<<','<<associated.box.GetY() + camPos.GetY()<<')'<<std::endl;
    Render(associated.box.GetX() + camPos.GetX(), associated.box.GetY() + camPos.GetY());

}

void Sprite::Render(float x, float y) {
    SDL_Rect dstRect;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w * scale.GetX();
    dstRect.h = clipRect.h * scale.GetY();
    if (texture == nullptr) {
        std::cerr << "Error Sprite: Trying to render null texture." <<std::endl;
    }
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angle*180/PI,
        nullptr, SDL_FLIP_NONE);
#ifdef DEBUG
	SDL_Point points[5];

	Vec2 point = (associated.box.Origin() - associated.box.Center()).GetRotated( associated.angle )
					+ associated.box.Center() + Camera::pos;
	points[0] = {(int)point.GetX(), (int)point.GetY()};
	points[4] = {(int)point.GetX(), (int)point.GetY()};

	point = (Vec2(associated.box.GetX() + associated.box.GetW(), associated.box.GetY()) - associated.box.Center()).GetRotated( associated.angle)
					+ associated.box.Center() + Camera::pos;
	points[1] = {(int)point.GetX(), (int)point.GetY()};

	point = (Vec2(associated.box.GetX() + associated.box.GetW(), associated.box.GetY() + associated.box.GetH()) - associated.box.Center()).GetRotated( associated.angle)
					+ associated.box.Center() + Camera::pos;
	points[2] = {(int)point.GetX(), (int)point.GetY()};

	point = (Vec2(associated.box.GetX(), associated.box.GetY() + associated.box.GetH()) - associated.box.Center()).GetRotated( associated.angle)
					+ associated.box.Center() + Camera::pos;
	points[3] = {(int)point.GetX(), (int)point.GetY()};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), ((secondsToSelfDestruct == 0)?255:0), 0, ((secondsToSelfDestruct == 0)?0:255), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
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

void Sprite::Update(float dt) {
    timer.Update(dt);
    if (secondsToSelfDestruct != 0) {
        // std::cout<<"RECT:"<<associated.box.GetX()<<" "<<associated.box.GetY()<<" "<<associated.box.GetW()<<" "<<associated.box.GetH()<<std::endl;
        // std::cout<<"TIME:"<<timer.Get()<<std::endl;
        if (timer.Get() > secondsToSelfDestruct) {
            associated.RequestDelete();
        } else {
            long frame = static_cast<long>(std::floor(timer.Get()*1000/frameTime));
            // if (frameCount == 3) std::cout<<"Elapsed:"<<timeElapsed<<" dt:"<<dt<<" Frame:"<<frame<<std::endl;
            clipRect.x = (frame%frameCount)*width;
        }
    } else {
        long frame = static_cast<long>(std::floor(timer.Get()*1000/frameTime));
        // if (frameCount == 3) std::cout<<"Elapsed:"<<timeElapsed<<" dt:"<<dt<<" Frame:"<<frame<<std::endl;
        clipRect.x = (frame%frameCount)*width;
    }
}
