#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

#include <vector>
#include <memory>

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
};

#endif /* STATE_H */
