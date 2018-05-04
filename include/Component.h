#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include "GameObject.h"

class Component {
public:
    Component(GameObject &associated);
    virtual ~Component() = default;

    virtual bool Is(std::string type) = 0;
    virtual std::string Type() = 0;
    virtual void Render() = 0;
    virtual void Update(float dt) = 0;
    virtual void Start();

protected:
    GameObject &associated;
};

#endif /* COMPONENT_H */
