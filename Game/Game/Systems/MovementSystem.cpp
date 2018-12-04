#include "MovementSystem.h"

void MovementSystem::addEntity(Entity en)
{
	m_entityList.push_back(en);
}

void MovementSystem::control(SDL_Keycode in)
{
	for (Entity& i : m_entityList) {
		if (i.id == 1) {
			for (Component* j : i.getComponents()) {
				if (j->id == 3) {
					c = dynamic_cast<ControlComponent*>(j);
					switch (in) {
					case SDLK_UP:
						c->changeState(c->Up);
						break;
					case SDLK_DOWN:
						c->changeState(c->Down);
						break;
					case SDLK_LEFT:
						c->changeState(c->Left);
						break;
					case SDLK_RIGHT:
						c->changeState(c->Right);
						break;
					default:
						c->changeState(c->Idle);
						break;
					}
				}
			}
		}
	}
}

void MovementSystem::update()
{
	for (Entity& i : m_entityList) {

		for (Component* j : i.getComponents()) {
			if (j->id == 2) {

				p = dynamic_cast<PositionComponent*>(j);
			}

			if (j->id == 3)
			{
				c = dynamic_cast<ControlComponent*>(j);
			}

			if (j->id == 4)
			{
				chase = dynamic_cast<ChaseComponent*>(j);
			}
		}

		x = std::get<0>(p->getPos());
		y = std::get<1>(p->getPos());

		if (chase->m_chaser)
		{
			m_currentSpeed = chaseSpeed;
		}
		else
		{
			m_currentSpeed = avoidSpeed;
		}

		if (c->m_currentGameState == c->Up) {
			y -= m_currentSpeed;
		}

		if (c->m_currentGameState == c->Down) {
			y += m_currentSpeed;
		}

		if (c->m_currentGameState == c->Right) {
			x += m_currentSpeed;
		}

		if (c->m_currentGameState == c->Left) {
			x -= m_currentSpeed;
		}

		checkBoundary();
		std::pair<float, float> m_pos = { x, y };
		p->setPos(m_pos);
	}
}

void MovementSystem::checkBoundary()
{
	if (x + 50 > 1920)
	{
		x = 1920 - 50;
	}
	else if (x - 50 < 0)
	{
		x = 50;
	}

	if (y + 50 > 1080)
	{
		y = 1080 - 50;
	}
	else if (y - 50 < 0)
	{
		y = 50;
	}
}
