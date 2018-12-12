#include "CollisionDetection.h"

void CollisionDetection::addEntity(Entity en)
{
	m_entityList.push_back(en);
}

void CollisionDetection::addSystemH(HealthSystem sys)
{
	HealthSys = sys;
}

void CollisionDetection::addSystemS(ScoreSystem sys)
{
	ScoreSys = sys;
}

void CollisionDetection::update()
{
	chaserChecks();
}

void CollisionDetection::collisionResponseChaser(Entity chaser, Entity notChaser)
{
	HealthSys.updateHealth(notChaser);
	ScoreSys.updateScore(notChaser);

	for (Entity& i : m_entityList) {
		for (Component* j : i.getComponents()) {
			if (j->id == 2) {
				dynamic_cast<PositionComponent*>(j)->resetPos();
			}
		}
	}

	if (chaser.id == 1) {
		chase1->setChaser(false);
		chase1->setColor(SDL_Color{ 0,0,255,255 });
	}
	else if (chaser.id == 2) {
		chase2->setChaser(false);
		chase2->setColor(SDL_Color{ 0,0,255,255 });
	}
	else if (chaser.id == 3) {
		chase3->setChaser(false);
		chase3->setColor(SDL_Color{ 0,0,255,255 });
	}

	if (notChaser.id == 1) {
		chase1->setChaser(true);
		chase1->setColor(SDL_Color{ 255,0,0,255 });
	}
	else if (notChaser.id == 2) {
		chase2->setChaser(true);
		chase2->setColor(SDL_Color{ 255,0,0,255 });
	}
	else if (notChaser.id == 3) {
		chase3->setChaser(true);
		chase3->setColor(SDL_Color{ 255,0,0,255 });
	}
}

void CollisionDetection::setValues()
{
	for (Entity& i : m_entityList) {
		if (i.id == 1) {
			for (Component* j : i.getComponents()) {
				if (j->id == 1) {
					Health1 = dynamic_cast<HealthComponent*>(j);
				}
				if (j->id == 2) {
					x1 = std::get<0>(dynamic_cast<PositionComponent*>(j)->getPos());
					y1 = std::get<1>(dynamic_cast<PositionComponent*>(j)->getPos());
					radius = i.getRadius();
				}
				if (j->id == 4) {
					chase1 = dynamic_cast<ChaseComponent*>(j);
				}
			}
		}
		if (i.id == 2) {
			for (Component* j : i.getComponents()) {
				if (j->id == 1) {
					Health1 = dynamic_cast<HealthComponent*>(j);
				}
				if (j->id == 2) {
					x2 = std::get<0>(dynamic_cast<PositionComponent*>(j)->getPos());
					y2 = std::get<1>(dynamic_cast<PositionComponent*>(j)->getPos());
					radius = i.getRadius();
				}
				if (j->id == 4) {
					chase2 = dynamic_cast<ChaseComponent*>(j);
				}
			}
		}
		if (i.id == 3) {
			for (Component* j : i.getComponents()) {
				if (j->id == 1) {
					Health3 = dynamic_cast<HealthComponent*>(j);
				}
				if (j->id == 2) {
					x3 = std::get<0>(dynamic_cast<PositionComponent*>(j)->getPos());
					y3 = std::get<1>(dynamic_cast<PositionComponent*>(j)->getPos());
					radius = i.getRadius();
				}
				if (j->id == 4) {
					chase3 = dynamic_cast<ChaseComponent*>(j);
				}
			//	if (j->id == 5) {
				//	Score2 = dynamic_cast<ScoreComponent*>(j);
			//	}
			}
		}
	}
}

bool CollisionDetection::p1p2()
{
	dx = x2 - x1;
	dy = y2 - y1;
	radii = radius + radius;
	if ((dx * dx) + (dy * dy) < radii * radii)
	{
		return true;
	}

	return false;
}


void CollisionDetection::chaserChecks()
{
	//collisions between 1&2
	if (p1p2() == true && chase1->m_chaser)
	{
		collisionResponseChaser(m_entityList.at(0), m_entityList.at(1));
	}
	else if (p1p2() == true && chase2->m_chaser)
	{
		collisionResponseChaser(m_entityList.at(1), m_entityList.at(0));
	}
}

