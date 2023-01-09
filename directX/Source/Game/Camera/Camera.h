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

	static const XMFLOAT3* trackingPosition;
	static const XMVECTOR* trackingRotation;
	static const XMFLOAT3 localPosition;
	static const XMFLOAT3 localFocus;

public:
	static XMFLOAT3 getPosition();
	static void setPosition(float x, float y, float z);
	static void addPosition(float x, float y, float z);
	static XMFLOAT3 getFocus();
	static void setFocus(float x, float y, float z);
	static void addFocus(float x, float y, float z);

	static void setTracking(const XMFLOAT3* position, const XMVECTOR* rotation);
	static void stopTracking();
	static void tracking();

	static XMMATRIX getWorldMatrix();
	static XMMATRIX getViewMatrix();
	static XMMATRIX getProjectionMatrix();

private:
	Camera() {}
};