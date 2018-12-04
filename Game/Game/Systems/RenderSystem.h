#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "..//Entities/Entities.h"

/// <summary>
/// Draws any entites attached to the screen.
/// </summary>
class RenderSystem {
public:
	void addEntity(Entity en);
	void render(SDL_Renderer* renderer);

private:
	vector<Entity> m_entityList;
	SDL_Color m_color;
	int x = 0;
	int y = 0;
	int radius = 0;

};

#endif // !RENDERSYSTEM


