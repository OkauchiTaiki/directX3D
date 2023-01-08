#pragma once

class Camera
{
private:
	static const XMFLOAT3 worldTranslation;
	static const XMVECTOR worldRotation;
	static const XMFLOAT3 worldScale;

	static XMFLOAT3 position;
	static XMFLOAT3 focus;
	static const XMFLOAT3 up;

	static const float fov;
	static const float aspect;
    static const float nearZ;
	static const float farZ;

public:
	static XMFLOAT3 getPosition();
	static void setPosition(float x, float y, float z);
	static void addPosition(float x, float y, float z);
	static XMFLOAT3 getFocus();
	static void setFocus(float x, float y, float z);

	static XMMATRIX getWorldMatrix();
	static XMMATRIX getViewMatrix();
	static XMMATRIX getProjectionMatrix();

private:
	Camera() {}
};