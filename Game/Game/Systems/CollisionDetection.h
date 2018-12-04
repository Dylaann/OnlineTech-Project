#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Entities/Entities.h"
#include "HealthSystem.h"
#include <iostream>

/// <summary>
/// Control system moves any entities attached in the direction the button is pressed.
/// </summary>
class CollisionDetection {
public:
	void addEntity(Entity en);
	void addSystem(HealthSystem sys);
	void update();
	void collisionResponseChaser(Entity chaser, Entity notChaser);
	void collisionResponsePlayers(Entity p1, Entity p2);
	void setValues();

private:
	vector<Entity> m_entityList;
	PositionComponent* p;
	ChaseComponent* chase1;
	ChaseComponent* chase2;
	ChaseComponent* chase3;

	HealthComponent* Health1;
	HealthComponent* Health2;
	HealthComponent* Health3;

	ControlComponent* control1;
	ControlComponent* control2;

	HealthSystem HealthSys;


	int x1 = 0;
	int y1 = 0;

	int x2 = 0;
	int y2 = 0;

	int x3 = 0;
	int y3 = 0;

	int radius = 0;

	int dx = 0;
	int dy = 0;
	int radii = 0;

	bool p1p2();
	bool p1p3();
	bool p2p3();

	void playerChecks();
	void chaserChecks();
};

#endif // !COLLISIONDETECTION_H

