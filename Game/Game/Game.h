#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include "Entities/Entities.h"
#include "Components/Components.h"
#include "Systems/MovementSystem.h"
#include "Systems/HealthSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/CollisionDetection.h"

using namespace std;

class Game {

public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update();
	void render();
	void initialiseEntitys();
	void initialiseComponents();
	void initialiseSystems();
	void setUpGame();


	SDL_Window *m_window;
	int m_windowWidth = 1920;
	int m_windowHeight = 1080;

	SDL_Renderer *m_renderer;

	bool m_exitGame;

	Entity* m_player1;
	Entity* m_player2;

	HealthComponent* m_healthComponent;
	ControlComponent* m_controlComponent;
	ControlComponent* m_controlComponent2;
	ControlComponent* m_controlComponent3;
	PositionComponent* m_positionComponent;
	ChaseComponent* m_chaseComponent;
	ChaseComponent* m_chaseComponent2;
	ChaseComponent* m_chaseComponent3;

	HealthSystem m_healthSystem;
	RenderSystem m_renderSystem;
	MovementSystem m_movementSystem;
	CollisionDetection m_colDet;
};



#endif // !GAME
