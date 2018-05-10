#include "../include/Alien.h"
#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include <iostream>

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), nMinions(nMinions), speed(0, 0), hp(100) {
    Sprite *spr =  new Sprite(associated, "./assets/img/alien.png");
    associated.box.SetSize(spr->GetWidth(), spr->GetHeight());
    associated.AddComponent(spr);
}
Alien::~Alien() {
    minionArray.clear();
}

Alien::Action::Action(Alien::Action::ActionType actionType, Vec2 pos) : type(actionType), pos(pos){
}

void Alien::Update(float dt) {
    // std::cout<<"Update GO:"<<pos<<std::endl;
    associated.angle -= dt;
    InputManager &inp = InputManager::GetInstance();
    Vec2 clickPos(inp.GetMouseX(), inp.GetMouseY());
    if (inp.MousePress(LEFT_MOUSE_BUTTON)) { // SHOOT
        Action act = Alien::Action(Action::ActionType::SHOOT, clickPos - Camera::pos);
        taskQueue.push(act);
        // speed = act.pos - ;
    }
    if (inp.MousePress(RIGHT_MOUSE_BUTTON)) { // MOVE
        taskQueue.push(Action(Action::ActionType::MOVE, clickPos - Camera::pos));
    }

    if (!taskQueue.empty()) {
        auto task = taskQueue.front();
        Vec2 point = task.pos;
        // std::cout<<"Point:"<< point <<" = "<<task.pos<<'-'<<Camera::pos<<std::endl;
        float distance = Vec2::EuclidianDist(point, associated.box.Center());
        Vec2 dir = point - associated.box.Center();
        dir.SetMag(SPEED);
        switch(task.type){
            case(Action::ActionType::MOVE):
                // std::cout<<"Distance :"<< distance <<std::endl;
                if (distance < 1.09 * SPEED) {
                    // std::cout<<"Parou"<<std::endl;
                    associated.box.SetCenter(point);
                    taskQueue.pop();
                } else {
                    // associated.box
                    // std::cout<<"POS CENTER:"<< associated.box.Center() <<std::endl;
                    associated.box.Shift(dir);
                }
            break;
            case (Action::ActionType::SHOOT):
                std::shared_ptr<GameObject> closest = minionArray[0].lock();
                float distance = std::numeric_limits<float>::max();
                for (auto auxminion : minionArray) {
                    auto minion = auxminion.lock();
                    if (minion != nullptr) {
                        float auxDist = Vec2::ManhattamDist(point, minion->box.Center());
                        if (auxDist < distance) {
                            closest = minion;
                            distance = auxDist;
                        }
                    }
                }
                Component *minion = closest->GetComponent("Minion");
                if (minion != nullptr) {
                    Minion *casted = dynamic_cast<Minion*>(minion);
                    casted->Shoot(point);
                }
                taskQueue.pop();
            break;
        }
    }
}

void Alien::Start() {
    if (nMinions > 0) {
        float radInterval = 2*PI/nMinions;
        auto &state = Game::GetInstance().GetState();
        for (int i = 0; i < nMinions; i++) {
            auto minionObj = std::make_shared<GameObject>();
            Minion *minion = new Minion(*minionObj, associated, i * radInterval);
            minionObj->AddComponent(minion);
            minionArray.push_back(minionObj);
            state.AddObject(minionObj);
        }
    }
    //std::cout<<"Render GO addr:"<<&associated<<std::endl;
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
    return type == "Alien";
}

std::string Alien::Type() {
    return "Alien";
}
