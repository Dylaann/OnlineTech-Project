#include "HealthSystem.h"

/// <summary>
/// Adds entity to list
/// </summary>
/// <param name="en"></param>
void HealthSystem::addEntity(Entity en)
{
	m_entityList.push_back(en);
}

/// <summary>
/// decreases health.
/// </summary>
void HealthSystem::updateHealth(Entity en)
{
	for (Entity& i : m_entityList) {
		if (i.id == en.id) {
			for (Component* j : i.getComponents()) {
				if (j->id == 1) {
					int newHealth = dynamic_cast<HealthComponent*>(j)->getHealth() - m_damage;
					dynamic_cast<HealthComponent*>(j)->setHealth(newHealth);
				}
			}
		}
	}
}
