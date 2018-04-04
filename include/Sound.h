#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>

#include "Component.h"
#include "GameObject.h"

class Sound : public Component {
public:
    Sound(GameObject &associated);
    Sound(GameObject &associated, std::string file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

private:
    int computeChunkLengthMillisec(int chunkSize);
    inline int formatSampleSize(int format);
    Mix_Chunk* chunk;
    int channel;
    int duration;
    int frequency;
    Uint16 format;
    int channels;
};

#endif /* SOUND_H */
