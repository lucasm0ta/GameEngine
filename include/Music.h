#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <SDL2/SDL_mixer.h>

class Music {
public:
    Music();
    Music(std::string file);
    ~Music();

    void Play(int time = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool isOpen();

private:
    Mix_Music *music;
};

#endif /* MUSIC_H */