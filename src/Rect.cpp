#include "../include/Rect.h"
#include <cstdlib>

Rect::Rect (float _x, float _y, float _w, float _h) {
    x = _x;
    y = _y;
    w = _x;
    h = _h;
 }

bool Rect::Contains(float _x, float _y) const {
    return (_x >= x && _x <= x+w && _y >= y && _y <= y+h);
}

Vec2 Rect::Center() const {
    return Vec2(x+w/2, y + h/2);
}

void Rect::Shift(float dx, float dy) {
    x += dx;
    y += dy;
}

void Rect::Shift(Vec2 v) {
    x += v.GetX();
    y += v.GetY();
}

void Rect::SetOrigin(float _x, float _y)  {
    x = _x;
    y = _y;
}

void Rect::SetOrigin(Vec2 vec)  {
    x = vec.GetX();
    y = vec.GetY();
}

float Rect::GetX() const {
    return x;
}

float Rect::GetY() const {
    return y;
}

float CenterDist(const Rect &a, const Rect &b) {
    auto vec = a.Center()-b.Center();
    return vec.Mag();
}
