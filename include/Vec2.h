#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
    Vec2 (float x, float y);
    Vec2& GetRotated(float rad);
    float Mag() const;
    static float EuclidianDist(const Vec2 &a, const Vec2 &b);
    static float ManhattamDist(const Vec2 &a, const Vec2 &b);

    Vec2 operator+(const Vec2 &a) const;
    Vec2 operator+(const Vec2 &&a) const;
    Vec2 operator-(const Vec2 &a) const;

    Vec2& operator=(const Vec2 &a) = default;
    //Vec2& operator=(const Vec2& a);

    float x;
    float y;
};

#endif /* VEC2_H */
