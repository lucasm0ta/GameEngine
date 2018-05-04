#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

#include <vector>
#include <memory>
#include <random>

class State {
public:
    State();
    ~State();

    void LoadAssets();
    bool QuitRequested();
    void Update(float dt);
    void Render();
    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

private:
    void Input();

    std::vector<std::shared_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;
    std::random_device randDevice;
    std::mt19937 randGen;
    bool started;
};

#endif /* STATE_H */
