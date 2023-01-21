#include "framework.h"
#include "Source\environment.h"

Enemy::Enemy(Cube* _appearance) : appearance(_appearance)
{
	respawnPosition = appearance->position;
}

Enemy::~Enemy()
{
	delete appearance;
}

void Enemy::movePosition()
{
	count++;

	float moveY = sinf(count / 20) / 20;

	XMFLOAT3 worldMovingVector = { 0.0f, moveY, 0.0f };

	appearance->position = appearance->position + worldMovingVector;
}

void Enemy::die()
{
	respawnFrameCount = 0;
	appearance->disableAll();
}

void Enemy::checkRespawn()
{
	respawnFrameCount++;
	if (respawnFrameCount >= respawnFrame)
	{
		respawn();
	}
}

void Enemy::respawn()
{
	count = 0;
	appearance->enableAll();
	appearance->position = respawnPosition;
}