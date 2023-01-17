#pragma once

class Bullet
{
public:
	Bullet(Sphere* _appearance);
	~Bullet();

	//Œ©‚½–Ú
	Sphere* appearance;
private:
	const float speed = 3.0f;
	XMFLOAT3 moveVector;

public:
	void generateBullet(XMFLOAT3 moveVec);

	void move();

	void death();

};

