#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include "Entities/Entities.h"
#include "Components/Components.h"
#include "Systems/MovementSystem.h"
#include "Systems/HealthSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/CollisionDetection.h"
#include "Client/Client.h"

using namespace std;

class Game {

public:
	Game();
	~Game();

	void run();

	void initClient();

private:

	Client m_client;
	void MessageResponse(std::map<std::string, int> parsedMessage);

	void processEvents();
	void update();
	void render();
	void initialiseEntitys();
	void initialiseComponents();
	void initialiseSystems();
	void setUpGame();
	void setUpFont();
	void doSomeFont();
	void timerCount();


	SDL_Window *m_window;
	int m_windowWidth = 1280;
	int m_windowHeight = 720;

	SDL_Renderer *m_renderer;

	bool m_exitGame;
	int timerInt = 0;

	Entity* m_player1;
	Entity* m_player2;

	HealthComponent* m_healthComponent;
	ControlComponent* m_controlComponent;
	ControlComponent* m_controlComponent2;
	PositionComponent* m_positionComponent;
	ChaseComponent* m_chaseComponent;
	ChaseComponent* m_chaseComponent2;
	ScoreComponent* m_scoreComponent;
	ScoreComponent* m_scoreComponent2;

	HealthSystem m_healthSystem;
	RenderSystem m_renderSystem;
	MovementSystem m_movementSystem;
	CollisionDetection m_colDet;
	ScoreSystem m_scoreSystem;


	SDL_Texture* Message;
	SDL_Rect Message_rect;
	SDL_Surface* surfaceMessage;
	TTF_Font* Sans;

	SDL_Texture* Message2;
	SDL_Rect Message_rect2;
	SDL_Surface* surfaceMessage2;
	

	SDL_Texture* timerT;
	SDL_Rect timer_rect;
	SDL_Surface* timerMessage;


	Uint32 old_time, current_time;

	float ftime;
	
	bool gameSet = false;
};



#endif // !GAME
