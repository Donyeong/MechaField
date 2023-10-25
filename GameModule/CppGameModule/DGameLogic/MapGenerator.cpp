#include "MapGenerator.h"

void GameMapGenerator::Generate()
{
	m_game_map_world = new GameMapWorld();

	KDTree& objs = m_game_map_world->objs;
	objs.insert(Point)
}
