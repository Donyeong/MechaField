#pragma once
#include "../DGenericLib/Generics.h"
#include "KDTree.h"

enum class eGameMapTileType {
	NONE,
	BOX,
};

struct GameMapTile {
public:
	int x, y;
	eGameMapTileType tile_type;
};

class  GameMapRoom {
public:
	DGeneric::Vector<GameMapTile> d;
};

class GameMapWorld {
public:
	DGeneric::Vector<GameMapRoom> rooms;
	KDTree objs;
};

class GameMapGenerator
{
public:
	void Generate();
	GameMapWorld* m_game_map_world;
};

