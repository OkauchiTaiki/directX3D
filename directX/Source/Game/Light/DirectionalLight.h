#pragma once

class DirectionalLight
{
private:
	static XMFLOAT3 direction;
public:
	static XMVECTOR getDirection();
	static void setDirection(float x, float y, float z);

private:
	DirectionalLight() {}
};
