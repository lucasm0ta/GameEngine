#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include "Component.h"
#include "GameObject.h"
#include "Rect.h"
#include "Timer.h"

class Sprite : public Component {
public:
    Sprite(GameObject &associated, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
    Sprite(GameObject &associated, std::string file, int frameCount = 1, float frameTime = 1,
        float secondsToSelfDestruct = 0);
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

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);

private:
    SDL_Texture *texture;
    SDL_Rect clipRect;
    int width;
    int height;
    Vec2 scale;
    int frameCount;
    int currentFrame;
    float frameTime;
    float secondsToSelfDestruct;
    Timer timer;
};

#endif /* SPRITE_H */
