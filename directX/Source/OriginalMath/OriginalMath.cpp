#include "framework.h"
#include "Source\environment.h"

float OriginalMath::length(const XMFLOAT3& vector)
{
	float length = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	return length;
}

float OriginalMath::dot(const XMFLOAT3& vector1, const XMFLOAT3& vector2)
{
	float dot = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
	return dot;
}

XMFLOAT3 OriginalMath::normalize(const XMFLOAT3& vector)
{
	if (isnan((vector / length(vector)).x) || isnan((vector / length(vector)).y) || isnan((vector / length(vector)).z))
	{
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMFLOAT3 normal = vector / length(vector);
	return normal;
}

float OriginalMath::angle(const XMFLOAT3& vector1, const XMFLOAT3& vector2)
{
	float cos = dot(normalize(vector1), normalize(vector2));
	if (cos >= 1.0f)   cos = 1.0f;
	if (cos <= -1.0f)   cos = -1.0f;
	float angle = acosf(cos);

	return angle;
}

XMFLOAT3 OriginalMath::multiplyMatrix(const XMFLOAT3& vector, const XMMATRIX& matrix)
{
	XMFLOAT3 newVector{};
	XMStoreFloat3(&newVector, XMVector4Transform(XMLoadFloat3(&vector), matrix));
	return newVector;
}