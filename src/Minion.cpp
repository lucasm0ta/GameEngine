#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/Bullet.h"
#include "../include/Game.h"

#define RADIUS 200

Minion::Minion(GameObject &associated, GameObject &alienCenter,
  float arcOffsetDeg) : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg),
  randGen(randDevice()) {
    Sprite *spr =  new Sprite(associated, "./assets/img/minion.png");

    std::uniform_real_distribution<float> realDist(1, 1.5);
    float randVal = realDist(randGen);
    spr->SetScale(randVal, randVal);
    associated.box.SetSize(spr->GetWidth(), spr->GetHeight());
    associated.AddComponent(spr);
}

Minion::~Minion() {
}

void Minion::Update(float dt) {
    // std::cout<<"Updated Minion:"<<dt<<std::endl;
    Vec2 distance(RADIUS, 0);
    arc +=dt;
    distance.Rotate(arc);
    associated.box.SetCenter(alienCenter.box.Center() + distance);
    associated.angle += dt;
}

void Minion::Render() {
}

bool Minion::Is(std::string type) {
    return (type == "Minion");
}

std::string Minion::Type() {
    return "Minion";
}

void Minion::Shoot(Vec2 pos) {
    auto &state = Game::GetInstance().GetState();

    auto bulletObj = std::make_shared<GameObject>();
    float angle = Vec2::Angle(associated.box.Center(), pos);
    Bullet *bullet = new Bullet(*bulletObj, angle, 500, 30, 2080);
    bulletObj->box.SetCenter(associated.box.Center());
    bulletObj->AddComponent(bullet);
    state.AddObject(bulletObj);
    std::cout<<"SHOOT"<<std::endl;
}
