#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <utility>

/// <summary>
/// Component Interface
/// </summary>
class Component {
public:
	int id = 0;
	virtual ~Component() {}

};

/// <summary>
/// Health Component.
/// </summary>
class HealthComponent : public Component {
public:
	HealthComponent() : m_health(100) { id = 1; };

	int getHealth() { return m_health; };
	void setHealth(int health) { m_health = health; };

private:
	int m_health;

};

/// <summary>
/// Position Component.
/// </summary>
class PositionComponent : public Component {
public:
	PositionComponent(std::pair<float, float> pos) : m_position(pos) { id = 2;  m_start = pos;};

	std::pair<float, float> getPos() { return m_position; };
	void setPos(std::pair<float, float> pos) { m_position = pos; };
	void resetPos() { m_position = m_start; }

private:
	std::pair<float, float> m_position;
	std::pair<float, float> m_start;
};

/// <summary>
/// Control Component.
/// </summary>
class ControlComponent : public Component {
public:
	ControlComponent() { id = 3; };

	enum DirectionState {
		Idle,
		Left,
		Right,
		Up,
		Down
	};

	void changeState(DirectionState state) {
		m_currentGameState = state;
	};

	DirectionState m_currentGameState = DirectionState::Idle;
};

/// <summary>
/// Chaser Component.
/// </summary>
class ChaseComponent : public Component {
public:
	ChaseComponent() { id = 4; };

	bool m_chaser;

	void setChaser(bool state) {
		m_chaser = state;
	};

	SDL_Color getColor() { return m_color; };
	void setColor(SDL_Color color) { m_color = color; }

private:
	SDL_Color m_color;

};





/// <summary>
/// Score Component.
/// </summary>

class ScoreComponent : public Component {
public:
	ScoreComponent() : m_score(0) { id = 5; };

	int getScore() { return m_score; };
	void setScore(int score) { m_score = score; };

private:
	int m_score = 0;
};

#endif // !COMPONENTS_H


