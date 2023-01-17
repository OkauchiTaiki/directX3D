#include "framework.h"
#include "Source\environment.h"

Enemy::Enemy(Cube* _appearance) : appearance(_appearance)
{
	count = 0;
}

Enemy::~Enemy()
{
	delete appearance;
}

const XMVECTOR* Enemy::getRotation() const
{
	return &rotation;
}

void Enemy::movePosition()
{
	//移動ベクトルを作る
	count++;

	float moveY = sinf(count / 10) / 20;

	XMFLOAT3 worldMovingVector = { 0.0f, moveY, 0.0f };

	appearance->position = appearance->position + worldMovingVector;
}