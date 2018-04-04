#include <string>
#include <vector>
#include <iostream>

#include "../include/Component.h"
#include "../include/GameObject.h"

GameObject::GameObject() : isDead(false) {
}

GameObject::~GameObject() {
    for (Component *cmp : components) {
        delete cmp;
    }
    // std::cout<<"Delete"<<std::endl;
    //std::cout<<"Delete isDead:"<<((isDead)?"True":"False")<<std::endl;
}

void GameObject::Update(float dt) {
    //std::cerr << "Size Components:"<<components.size()<<std::endl;
    //std::cout<<"Update isDead:"<<((isDead)?"True":"False")<<std::endl;
    for (Component *cmp : components) {
        if (cmp != nullptr) cmp->Update(dt);
    }
}

void GameObject::Render() {
    for (Component *cmp : components) {
        if (cmp != nullptr) cmp->Render();
    }
    //std::cout<<"Render isDead:"<<((isDead)?"True":"False")<<std::endl;
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
    //std::cout<<"ReqDelete isDead:"<<((isDead)?"True":"False")<<std::endl;
}

void GameObject::AddComponent(Component *cpt) {
    components.push_back(cpt);
    //std::cout<<"AddCmp isDead:"<<((isDead)?"True":"False")<<std::endl;
}

void GameObject::RemoveComponent(Component *cpt) {
    std::vector<Component*>::iterator i =  components.begin();
    while (i != components.end()) {
        if (*i == cpt){
            components.erase(i);
            break;
        }
    }
    //std::cout<<"RemComp isDead:"<<((isDead)?"True":"False")<<std::endl;
}

Component *GameObject::GetComponent(std::string type) {
    for (Component *cmp : components) {
        if (cmp->Is(type)) {
            return cmp;
        }
    }
    //std::cout<<"GetCmp isDead:"<<((isDead)?"True":"False")<<std::endl;
    return nullptr;
}
