#include "framework.h"
#include "Source\environment.h"

XMFLOAT3 operator+ (XMFLOAT3 v1, XMFLOAT3 v2)
{
	XMFLOAT3 v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;

	return v;
}

XMFLOAT3 operator- (XMFLOAT3 v1, XMFLOAT3 v2)
{
	XMFLOAT3 v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;

	return v;
}

XMFLOAT3 operator* (XMFLOAT3 v1, float num)
{
	XMFLOAT3 v;
	v.x = v1.x * num;
	v.y = v1.y * num;
	v.z = v1.z * num;

	return v;
}

XMFLOAT3 operator/ (XMFLOAT3 v1, float num)
{
	XMFLOAT3 v;
	v.x = v1.x / num;
	v.y = v1.y / num;
	v.z = v1.z / num;

	return v;
}