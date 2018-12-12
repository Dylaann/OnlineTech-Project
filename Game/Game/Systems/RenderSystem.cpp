#include "RenderSystem.h"
#include <iostream>
/// <summary>
/// adds entity to list.
/// </summary>
/// <param name="en"></param>
void RenderSystem::addEntity(Entity en)
{
	m_entityList.push_back(en);
}

/// <summary>
/// draws each entity at their position.
/// </summary>
/// <param name="renderer"></param>
void RenderSystem::render(SDL_Renderer* renderer)
{
	for (Entity& i : m_entityList) {
		for (Component* j : i.getComponents()) {
			if (j->id == 2) {
				x = std::get<0>(dynamic_cast<PositionComponent*>(j)->getPos());
				y = std::get<1>(dynamic_cast<PositionComponent*>(j)->getPos());
				radius = i.getRadius();
			}
			if (j->id == 4) {
				m_color = dynamic_cast<ChaseComponent*>(j)->getColor();
			}
			if (j->id == 5) {
				m_score = dynamic_cast<ScoreComponent*>(j)->getScore();
			}
		}
		
		SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
		if (TTF_Init() < 0)
		{
			//error
			std::cout << "error error error" << std::endl;
		}
		int point_x;
		int point_y;

	/*	const char *path = "ASSETS\\arial.ttf";
		TTF_Font* Sans = TTF_OpenFont(path, 50);
		SDL_Color White = { 255, 255, 255 };

		const char text = m_score;

		surfaceMessage = TTF_RenderText_Solid(Sans, &text, White);

		MessageText = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		Message_rect.x = 100;
		Message_rect.y = 100;
		Message_rect.w = 200;
		Message_rect.y = 200;

		SDL_RenderCopy(renderer, MessageText, NULL, &Message_rect);*/

		while (radius > 0)
		{
			for (int t = 0; t < 360; t++)
			{
				point_x = x + radius * cos(t);
				point_y = y + radius * sin(t);
				SDL_RenderDrawPoint(renderer, point_x, point_y);
			}
			radius--;
		}
	}
}