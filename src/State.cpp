#include <iostream>
#include <memory>

#include "../include/State.h"
#include "../include/Face.h"
#include "../include/Sound.h"

#define PI 3.14159

State::State() : quitRequested(false) {
    Music mus("./assets/audio/stageState.ogg");
    mus.Play();

    objectArray.push_back(std::unique_ptr<GameObject>(new GameObject()));
    //std::cerr <<"Mouse = ("<<mouseX<<','<<mouseY<<')'<<std::endl;
    //std::cerr <<"Size: "<<objectArray.size()<<std::endl;
    std::unique_ptr<GameObject> &obj = objectArray.back();

    //std::cout<<"Created:"<<&(*obj)<<std::endl;
    obj->box.x = 0;
    obj->box.y = 0;

    obj->box.w = 1024;
    obj->box.h = 600;

    Sprite *spr =  new Sprite(*obj, "./assets/img/ocean.jpg");
    obj->AddComponent(spr);
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {

}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Render() {
    for (const auto &go : objectArray) {
        go->Render();
    }
}

void State::Update(float dt) {
    Input();
    //std::cout<<"Size:"<<objectArray.size()<<std::endl;
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(1);
    }
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        //std::cout<<"Obj:"<<i<<std::endl;
        if (objectArray[i]->IsDead()) {
            // std::cout<<"Morreu de fato"<<std::endl;
            objectArray.erase(objectArray.begin() + i);
            i--; //adjust iterator ???
        }
    }
}

void State::Input() {
    SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				//std::cout<<"From unique_ptr:"<<&(*objectArray[i])<<std::endl;
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains((float)mouseX, (float)mouseY)) {
					Face* face = (Face*)go->GetComponent("Face");
                    //std::cerr <<"Acertou"<<std::endl;
					if ( nullptr != face ) {
                        //std::cerr <<"Damage"<<std::endl;
						// Aplica dano

                        //std::cout<<"\tBefore Damage:"<<(go->IsDead()?"Dead":"Alive")<<std::endl;

                        //std::cout<<"1GO addr:"<<&(*go)<<std::endl;
						face->Damage(30);
						// Sai do loop (só queremos acertar um)
						break;
					}
				} /*else {
                    std::cerr <<"Box: ("<<go->box.x<<','<< go->box.y<<')'<<'('<<go->box.w<<','<<go->box.h<<')'<<std::endl;
                    std::cerr <<"Mouse: ("<<mouseX<<','<<mouseY<<')'<<std::endl;
                }*/
			}
		}
		if (event.type == SDL_KEYDOWN) {
			// Se a tecla for ESC, setar a flag de quit
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				quitRequested = true;
			} else {// Se não, crie um objeto
				Vec2 objPos = Vec2(100, 0).GetRotated(- PI  + PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY) {
    objectArray.push_back(std::unique_ptr<GameObject>(new GameObject()));
    //std::cerr <<"Mouse = ("<<mouseX<<','<<mouseY<<')'<<std::endl;
    //std::cerr <<"Size: "<<objectArray.size()<<std::endl;
    std::unique_ptr<GameObject> &obj = objectArray.back();

    //std::cout<<"Created:"<<&(*obj)<<std::endl;
    obj->box.x = mouseX;
    obj->box.y = mouseY;

    obj->box.w = 200;
    obj->box.h = 200;

    Sprite *spr =  new Sprite(*obj, "./assets/img/penguinface.png");
    obj->AddComponent(spr);

    Sound *sound = new Sound(*obj, "./assets/audio/boom.wav");
    obj->AddComponent(sound);

    Face *face = new Face(*obj);
    obj->AddComponent(face);
}
