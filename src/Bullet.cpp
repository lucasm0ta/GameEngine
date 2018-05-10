#include "../include/Bullet.h"
#include "../include/Sprite.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage,
    float maxDistance) : Component(associated),
    speed(speed, 0), distanceLeft(maxDistance), damage(damage) {

    this->speed.Rotate(angle);
    Sprite *spr =  new Sprite(associated, "./assets/img/minionbullet2.png", 3, 100);
    associated.box.SetSize(spr->GetWidth(), spr->GetHeight());
    associated.AddComponent(spr);
    associated.angle = angle;
}

Bullet::~Bullet() {
}

void Bullet::Update(float dt) {
    Vec2 pos = speed*dt;
    float mag = pos.Mag();
    if (mag <= distanceLeft) {
        associated.box.Shift(pos);
        distanceLeft -= mag;
    } else {
        associated.RequestDelete();
    }
}

void Bullet::Render() {
}

bool Bullet::Is(std::string type) {
    return (type == "Bullet");
}

std::string Bullet::Type() {
    return "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}
