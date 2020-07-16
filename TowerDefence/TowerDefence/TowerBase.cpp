#include "TowerBase.h"
#include "GameManager.h"
#include "BulletBase.h"

TowerBase::TowerBase()
{
}

TowerBase::TowerBase(SDL_Renderer* renderer, EnemyManager* enemyManager, SpriteManager* spriteManager, BulletManager* bulletManager, EffectsManager* effectsManager, Sprite* sprite, Vector2D position, Vector2D scale) : renderer(renderer), enemyManager(enemyManager), spriteManager(spriteManager), bulletManager(bulletManager), effectsManager(effectsManager), sprite(sprite), position(position), scale(scale)
{
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	collider = new Collider(this->position, 90.0f);
}

TowerBase::~TowerBase()
{
}

void TowerBase::Start()
{
}

void TowerBase::Update()
{
	if (currentEnemyTarget == nullptr)
	{
		if (enemyManager->GetEnemies().empty() == false)
		{
			for (std::vector<EnemyBase*> enemies : enemyManager->GetEnemies())
			{
				if (enemies.empty() == false)
				{
					for (EnemyBase* enemy : enemies)
					{
						if (collider->isPointInCircle(position + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
							enemy->GetPosition() + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2), collisionRadius))
						{
							currentEnemyTarget = enemy;
							break;
						}
					}
				}
			}
		}
	}
	else if (collider->isPointInCircle(position + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
		currentEnemyTarget->GetPosition() + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
		collisionRadius) == false)
	{
		currentEnemyTarget = nullptr;
	}

	if (currentEnemyTarget != nullptr)
	{
		shootTimer++;

		if (shootTimer >= shootMaxTime)
		{
			BulletBase* bullet = new BulletBase(renderer, enemyManager, effectsManager, spriteManager->GetSprite(SpriteName::startPosition),
				position + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
				currentEnemyTarget->GetPosition() + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
				Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 4, GameManager::DEFAULT_SPRITE_SIZE / 4));

			bulletManager->AddBullet(bullet);

			shootTimer = 0.0f;
		}
	}
}

void TowerBase::Render()
{
	SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);

	//Draw a circle for the collisions
	//DrawDebugCircle();
}

void TowerBase::Destroy()
{
}

void TowerBase::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}
