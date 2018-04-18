#include <iostream>

#include "../include/Game.h"
#include "../include/Resources.h"


std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    if (Resources::imageTable.find(file) != Resources::imageTable.end()) {
        return Resources::imageTable[file];
    } else {
        const char *dir = file.c_str();
        SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), dir);
        if (texture == nullptr) { // error
            std::cerr << "Error Sprite SDL: " << SDL_GetError() << std::endl;
            return nullptr;
        } else {
            std::cout << "Added Image"<<std::endl;
            Resources::imageTable.insert({file, texture});
            return Resources::imageTable[file];
        }
    }
}

void Resources::ClearImages() {
    auto it = Resources::imageTable.begin();
    while (it != Resources::imageTable.end()) {
        SDL_DestroyTexture(it->second);
        it++;
    }
    Resources::imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
    if (Resources::musicTable.find(file) != Resources::musicTable.end()) {
        return Resources::musicTable[file];
    } else {
        Mix_Music *music = Mix_LoadMUS(file.c_str());
        if (music  == nullptr) {
            std::cerr << "Error Music SDL(Open): " << Mix_GetError() <<std::endl;
            return nullptr;
        } else {
            std::cout << "Added Music"<<std::endl;
            Resources::musicTable.insert({file, music});
            return Resources::musicTable[file];
        }
    }
}

void Resources::ClearMusic() {
    auto it = Resources::musicTable.begin();
    while (it != Resources::musicTable.end()) {
        Mix_FreeMusic(it->second);
        it++;
    }
    Resources::musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
    if (Resources::soundTable.find(file) != Resources::soundTable.end()) {
        return Resources::soundTable[file];
    } else {
        Mix_Chunk *sound = Mix_LoadWAV(file.c_str());
        if (sound == nullptr) {
            std::cerr<< "Failed to open WAV"<<std::endl;
            return nullptr;
        } else {
            std::cout << "Added Sound"<<std::endl;
            Resources::soundTable.insert({file, sound});
            return Resources::soundTable[file];
        }
    }
}

void Resources::ClearSound() {
    auto it = Resources::soundTable.begin();
    std::cout << "Size:"<<  Resources::soundTable.size()<<std::endl;
    while (it != Resources::soundTable.end()) {
        std::cout << "Free Sound:" << it->first << std::endl;
        Mix_Chunk* sound = it->second;
        if (sound != nullptr)
            Mix_FreeChunk(sound);
        it++;
    }
    Resources::soundTable.clear();
}
