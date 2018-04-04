#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include "Component.h"
#include "GameObject.h"

class Sprite : public Component {
public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, std::string file);
    ~Sprite();

    int GetHeight();
    int GetWidth();

    bool Is(std::string type);
    bool IsOpen();
    void Open(std::string file);
    void Render();
    void SetClip(int x, int y, int w, int h);
    void Update(float dt);

private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
};

#endif /* SPRITE_H */
