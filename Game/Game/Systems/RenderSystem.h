#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "..//Entities/Entities.h"
#include <SDL_ttf.h>
#include <string>

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
	int m_score = 0;
	SDL_Surface* surfaceMessage;
	SDL_Texture* MessageText;
	SDL_Rect Message_rect;

};

#endif // !RENDERSYSTEM


