#pragma once


enum class SpriteName
{
	grass = 0,
	water = 1,
	tower01 = 2,
	tower02 = 3,
	startPosition = 8,
	endPosition = 9,
	EnemySmall = 20,
	EnemyBig = 21,
	TowerSmall = 30,
	TowerBig = 31,
	Congratulations = 80,
	GameOver = 90,
};

enum class BulletType
{
	Regular,
	Freezing,
};

enum class ManagerName
{
	NONE,
	BulletManager,
	EffectsManager,
	EnemyManager,
	GameManager,
	MapManager,
	SpriteManager,
	TextureManager,
	TileManager,
	TowerManager,
	LevelManager,
	UIManager,
};