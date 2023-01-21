#include "framework.h"
#include "Source\environment.h"

const float Bullet::survivalLimitedRangeX = 100.0f;
const float Bullet::survivalLimitedRangeY = 100.0f;
const float Bullet::survivalLimitedRangeZ = 100.0f;
const float Bullet::speed = 1.0f;

Bullet::Bullet(Sphere* _appearance) : appearance(_appearance)
{
	appearance->disableAll();
}

Bullet::~Bullet()
{

}

void Bullet::generateBullet(XMFLOAT3 moveVec, XMFLOAT3 position)
{
	moveVector = moveVec;
	appearance->position = position;
	appearance->enableAll();
}

void Bullet::move()
{
	appearance->position = appearance->position + moveVector * speed;

	if (existOutsideTheLimitedRange())
	{
		die();
	}
}

bool Bullet::existOutsideTheLimitedRange()
{
	if (fabsf(appearance->position.x) >= survivalLimitedRangeX ||
		fabsf(appearance->position.y) >= survivalLimitedRangeY ||
		fabsf(appearance->position.z) >= survivalLimitedRangeZ)
	{
		return true;
	}
	
	return false;
}

void Bullet::die()
{
	appearance->disableAll();
}



