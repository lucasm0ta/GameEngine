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
        SDL_Delay(duration);
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
    } else {
    	Mix_QuerySpec(&frequency, &format, &channels);
        duration = Sound::computeChunkLengthMillisec(chunk->alen);
        // std::cerr<< "Carregou som at "<<&(*this)<<std::endl;
    }
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

int Sound::computeChunkLengthMillisec(int chunkSize) {
    /* bytes / samplesize == sample points */
	const int points = chunkSize / formatSampleSize(format);

	/* sample points / channels == sample frames */
	const int frames = (points / channels);

	/* (sample frames * 1000) / frequency == play length, in ms */
	return ((frames * 1000) / frequency);
}

int Sound::formatSampleSize(int format)
{
	return (format & 0xFF) / 8;
}
