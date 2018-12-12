#include "ScoreSystem.h"
#include <iostream>

/// <summary>
/// Adds entity to list
/// </summary>

void ScoreSystem::addEntity(Entity en)
{
	m_entityList.push_back(en);
}

/// <summary>
/// increase score
/// </summary>

void ScoreSystem::updateScore(Entity en)
{
	for (Entity& i : m_entityList) {
		if (i.id == en.id) {
			if (i.id == 1) {
				sc1->setScore(sc1->getScore() + m_score);
				std::cout << " P1 Score: " << sc1->getScore() << std::endl;
			}
			if (i.id == 2) {
				sc2->setScore(sc2->getScore() + m_score);
				std::cout << " P2 Score: " << sc2->getScore() << std::endl;
			}
		}
	}
}

void ScoreSystem::setValues() {
	for (Entity& i : m_entityList) {
		if (i.id == 1) {
			for (Component* j : i.getComponents()) {
				if (j->id == 5) {
					sc1 = dynamic_cast<ScoreComponent*>(j);
				}
			}
		}
		if (i.id == 2) {
			for (Component* j : i.getComponents()) {
				if (j->id == 5) {
					sc2 = dynamic_cast<ScoreComponent*>(j);
				}
			}
		}
	}
}

std::vector<ScoreComponent*> ScoreSystem::getScores() {
	std::vector<ScoreComponent*> s;
	s.push_back(sc1);
	s.push_back(sc2);
	return s;
}