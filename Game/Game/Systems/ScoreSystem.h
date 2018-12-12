#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include "..//Entities/Entities.h"

/// <summary>
/// Keeps track of the players score
/// </summary>

class ScoreSystem {

public: 
	void addEntity(Entity en);
	void updateScore(Entity en);
	void setValues();

	std::vector<ScoreComponent*> getScores();

private: 
	

	vector<Entity> m_entityList;
	int m_score = 50;
	//Move to entity
	ScoreComponent* sc1;
	ScoreComponent* sc2;

};


#endif // !SCORESYSTEM_H
