#include <iostream>
#include <SDL2/SDL.h>

#include "../include/Sound.h"

Sound::Sound(GameObject &associated): Component(associated), chunk(nullptr) {
}

Sound::Sound(GameObject &associated, std::string file) : Sound(associated) {
    Open(file);
}

Sound::~Sound() {
    if (chunk != nullptr) {
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times) {
    if (chunk != nullptr) {
        channel = Mix_PlayChannel(-1, chunk, 1);
        // std::cerr<< "Sound at channel:"<<channel<<" at "<<&(*this)<<std::endl;
    } else {
        std::cerr<< "No sound to be played"<<std::endl;
    }
}

bool Sound::Playing() {
    return (Mix_Playing(channel) == 1);
}

void Sound::Stop() {
    if (chunk == nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    if (chunk != nullptr) {
        Mix_FreeChunk(chunk);
    }
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr){
        std::cerr<< "Failed to open WAV"<<std::endl;
    }
    // std::cerr<< "Carregou som at "<<&(*this)<<std::endl;
}

bool Sound::IsOpen() {
    return (chunk != nullptr);
}

void Sound::Update(float) {
}

void Sound::Render() {
}

bool Sound::Is(std::string type) {
    return type == "Sound";
}
