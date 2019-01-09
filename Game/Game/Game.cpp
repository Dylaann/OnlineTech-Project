#include "Game.h"
#include <time.h>
#include <string>
#include <sstream>

Game::Game()
{
	srand(time(NULL));
	m_window = SDL_CreateWindow("Online Technologies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}
	else
	{

	}


	
	initialiseEntitys();
	initialiseComponents();
	initialiseSystems();
	setUpGame();
	setUpFont();
	m_scoreSystem.setValues();
	m_colDet.setValues();

	initClient();
}

Game::~Game()
{
}

void Game::run()
{
	const Uint32 fps = 60;
	const Uint32 minimumFrameTime = 1000 / fps;

	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;

	
	current_time = SDL_GetTicks();

	while (!m_exitGame) {

		processEvents();
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;
		
		old_time = current_time;
		current_time = SDL_GetTicks();
		ftime += (current_time - old_time) / 1000.0f;
		
		update();
		render();

		SDL_FreeSurface(surfaceMessage);
		SDL_FreeSurface(surfaceMessage2);
		SDL_FreeSurface(timerMessage);

		SDL_DestroyTexture(Message);
		SDL_DestroyTexture(Message2);
		SDL_DestroyTexture(timerT);

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
		
	}

	

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::processEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_exitGame = true;
			break;
		case SDL_KEYDOWN:
			m_movementSystem.control(event.key.keysym.sym);
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_exitGame = true;
				break;
		}
	}
}

void Game::update()
{
	MessageResponse(m_client.processMessage(m_client.Receive()));

	if (m_player1->m_connected && m_player2->m_connected) {

		m_movementSystem.update();
		m_colDet.update();
		m_colDet.setValues();
		m_scoreSystem.setValues();

		timerCount();
		doSomeFont();

		if (m_player1->getLocal()) {
			PositionComponent* p = nullptr;

			for (Component* j : m_player1->getComponents()) {
				if (j->id == 2) {
					p = dynamic_cast<PositionComponent*>(j);
				}
			}
			m_client.Send(p->getPosStr());
		}
		else if (m_player2->getLocal()) {
			PositionComponent* p = nullptr;

			for (Component* j : m_player2->getComponents()) {
				if (j->id == 2) {
					p = dynamic_cast<PositionComponent*>(j);
				}
			}
			m_client.Send(p->getPosStr());
		}
	}
}

void Game::render()
{
	SDL_Color White = { 255, 255, 255 };
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	SDL_RenderClear(m_renderer);

	m_renderSystem.render(m_renderer);

	SDL_RenderCopy(m_renderer, Message, NULL, &Message_rect);
	SDL_RenderCopy(m_renderer, Message2, NULL, &Message_rect2);
	SDL_RenderCopy(m_renderer, timerT, NULL, &timer_rect);

	SDL_RenderPresent(m_renderer);
}

/// <summary>
/// initialises entitys.
/// </summary>
void Game::initialiseEntitys()
{
	m_player1 = new Player(1);
	m_player2 = new Player(2);
}

/// <summary>
/// adds components to entitys.
/// </summary>
void Game::initialiseComponents()
{
	m_healthComponent = new HealthComponent();
	m_positionComponent = new PositionComponent(std::pair<float, float>(100, 100));
	m_controlComponent = new ControlComponent();
	m_controlComponent2 = new ControlComponent();
	m_chaseComponent = new ChaseComponent();
	m_chaseComponent2 = new ChaseComponent();
	m_scoreComponent = new ScoreComponent();
	m_scoreComponent2 = new ScoreComponent();

	m_player1->addComponent(m_healthComponent);
	m_player1->addComponent(m_positionComponent);
	m_player1->addComponent(m_controlComponent);
	m_player1->addComponent(m_chaseComponent);
	m_player1->addComponent(m_scoreComponent);

	m_positionComponent = new PositionComponent(std::pair<float, float>(1000, 600));
	m_player2->addComponent(m_healthComponent);
	m_player2->addComponent(m_positionComponent);
	m_player2->addComponent(m_controlComponent2);
	m_player2->addComponent(m_chaseComponent2);
	m_player2->addComponent(m_scoreComponent2);
}

/// <summary>
/// Adds entitys to systems.
/// </summary>
void Game::initialiseSystems()
{
	m_renderSystem.addEntity(*m_player1);
	m_renderSystem.addEntity(*m_player2);

	m_healthSystem.addEntity(*m_player1);
	m_healthSystem.addEntity(*m_player2);

	m_movementSystem.addEntity(m_player1);
	m_movementSystem.addEntity(m_player2);

	m_scoreSystem.addEntity(*m_player1);
	m_scoreSystem.addEntity(*m_player2);
	m_scoreSystem.setValues();

	m_colDet.addEntity(*m_player1);
	m_colDet.addEntity(*m_player2);

	m_colDet.addSystemH(m_healthSystem);
	m_colDet.addSystemS(m_scoreSystem);
}


void Game::setUpGame()
{
	SDL_Color m_red{ 255,0,0,255 };
	SDL_Color m_blue{ 0,0,255,255 };

	int i = rand() % 2 + 1;
	if (i == 1) {
		for (Component* j : m_player1->getComponents()) {
			if (j->id == 4)
			{
				 dynamic_cast<ChaseComponent*>(j)->setChaser(true);
				 dynamic_cast<ChaseComponent*>(j)->setColor(m_red);
			}
		}
		for (Component* j : m_player2->getComponents()) {
			if (j->id == 4) {
				dynamic_cast<ChaseComponent*>(j)->setChaser(false);
				dynamic_cast<ChaseComponent*>(j)->setColor(m_blue);
			}
		}
	}
	else if (i == 2) {
		for (Component* j : m_player1->getComponents()) {
			if (j->id == 4)
			{
				dynamic_cast<ChaseComponent*>(j)->setChaser(false);
				dynamic_cast<ChaseComponent*>(j)->setColor(m_blue);
			}
		}
		for (Component* j : m_player2->getComponents()) {
			if (j->id == 4) {
				dynamic_cast<ChaseComponent*>(j)->setChaser(true);
				dynamic_cast<ChaseComponent*>(j)->setColor(m_red);
			}
		}
	}
	else if (i == 3) {
		for (Component* j : m_player1->getComponents()) {
			if (j->id == 4)
			{
				dynamic_cast<ChaseComponent*>(j)->setChaser(false);
				dynamic_cast<ChaseComponent*>(j)->setColor(m_blue);
			}
		}
		for (Component* j : m_player2->getComponents()) {
			if (j->id == 4) {
				dynamic_cast<ChaseComponent*>(j)->setChaser(false);
				dynamic_cast<ChaseComponent*>(j)->setColor(m_blue);
			}
		}
	}
}

void Game::setUpFont() {

	if (TTF_Init() < 0)
	{
		std::cout << "error error error" << std::endl;
	}
	const char *path = "ASSETS\\arial.ttf";
	Sans = TTF_OpenFont(path, 50);
}

void Game::doSomeFont()
{
	SDL_Color White = { 255, 255, 255 };
	
	std::stringstream score1;
	score1 << "Player1 Score:" << std::to_string(m_scoreSystem.getScores().at(0)->getScore());
	surfaceMessage = TTF_RenderText_Solid(Sans, score1.str().c_str(), White);
	Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);
	Message_rect.x = 20;
	Message_rect.y = 20;
	Message_rect.w = 200;
	Message_rect.h = 100;
	
	
	std::stringstream score2;
	score2 << "Player2 Score:" << std::to_string(m_scoreSystem.getScores().at(1)->getScore());
	surfaceMessage2 = TTF_RenderText_Solid(Sans, score2.str().c_str(), White);
	Message2 = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage2);
	Message_rect2.x = 300;
	Message_rect2.y = 20;
	Message_rect2.w = 200;
	Message_rect2.h = 100;

	std::stringstream timer;
	timer << "Timer: " << static_cast<int>(ftime);
	timerMessage = TTF_RenderText_Solid(Sans, timer.str().c_str(), White);
	timerT = SDL_CreateTextureFromSurface(m_renderer, timerMessage);
	timer_rect.x = 1600;
	timer_rect.y = 20;
	timer_rect.w = 200;
	timer_rect.h = 100;

}

void Game::timerCount() {

	if (ftime > 15)
	{
		ftime = 0;
	}
}

void Game::initClient()
{
	if (m_client.init()) {
		if (!m_player1->m_connected && !m_player2->m_connected) {
			m_player1->m_connected = true;
		}
		else if (m_player1->m_connected && !m_player2->m_connected) {
			m_player2->m_connected = true;
		}
		else {
			std::cout << "Game Full" << std::endl;
		}
	}
}

void Game::MessageResponse(std::map<std::string, int> parsedMessage)
{
	for (auto const& pair : parsedMessage) {

		PositionComponent* p1 = nullptr;
		PositionComponent* p2 = nullptr;

		for (Component* j : m_player1->getComponents()) {
			if (j->id == 2) {
				p1 = dynamic_cast<PositionComponent*>(j);
			}
		}

		for (Component* j : m_player2->getComponents()) {
			if (j->id == 2) {
				p2 = dynamic_cast<PositionComponent*>(j);
			}
		}

		int x = std::get<0>(p1->getPos());
		int y = std::get<1>(p1->getPos());

		int x2 = std::get<0>(p2->getPos());
		int y2 = std::get<1>(p2->getPos());

		auto key = pair.first;
		auto value = pair.second;

		if (key == "FIRST") {
			m_player1->setLocal(true);
			m_player1->m_connected = true;
		}
		else if (key == "JOINED") {
			m_player2->setLocal(true);
			m_player2->m_connected = true;
		}
		else if (key == "X") {
			if (m_player1->getLocal()) {
				p2->setPos(std::make_pair(value, y2));
			}
			else if (m_player2->getLocal()) {
				p1->setPos(std::make_pair(value, y));
			}
		}
		else if (key == "Y") {
			if (m_player1->getLocal()) {
				p2->setPos(std::make_pair(x2, value));
			}
			else if (m_player2->getLocal()) {
				p1->setPos(std::make_pair(x, value));
			}
		}
	}
}