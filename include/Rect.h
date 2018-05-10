#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    Rect () = default;
    Rect (float x, float y, float w, float h);
    bool Contains(float x, float y) const;
    Vec2 Center() const;
    Vec2 Origin() const;
    static float CenterDist(const Rect &a, const Rect &b);

    void Shift(float dx, float dy);
    void Shift(Vec2 vec);

    void SetOrigin(Vec2 vec);
    void SetOrigin(float x, float y);
    void SetCenter(Vec2 vec);
    void SetCenter(float x, float y);

    void SetSize(float w, float h);
    void SetClip(float x, float y, float w, float h);
    float GetX() const;
    float GetY() const;
    float GetW() const;
    float GetH() const;

private:
    float x;
    float y;
    float w;
    float h;
};

#endif /* RECT_H */
