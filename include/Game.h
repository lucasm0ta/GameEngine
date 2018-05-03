#ifndef GAME_H
#define GAME_H

#include <string>
#include "State.h"
#include <SDL2/SDL.h>

class Game {
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State &GetState();
    static Game &GetInstance();
    float GetDeltaTime();

private:
    Game(std::string title, int width, int height);
    void CalculateDeltaTime();

    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
    bool hasStarted;
    int frameStart;
    float dt;
};

#endif /* GAME_H */
