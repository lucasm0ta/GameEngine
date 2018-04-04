#include "../include/Vec2.h"

#include <cmath>

Vec2::Vec2 (float _x, float _y) {
    x = _x;
    y = _y;
}
Vec2& Vec2::GetRotated(float rad) {
    x = std::cos(rad)*x - std::sin(rad)*y;
    y = std::sin(rad)*x + std::cos(rad)*y;
    return *this;
}

float Vec2::Mag() const {
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

float Vec2::EuclidianDist(const Vec2 &a, const Vec2 &b) {
    return std::sqrt(std::pow(a.x-b.x, 2) + std::pow(a.y-b.y, 2));
}

float  Vec2::ManhattamDist(const Vec2 &a, const Vec2 &b) {
    return std::abs(a.x-b.x) + std::abs(a.y-b.y);
}

Vec2 Vec2::operator+(const Vec2 &a) const {
    return Vec2(a.x + x, a.y + y);
}

Vec2 Vec2::operator+(const Vec2 &&a) const {
    return Vec2(a.x + x, a.y + y);
}


Vec2 Vec2::operator-(const Vec2 &a) const {
    return Vec2(a.x - x, a.y - y);
}