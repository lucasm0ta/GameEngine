#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <queue>
#include <memory>

#define SPEED 5.0

class Alien : public Component {
public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();

private:
    class Action {
    public:
        enum ActionType {
            MOVE = 0,
            SHOOT
        };
        Action(Alien::Action::ActionType actionType, Vec2 pos);
        ActionType type;
        Vec2 pos;
    };
    int nMinions;
    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif /* ALIEN_H */
