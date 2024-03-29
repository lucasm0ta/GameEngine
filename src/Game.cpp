#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) : width(width), height(height) {
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
		std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
		hasStarted = false;
		return;
	}

    // FLAGS
    // IMG_INIT_JPEG
    // IMG_INIT_PNG
    // IMG_INIT_TIF

	int flags_img = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    int init_img = IMG_Init(flags_img);
	if ((init_img&flags_img) != flags_img) {
		printf("Error IMG_Init: %s\n", IMG_GetError());
		SDL_Quit();
		hasStarted = false;
		return;
	}
    // FLAGS
    // MIX_INIT_FLAC
    // MIX_INIT_MP3
    // MIX_INIT_OGG
    // MIX_INIT_MOD
    // MIX_INIT_FLUIDSYNTH
    // MIX_INIT_MODPLUG

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
		              MIX_DEFAULT_CHANNELS, 1024) == -1) {
	    printf("Error Mix_OpenAudio: %s\n", Mix_GetError());
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}

	int flags_mix = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
    int init_mix = Mix_Init(flags_mix);
	if ((init_mix&flags_mix) != flags_mix) {
		printf("Error Mix_Init: %s\n", Mix_GetError());
		SDL_Quit();
		hasStarted = false;
		return;
	}

    Mix_AllocateChannels(32);

	// Start Window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		std::cerr << "Error SDL_CreateWindow: " << SDL_GetError() << std::endl;
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}
	// Set fullscreen
	/*if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
		SDL_DestroyWindow(window);
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}*/


	// Start Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::cerr << "Error SDL_CreateRenderer: " << SDL_GetError() << std::endl;
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}
	int w,h;
	SDL_GetWindowSize(window, &w,&h);
	std::cout<<"WINDOW SIZE: ("<<w<<','<<h<<')'<<std::endl;

	srand(time(NULL));
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	hasStarted = true;
	dt = 0;
	frameStart = 0;
	std::cout<<"Iniciou"<<std::endl;
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

Vec2 Game::GetWindowSize() {
	return Vec2(width, height);
}

Game &Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Lucas Mota Ribeiro 12/0016885", 1024, 600);
    }
    return *instance;
}

void Game::Run() {
	if (hasStarted){
		state = new State();
		state->Start();
	    while (!state->QuitRequested()) {
			CalculateDeltaTime();
			float dt = GetDeltaTime();
			InputManager::GetInstance().Update(dt);
	        state->Update(dt);
	        state->Render();
	        SDL_RenderPresent(renderer);
	        SDL_Delay(33);
	    }
		Resources::ClearImages();
		Resources::ClearSound();
		Resources::ClearMusic();
	}
}

float Game::GetDeltaTime() {
	return dt;
}

void Game::CalculateDeltaTime() {
	int current = SDL_GetTicks();
	dt = std::abs(frameStart - current)/1000.0;
	frameStart = current;
}
