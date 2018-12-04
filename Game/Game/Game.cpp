#include "Game.h"
#include <time.h>

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
	m_colDet.setValues();
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

	while (!m_exitGame) {

		processEvents();
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		update();
		render();

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
	m_movementSystem.update();
	m_colDet.update();
	m_colDet.setValues();
}

void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	SDL_RenderClear(m_renderer);

	m_renderSystem.render(m_renderer);

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

	m_player1->addComponent(m_healthComponent);
	m_player1->addComponent(m_positionComponent);
	m_player1->addComponent(m_controlComponent);
	m_player1->addComponent(m_chaseComponent);

	m_positionComponent = new PositionComponent(std::pair<float, float>(1000, 600));
	m_player2->addComponent(m_healthComponent);
	m_player2->addComponent(m_positionComponent);
	m_player2->addComponent(m_controlComponent2);
	m_player2->addComponent(m_chaseComponent2);
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

	m_movementSystem.addEntity(*m_player1);
	m_movementSystem.addEntity(*m_player2);

	m_colDet.addEntity(*m_player1);
	m_colDet.addEntity(*m_player2);

	m_colDet.addSystem(m_healthSystem);
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

	m_colDet.setValues();
}