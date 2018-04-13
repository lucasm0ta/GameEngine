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

private:
    void Input();
    void AddObject(int mouseX, int MouseY);

    std::vector<std::unique_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;
    std::random_device randDevice;
    std::mt19937 randGen;
};

#endif /* STATE_H */
