#include "../include/Component.h"
#include <iostream>

Component::Component(GameObject &assoc) : associated(assoc) {
    //std::cout<<"Component GO addr:"<<&assoc<<std::endl;
}
