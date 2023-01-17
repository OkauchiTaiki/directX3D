#include "framework.h"
#include "Source\environment.h"

Bullet::Bullet(Sphere* _appearance) : appearance(_appearance)
{
	appearance->disableAll();
}

Bullet::~Bullet()
{

}

void Bullet::generateBullet(XMFLOAT3 moveVec)
{
	moveVector = moveVec;
	appearance->enableAll();
}

void Bullet::move()
{
	appearance->position = appearance->position + moveVector * speed;
}

void Bullet::death()
{
	appearance->disableAll();
}



