#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "./Component.h"
#include "./GameObject.h"

#include <string>

class CameraFollower : public Component{
public:
    CameraFollower(GameObject &go);

    void Update(float dt);
    void Render();
    bool Is(std::string type);
};

#endif /* CAMERAFOLLOWER_H */
