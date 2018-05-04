#ifndef VEC2_H
#define VEC2_H

#include <iostream>

class Vec2 {
public:
    Vec2 (float x, float y);
    Vec2& GetRotated(float rad);
    float Mag() const;
    static float EuclidianDist(const Vec2 &a, const Vec2 &b);
    static float ManhattamDist(const Vec2 &a, const Vec2 &b);

    float GetX() const;
    float GetY() const;

    Vec2 operator+(const Vec2 &a) const;
    Vec2 operator+(const Vec2 &&a) const;
    Vec2 operator-(const Vec2 &a) const;
    Vec2 operator-(const Vec2 &&a) const;
    Vec2 operator-() const;

    Vec2& operator=(const Vec2 &a) = default;
    Vec2& operator+=(const Vec2 &a);
    Vec2& operator+=(const Vec2 &&a);
    friend std::ostream& operator<<(std::ostream& os, const Vec2& a);

private:
    float x;
    float y;
};

#endif /* VEC2_H */
