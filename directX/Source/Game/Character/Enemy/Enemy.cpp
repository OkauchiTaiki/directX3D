#include "framework.h"
#include "Source\environment.h"
#include <time.h>


XMFLOAT3 Random(int max, int min);

Enemy::Enemy(Cube* _appearance) : appearance(_appearance)
{
	respawnPosition = appearance->position;
	//@—”‰Šú‰»
	srand((unsigned int)time(NULL));
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
	respawnPosition = Random(5, -5);

	count = 0;
	appearance->enableAll();
	appearance->position = respawnPosition;
}

XMFLOAT3 Random(int max,int min)
{

	float random_x = min + (float)(rand()) / ((float)(RAND_MAX / (max - min)));
	float random_y = 0 + (float)(rand()) / ((float)(RAND_MAX / (max - 0)));
	float random_z = min + (float)(rand()) / ((float)(RAND_MAX / (max - min)));

	XMFLOAT3 RespawnPosition = { random_x,random_y,random_z };
	return RespawnPosition;
}