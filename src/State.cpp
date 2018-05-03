#include <iostream>
#include <memory>
#include <cmath>

#include "../include/State.h"
#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/TileMap.h"
#include "../include/TileSet.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"

#define PI 3.14159

State::State() : quitRequested(false), randGen(randDevice()) {
    Music mus("./assets/audio/stageState.ogg");
    mus.Play();

    objectArray.push_back(std::unique_ptr<GameObject>(new GameObject()));
    std::unique_ptr<GameObject> &bgObj = objectArray.back();

    //std::cout<<"Created:"<<&(*obj)<<std::endl;
    bgObj->box.x = 0;
    bgObj->box.y = 0;

    bgObj->box.w = 1024;
    bgObj->box.h = 600;
    Sprite *spr = new Sprite(*bgObj, "./assets/img/ocean.jpg");
    bgObj->AddComponent(spr);

    CameraFollower *follower = new CameraFollower(*bgObj);
    bgObj->AddComponent(follower);

    objectArray.push_back(std::unique_ptr<GameObject>(new GameObject()));
    std::unique_ptr<GameObject> &obj = objectArray.back();

    //std::cout<<"Created:"<<&(*obj)<<std::endl;
    obj->box.x = 0;
    obj->box.y = 0;

    obj->box.w = 1024;
    obj->box.h = 600;

    TileSet *set = new TileSet(*obj, "./assets/img/tileset.png", 64, 64);
    TileMap *tileMap = new TileMap(*obj, "./assets/map/tileMap.txt", set);
    obj->AddComponent(tileMap);
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {

}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Render() {
    for (const auto &go : objectArray) {
        go->Render();
    }
}

void State::Update(float dt) {
    Camera::Update(dt);

    InputManager &inp = InputManager::GetInstance();
    float mouseX, mouseY;
    mouseX = inp.GetMouseX();
    mouseY = inp.GetMouseY();
    if (inp.KeyPress(ESCAPE_KEY) || inp.QuitRequested()) {
        quitRequested = true;
        // std::cout<<"GOOD ";
    } else {
        // std::cout<<"BAD ";
    }
    if (inp.MousePress(LEFT_MOUSE_BUTTON)) {
    	for (int i = objectArray.size() - 1; i >= 0; --i) {
            GameObject* go = (GameObject*) objectArray[i].get();

            if (go->box.Contains((float)mouseX, (float)mouseY)) {
                Face* face = (Face*)go->GetComponent("Face");
                //std::cerr <<"Acertou"<<std::endl;
                if ( nullptr != face ) {
                    //std::cerr <<"Damage"<<std::endl;

                    //std::cout<<"\tBefore Damage:"<<(go->IsDead()?"Dead":"Alive")<<std::endl;
                    std::uniform_int_distribution<int> dist(0, 10);
                    face->Damage(dist(randGen) + 10);
                    break;
                }
            }
    	}
    }
    if (inp.IsKeyDown(LEFT_ARROW_KEY)) {
        // std::cout<<"leffft\n";
        Camera::pos += Vec2(dt, 0);
        // std::cout<<"CamPos:"<<Camera::pos<<" dt:"<<dt<<std::endl;
    }
    if (inp.IsKeyDown(RIGHT_ARROW_KEY)) {
        Camera::pos += Vec2(-dt, 0);
    }
    if (inp.IsKeyDown(UP_ARROW_KEY)) {
        Camera::pos += Vec2(0, dt);
    }
    if (inp.IsKeyDown(DOWN_ARROW_KEY)) {
        Camera::pos += Vec2(0, -dt);
    }
    if (inp.KeyPress(SPACE_KEY)) {
        Vec2 camPos = Camera::pos;
        std::uniform_real_distribution<float> realDist(0, 2);
        std::uniform_int_distribution<int> intDist(1, 200);
        auto randVec = Vec2(intDist(randGen), 0).GetRotated(PI*(realDist(randGen)));
        Vec2 mousePos = Vec2(mouseX, mouseY);
        Vec2 objPos = randVec + mousePos - camPos;
        // std::cout<<"Criou :"<<objPos<<" = "<<mousePos<<' '<<camPos<<std::endl;
        AddObject((int)objPos.x, (int)objPos.y);
    }

    //std::cout<<"Size:"<<objectArray.size()<<std::endl;
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        //std::cout<<"Obj:"<<i<<std::endl;
        if (objectArray[i]->IsDead()) {
            // std::cout<<"Morreu de fato"<<std::endl;
            auto soundComp = objectArray[i].get()->GetComponent("Sound");
            if (!soundComp || !static_cast<Sound *>(soundComp)->Playing()) {
                std::cerr << "Morreu"<<std::endl;
                objectArray.erase(objectArray.begin() + i);
                i--; //adjust iterator ???
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY) {
    objectArray.push_back(std::unique_ptr<GameObject>(new GameObject()));
    //std::cerr <<"Mouse = ("<<mouseX<<','<<mouseY<<')'<<std::endl;
    //std::cerr <<"Size: "<<objectArray.size()<<std::endl;
    std::unique_ptr<GameObject> &obj = objectArray.back();

    //std::cout<<"Created:"<<&(*obj)<<std::endl;
    obj->box.x = mouseX;
    obj->box.y = mouseY;

    obj->box.w = 200;
    obj->box.h = 200;

    Sprite *spr =  new Sprite(*obj, "./assets/img/penguinface.png");
    obj->AddComponent(spr);

    Sound *sound = new Sound(*obj, "./assets/audio/boom.wav");
    obj->AddComponent(sound);

    Face *face = new Face(*obj);
    obj->AddComponent(face);
}
