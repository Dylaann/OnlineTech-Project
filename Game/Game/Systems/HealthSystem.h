#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include "..//Entities/Entities.h"

/// <summary>
/// Constantly decreases entitys health.
/// </summary>
class HealthSystem {
public:
	void addEntity(Entity en);
	void updateHealth(Entity en);

private:
	vector<Entity> m_entityList;
	int m_damage = 50;

};

#endif // !HEALTHSYSTEM_H


