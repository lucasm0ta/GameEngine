#include "../include/Face.h"
#include "../include/Sound.h"
#include <memory>
#include <iostream>

Face::Face(GameObject &associated) : Component(associated), hitpoints(30) {
        //std::cout<<"Face GO addr:"<<&(this->associated)<<std::endl;
}

void Face::Damage(int damage) {
    if (damage >= hitpoints) {
        //std::cout<<"Damage GO addr:"<<&associated<<std::endl;
        associated.RequestDelete();
        auto sound = reinterpret_cast<Sound*>(associated.GetComponent("Sound"));
        if (sound != nullptr) {
            // std::cerr << "Play Death" << std::endl;
            sound->Play();
        }
    } else {
        hitpoints -= damage;
    }
}

void Face::Update(float) {
    //std::cout<<"Update GO addr:"<<&associated<<std::endl;
}

void Face::Render() {
    //std::cout<<"Render GO addr:"<<&associated<<std::endl;
}

bool Face::Is(std::string type) {
    return type == "Face";
}
