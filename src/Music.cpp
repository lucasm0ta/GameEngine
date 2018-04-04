#include "../include/Music.h"
#include <iostream>

Music::Music() : music(nullptr) {
}

Music::Music(std::string file) : music(nullptr) {
    Open(file);
}
Music::~Music() {
    if (music == nullptr) {
        Mix_FreeMusic(music);
    }
}

void Music::Play(int time) {
    if (music == nullptr) {
        std::cerr << "Error Music: There is no music to be played." << std::endl;
        return;
    }
    if (Mix_PlayMusic(music, time) == -1) { // error
        std::cerr << "Error Music SDL(Play): " << Mix_GetError() <<std::endl;
        return;
    }
}

void Music::Stop(int msToStop) {
    if (Mix_PlayingMusic()) {
        Mix_FadeOutMusic(msToStop);
    } else {
        std::cerr << "Error Music SDL: There is no playing." << std::endl;
    }
}

void Music::Open(std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
            std::cerr << "Error Music SDL(Open): " << Mix_GetError() <<std::endl;
    }
}

bool Music::IsOpen() {
    return (music != nullptr);
}
