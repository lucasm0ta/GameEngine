#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include "Component.h"
#include "GameObject.h"
#include "Rect.h"

class Sprite : public Component {
public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, std::string file);
    ~Sprite();

    int GetHeight();
    int GetWidth();

    bool Is(std::string type);
    std::string Type();
    bool IsOpen();
    void Open(std::string file);
    void Render();
    void Render(float x, float y);
    void Update(float dt);

    void SetClip(int x, int y, int w, int h);
    void SetClip(Rect rec);
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();

private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
};

#endif /* SPRITE_H */
