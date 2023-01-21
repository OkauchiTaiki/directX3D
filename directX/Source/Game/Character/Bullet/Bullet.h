#pragma once

class Bullet
{
public:
	Bullet(Sphere* _appearance);
	~Bullet();

	//Œ©‚½–Ú
	Sphere* appearance;
private:
	static const float survivalLimitedRangeX;
	static const float survivalLimitedRangeY;
	static const float survivalLimitedRangeZ;
	static const float speed;
	XMFLOAT3 moveVector{};

public:
	void generateBullet(XMFLOAT3 moveVec, XMFLOAT3 position);

	void move();

	bool existOutsideTheLimitedRange();

	void die();

};

