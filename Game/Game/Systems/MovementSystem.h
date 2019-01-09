#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Entities/Entities.h"

/// <summary>
/// Control system moves any entities attached in the direction the button is pressed.
/// </summary>
class MovementSystem {
public:
	void addEntity(Entity* en);
	void control(SDL_Keycode in);
	void update();

private:
	vector<Entity*> m_entityList;
	PositionComponent* p;
	ControlComponent* c;
	ChaseComponent* chase;

	float x = 0;
	float y = 0;
	float avoidSpeed = 6.5;
	float chaseSpeed = 8;
	float m_currentSpeed = 0;

	void checkBoundary();
	int screenWidth = 1280;
	int screenHeight = 720;

};

#endif // !MOVEMENTSYSTEM_H
