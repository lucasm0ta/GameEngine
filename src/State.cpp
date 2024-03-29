#include <iostream>
#include <memory>
#include <cmath>
#include <map>

#include "../include/Alien.h"
#include "../include/PenguinBody.h"
#include "../include/State.h"
#include "../include/Sound.h"
#include "../include/TileMap.h"
#include "../include/TileSet.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Collider.h"
#include "../include/CameraFollower.h"
#include "../include/Collision.h"

State::State() : quitRequested(false), randGen(randDevice()), started(false) {
    Music mus("./assets/audio/stageState.ogg");
    mus.Play();

    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    //std::cout<<"Created:"<<&(*obj)<<std::endl;
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetOrigin(1024, 600);
    Sprite *spr = new Sprite(*bgObj, "./assets/img/ocean.jpg");
    bgObj->AddComponent(spr);
    CameraFollower *followerBg = new CameraFollower(*bgObj);
    bgObj->AddComponent(followerBg);
    //std::cout<<"Created:"<<&(*obj)<<std::endl;
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);

    auto tileSetObj = std::make_shared<GameObject>();
    objectArray.push_back(tileSetObj);
    TileSet *set = new TileSet(*tileSetObj, "./assets/img/tileset.png", 64, 64);
    TileMap *tileMap = new TileMap(*tileSetObj, "./assets/map/tileMap.txt", set);
    tileSetObj->AddComponent(tileMap);

    auto penguinObj = std::make_shared<GameObject>();
    objectArray.push_back(penguinObj);
    penguinObj->box.SetCenter(512, 300);
    PenguinBody *penguin = new PenguinBody(*penguinObj);
    Camera::Follow(penguinObj);
    penguinObj->AddComponent(penguin);

    auto alienObj = std::make_shared<GameObject>();
    objectArray.push_back(alienObj);
    alienObj->box.SetOrigin(700, 400);
    Alien *alien = new Alien(*alienObj, 5);
    alienObj->AddComponent(alien);

    std::cout<<alienObj->box.GetX()<<" " <<alienObj->box.GetY()<<" "<<alienObj->box.GetW()<<" "<<alienObj->box.GetH()<<std::endl;
    std::cout<<penguinObj->box.GetX()<<" "<<penguinObj->box.GetY()<<" "<<penguinObj->box.GetW()<<" "<<penguinObj->box.GetH()<<std::endl;
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
    // std::cout<<"TIME dt:"<<dt<<std::endl;
    float speed = dt * CAMERA_SPEED;
    Camera::Update(dt);

    InputManager &inp = InputManager::GetInstance();
    if (inp.KeyPress(ESCAPE_KEY) || inp.QuitRequested()) {
        quitRequested = true;
        // std::cout<<"GOOD ";
    } else {
        // std::cout<<"BAD ";
    }
    if (inp.MousePress(LEFT_MOUSE_BUTTON)) {
    	/*for (int i = objectArray.size() - 1; i >= 0; --i) {
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
    	}*/
    }
    if (inp.IsKeyDown(LEFT_ARROW_KEY)) {
        Camera::pos += Vec2(speed, 0);
        // std::cout<<"CamPos:"<<Camera::pos<<" speed:"<<speed<<std::endl;
    }
    if (inp.IsKeyDown(RIGHT_ARROW_KEY)) {
        Camera::pos += Vec2(-speed, 0);
    }
    if (inp.IsKeyDown(UP_ARROW_KEY)) {
        Camera::pos += Vec2(0, speed);
    }
    if (inp.IsKeyDown(DOWN_ARROW_KEY)) {
        Camera::pos += Vec2(0, -speed);
    }
    if (inp.KeyPress(SPACE_KEY)) {
        /*Vec2 camPos = Camera::pos;
        std::uniform_real_distribution<float> realDist(0, 2);
        std::uniform_int_distribution<int> intDist(1, 200);
        auto randVec = Vec2(intDist(randGen), 0).GetRotated(PI*(realDist(randGen)));
        Vec2 mousePos = Vec2(mouseX, mouseY);
        Vec2 objPos = mousePos + randVec - camPos;
        // std::cout<<"Criou :"<<objPos<<" = "<<mousePos<<' '<<camPos<<std::endl;
        // AddObject((int)objPos.GetX(), (int)objPos.GetY());
        */
    }

    //std::cout<<"Size:"<<objectArray.size()<<std::endl;
    std::vector<std::shared_ptr<GameObject>> objColliders;
    std::map<std::shared_ptr<GameObject>, Collider*> mapColliders;
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
        auto collider = objectArray[i]->GetComponent("Collider");
        if (collider != nullptr) {
            auto obj = objectArray[i];
            // obj->NotifyCollision(*obj)
            // objectArray[i]->NotifyCollision(*objectArray[i]);
            objColliders.push_back(obj);
            mapColliders[obj] = dynamic_cast<Collider*>(collider);
        }
    }

    // GET ALL COLLISION COMBINATIONS
    const int N = objColliders.size();
    const int R = 2;
    std::vector<bool> v(N);
    std::fill(v.begin(), v.begin() + R, true);
    if (objColliders.size() > 1) {
        int count = 0;
        do {
            std::vector<std::shared_ptr<GameObject>> aux(2);
            std::shared_ptr<GameObject> obj1, obj2;
            for (int i = 0; i < N; ++i) {
               if (v[i]) {
                   if (obj1 == nullptr) {
                       obj1 = objColliders[i];
                   } else {
                       obj2 = objColliders[i];
                   }
               }
            }
            auto col1 = mapColliders[obj1];
            auto col2 = mapColliders[obj2];
            if (col1 != col2) {
                if (Collision::IsColliding(col1->box, col2->box, obj1->angle, obj2->angle)) {
                // if (Collision::IsColliding(Rect(0, 0, 10, 10), Rect(0, 0, 10, 10), 0, 0)) {
                    // std::cerr<<"COLLIDING "<< count <<" "<<&(obj1->box)<<" "<<&(obj2->box)<<std::endl;
                    obj1->NotifyCollision(*obj2);
                    obj2->NotifyCollision(*obj1);
                }
            } else {
                std::cerr<<"Bad objects at collision!"<<std::endl;
                std::cerr<<"OBJ 1:"<<((obj1 == nullptr)?"BAD":"GOOD")<<std::endl;
                std::cerr<<"OBJ 2:"<<((obj2 == nullptr)?"BAD":"GOOD")<<std::endl;
                break;
            }
            count++;
        } while (std::prev_permutation(v.begin(), v.end()));
    }

    for (unsigned int i = 0; i < objectArray.size(); i++) {
        //std::cout<<"Obj:"<<i<<std::endl;
        if (objectArray[i]->IsDead()) {
            // std::cout<<"Morreu de fato"<<std::endl;
            auto soundComp = objectArray[i].get()->GetComponent("Sound");
            if (!soundComp || !static_cast<Sound *>(soundComp)->Playing()) {
                // std::cerr << "Morreu"<<std::endl;
                objectArray.erase(objectArray.begin() + i);
                i--; //adjust iterator ???
            }
        }
    }
}

std::weak_ptr<GameObject> State::AddObject(std::weak_ptr<GameObject> go) {
    auto shared = go.lock();
    if (shared != nullptr) {
        objectArray.push_back(shared);
        if (started) {
            shared->Start();
        }
    } else {
        std::cerr <<"Added bad OBJ"<<std::endl;
    }
    //std::cerr <<"Mouse = ("<<mouseX<<','<<mouseY<<')'<<std::endl;
    //std::cerr <<"Size: "<<objectArray.size()<<std::endl;

    //std::cout<<"Created:"<<&(*obj)<<std::endl;
    /*obj->box.x = mouseX;
    obj->box.y = mouseY;

    obj->box.w = 200;
    obj->box.h = 200;

    Sprite *spr =  new Sprite(*obj, "./assets/img/penguinface.png");
    obj->AddComponent(spr);

    Sound *sound = new Sound(*obj, "./assets/audio/boom.wav");
    obj->AddComponent(sound);

    Face *face = new Face(*obj);
    obj->AddComponent(face);*/
    /*if (started) {
        obj->Start();
    }*/
    return go;
}
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (go == objectArray[i].get()){
            return objectArray[i];
        }
    }
    return std::weak_ptr<GameObject>();
}
void State::Start() {
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
        // std::cout<<"STARTED!:"<<i<<std::endl;
    }
    started = true;
}
