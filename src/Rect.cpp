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

float CenterDist(const Rect &a, const Rect &b) {
    auto vec = a.Center()-b.Center();
    return vec.Mag();
}
