#include "../include/Alien.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include <iostream>

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed(0, 0), hp(100) {
    Sprite *spr =  new Sprite(associated, "./assets/img/penguinface.png");
    associated.AddComponent(spr);
}
Alien::~Alien() {
    minionArray.clear();
}

Alien::Action::Action(Alien::Action::ActionType actionType, float x, float y) : type(actionType), pos(x, y){
}

void Alien::Update(float) {
    // std::cout<<"Update GO:"<<pos<<std::endl;
    //
    InputManager &inp = InputManager::GetInstance();
    float mouseX, mouseY;
    mouseX = inp.GetMouseX();
    mouseY = inp.GetMouseY();
    if (inp.MousePress(LEFT_MOUSE_BUTTON)) { // SHOOT
        Action act = Alien::Action(Action::ActionType::SHOOT, mouseX, mouseY);
        taskQueue.push(act);
        // speed = act.pos - ;
    }
    if (inp.MousePress(RIGHT_MOUSE_BUTTON)) { // MOVE
        taskQueue.push(Action(Action::ActionType::MOVE, mouseX, mouseY));
    }

    if (!taskQueue.empty()) {
        auto task = taskQueue.front();
        switch(task.type){
            case(Action::ActionType::MOVE):
                if (Vec2::EuclidianDist(task.pos, associated.box.Center()) > task.pos.Mag()) {
                    Vec2 dir = task.pos - associated.box.Center();

                } else {
                    // associated.box
                }
            break;
            case (Action::ActionType::SHOOT):
                taskQueue.pop();
            break;
        }
    }
}

// int Alien::GetDamage() {
//     if (damage >= hitpoints) {
//         //std::cout<<"Damage GO addr:"<<&associated<<std::endl;
//         associated.RequestDelete();
//         auto sound = reinterpret_cast<Sound*>(associated.GetComponent("Sound"));
//         if (sound != nullptr) {
//             // std::cerr << "Play Death" << std::endl;
//             sound->Play();
//         }
//     } else {
//         hitpoints -= damage;
//     }
// }

void Alien::Start() {
    //std::cout<<"Render GO addr:"<<&associated<<std::endl;
}

void Alien::Render() {
    //std::cout<<"Render GO addr:"<<&associated<<std::endl;
}

bool Alien::Is(std::string type) {
    return type == "Alien";
}
