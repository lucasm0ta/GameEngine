#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    Rect () = default; 
    Rect (float x, float y, float w, float h);
    bool Contains(float x, float y) const;
    Vec2 Center() const;
    static float CenterDist(const Rect &a, const Rect &b);
    float x;
    float y;
    float w;
    float h;
};

#endif /* RECT_H */
