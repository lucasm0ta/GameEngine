#ifndef FACE_H
#define FACE_H

#include "Component.h"
#include "GameObject.h"

class Face : public Component {
public:
    Face(GameObject &associated);
    ~Face() = default;

    void Damage(int damage);

    void Update(float dt);
    void Render();
    bool Is(std::string type);

private:
    int hitpoints;
};

#endif /* FACE_H */
