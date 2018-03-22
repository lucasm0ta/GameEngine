#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
    // Start SDL

    // FLAGS
    // SDL_INIT_TIMER
    // SDL_INIT_GAMECONTROLLER
    // SDL_INIT_AUDIO
    // SDL_INIT_EVENTS
    // SDL_INIT_VIDEO
    // SDL_INIT_EVERYTHING
    // SDL_INIT_JOYSTICK
    // SDL_INIT_NOPARACHUTE
    // SDL_INIT_HAPTIC

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}

    // FLAGS
    // IMG_INIT_JPEG
    // IMG_INIT_PNG
    // IMG_INIT_TIF

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    // FLAGS
    // MIX_INIT_FLAC
    // MIX_INIT_MP3
    // MIX_INIT_OGG
    // MIX_INIT_MOD
    // MIX_INIT_FLUIDSYNTH
    // MIX_INIT_MODPLUG

    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(32);

	// Start Window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	// Start Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
}

Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
	SDL_Quit();
}
SDL_Renderer* Game::GetRenderer() {
    return renderer;
}
State &Game::GetState() {
    return *state;
}
Game &Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Lucas Mota Ribeiro 12/0016885", 1024, 600);
    }
    return *instance;
}

void Game::Run() {
	state = new State();
    Music mus("./assets/audio/stageState.ogg");
    mus.Play();
    while (!state->QuitRequested()) {
        state->Update(1);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}
