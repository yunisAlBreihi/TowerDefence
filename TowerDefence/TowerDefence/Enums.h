#pragma once

enum class SpriteName
{
	Grass = 0,
	Water = 1,
	RegularTowerGround = 2,
	FrostTowerGround = 3,
	EnemyBase = 8,
	PlayerBase = 9,
	SmallEnemy = 20,
	BigEnemy = 21,
	RegularTower = 30,
	FrostTower = 31,
	RegularBullet = 40,
	FrostBullet = 41,
	RegularExplosion = 50,
	FrostExplostion = 51,
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
	EnemySmall,
	EnemyBig,
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