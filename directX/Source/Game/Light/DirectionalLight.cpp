#include "framework.h"
#include "Source\environment.h"

XMFLOAT3 DirectionalLight::direction = { -0.5f, -1.0f, 0.5f };

XMVECTOR DirectionalLight::getDirection()
{
	return XMVector3Normalize(XMLoadFloat3(&direction));
}

void DirectionalLight::setDirection(float x, float y, float z)
{
	direction = { x, y, z };
}