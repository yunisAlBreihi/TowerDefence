#include "TowerBase.h"
#include "GameManager.h"
#include "BulletBase.h"

TowerBase::TowerBase()
{
}

TowerBase::TowerBase(SDL_Renderer* renderer, EnemyManager* enemyManager, SpriteManager* spriteManager, BulletManager* bulletManager, Sprite* sprite, Vector2D position, Vector2D scale) : renderer(renderer), enemyManager(enemyManager), spriteManager(spriteManager),bulletManager(bulletManager), sprite(sprite), position(position), scale(scale)
{
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
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
						if (isPointInCircle(position + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
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
	else if (isPointInCircle(position + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
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
			BulletBase* bullet = new BulletBase(renderer, spriteManager->GetSprite(SpriteName::startPosition),
				position + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
				currentEnemyTarget->GetPosition() + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
				Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 4 , GameManager::DEFAULT_SPRITE_SIZE / 4));

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

bool TowerBase::isPointInCircle(Vector2D firstPosition, Vector2D secondPosition, float radius)
{
	return ((firstPosition.x - secondPosition.x) * (firstPosition.x - secondPosition.x) + (firstPosition.y - secondPosition.y) * (firstPosition.y - secondPosition.y)) < radius * radius;
}

void TowerBase::DrawDebugCircle()
{
	if (collisionRadius > 0)
	{
		for (size_t i = 0; i < 360; i += 4)
		{
			circlePosition = Vector2D(GetPosition().x + collisionRadius * std::cos(i), GetPosition().y + collisionRadius * std::sin(i));
			SDL_SetRenderDrawColor(renderer, 230, 0, 126, 255);
			SDL_RenderDrawPoint(renderer, circlePosition.x + scale.x / 2, circlePosition.y + scale.y / 2);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}
}

void TowerBase::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}
