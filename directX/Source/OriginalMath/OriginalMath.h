#pragma once
#define PI 3.14159265f

class OriginalMath
{
public:
	static float length(const XMFLOAT3& vector);
	static float dot(const XMFLOAT3& vector1, const XMFLOAT3& vector2);
	static XMFLOAT3 normalize(const XMFLOAT3& vector);
	static float angle(const XMFLOAT3& vector1, const XMFLOAT3& vector2);
	static XMFLOAT3 multiplyMatrix(const XMFLOAT3& vector, const XMMATRIX& matrix);
};
