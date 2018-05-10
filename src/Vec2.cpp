#include "../include/Vec2.h"

#include <cmath>

Vec2::Vec2 (float _x, float _y) {
    x = _x;
    y = _y;
}
void Vec2::Rotate(float rad) {
    float _x = std::cos(rad)*x - std::sin(rad)*y;
    float _y = std::sin(rad)*x + std::cos(rad)*y;
    x = _x;
    y = _y;
}

float Vec2::Mag() const {
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

void Vec2::SetMag(float newMag) {
    float mag = Mag();
    x = newMag*x/mag;
    y = newMag*y/mag;
}

float Vec2::EuclidianDist(const Vec2 &a, const Vec2 &b) {
    return std::sqrt(std::pow(a.x-b.x, 2) + std::pow(a.y-b.y, 2));
}

float Vec2::ManhattamDist(const Vec2 &a, const Vec2 &b) {
    return std::abs(a.x-b.x) + std::abs(a.y-b.y);
}

float Vec2::Angle(const Vec2 &a, const Vec2 &b) {
    return std::atan2(b.y-a.y, b.x - a.x);
}

float Vec2::GetX() const {
    return x;
}

float Vec2::GetY() const {
    return y;
}

void Vec2::Set(float _x, float _y) {
    x = _x;
    y = _y;
}

Vec2 Vec2::operator+(const Vec2 &a) const {
    return Vec2(a.x + x, a.y + y);
}

Vec2 Vec2::operator+(const Vec2 &&a) const {
    return Vec2(a.x + x, a.y + y);
}

Vec2 Vec2::operator-(const Vec2 &a) const {
    return Vec2(x - a.x, y - a.y);
}

Vec2 Vec2::operator-(const Vec2 &&a) const {
    return Vec2(x - a.x, y - a. y);
}

Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}

Vec2& Vec2::operator+=(const Vec2 &a) {
    x += a.x;
    y += a.y;
    return *this;
}

Vec2& Vec2::operator+=(const Vec2 &&a) {
    x += a.x;
    y += a.y;
    return *this;
}

Vec2  Vec2::operator*(float f) const {
    return Vec2(x*f, y*f);
}

std::ostream& operator<<(std::ostream& os, const Vec2& a) {
    os << '(' << a.x << ',' << a.y << ')';
    return os;
}
