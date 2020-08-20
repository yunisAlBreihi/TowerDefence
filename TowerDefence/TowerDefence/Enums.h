#pragma once

enum class SpriteName
{
	Grass = 0,
	Water = 1,
	Tower01 = 2,
	Tower02 = 3,
	StartPosition = 8,
	EndPosition = 9,
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

enum class EnemyType
{
	SmallEnemy,
	BigEnemy,
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