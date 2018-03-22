#include "../include/State.h"

State::State() : quitRequested(false), bg("./assets/img/ocean.jpg") {
}

void State::LoadAssets() {

}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg.Render(0, 0);
}
