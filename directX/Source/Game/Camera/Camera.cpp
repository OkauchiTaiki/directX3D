#include "framework.h"
#include "Source\environment.h"

const XMFLOAT3 Camera::worldTranslation = { 0.0f, 0.0f, 0.0f };
const XMVECTOR Camera::worldRotation = XMQuaternionIdentity();
const XMFLOAT3 Camera::worldScale = { 1.0f, 1.0f, 1.0f };

XMFLOAT3 Camera::position = { 0.0f, 5.0f, -5.0f };
XMFLOAT3 Camera::focus = { 0.0f, 1.0f, 0.0f };
const XMFLOAT3 Camera::defaultUp = { 0.0f, 1.0f, 0.0f };
XMFLOAT3 Camera::up = { 0.0f, 1.0f, 0.0f };

const float Camera::fov = PI / 3.0f;
const float Camera::aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
const float Camera::nearZ = 0.1f;
const float Camera::farZ = 100.0f;

const XMFLOAT3* Camera::trackingPosition = nullptr;
const XMVECTOR* Camera::trackingRotation = nullptr;
const XMFLOAT3 Camera::localPosition = { 0.0f, 2.0f, -5.0f };
const XMFLOAT3 Camera::localFocus = { 0.0f, 1.0f, 0.0f };

XMFLOAT3 Camera::getPosition()
{
	return position;
}

void Camera::setPosition(float x, float y, float z)
{
	position = { x, y, z };
}

void Camera::addPosition(float x, float y, float z)
{
	position = position + XMFLOAT3(x, y, z);
}

XMFLOAT3 Camera::getFocus()
{
	return focus;
}

void Camera::setFocus(float x, float y, float z)
{
	focus = { x, y, z };
}

void Camera::addFocus(float x, float y, float z)
{
	focus = focus + XMFLOAT3(x, y, z);
}

void Camera::setTracking(const XMFLOAT3* position, const XMVECTOR* rotation)
{
	trackingPosition = position;
	trackingRotation = rotation;
}

void Camera::stopTracking()
{
	trackingPosition = nullptr;
	trackingRotation = nullptr;
}

void Camera::tracking()
{
	if (trackingPosition == nullptr)   return;
	if (trackingRotation == nullptr)   return;

	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(*trackingRotation);
	//位置
	XMFLOAT3 localPos;
	XMStoreFloat3(&localPos, XMVector3Transform(XMLoadFloat3(&localPosition), rotationMatrix));
	position = *trackingPosition + localPos;
	//焦点
	XMFLOAT3 localFoc;
	XMStoreFloat3(&localFoc, XMVector3Transform(XMLoadFloat3(&localFocus), rotationMatrix));
	focus = *trackingPosition + localFoc;
	//カメラの上方向ベクトル
	XMStoreFloat3(&up, XMVector3Transform(XMLoadFloat3(&defaultUp), rotationMatrix));
}


XMMATRIX Camera::getWorldMatrix()
{
	XMMATRIX worldMatrix = XMMatrixScaling(worldScale.x, worldScale.y, worldScale.z);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationQuaternion(worldRotation));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(worldTranslation.x, worldTranslation.y, worldTranslation.z));
	return worldMatrix;
}

XMMATRIX Camera::getViewMatrix()
{
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&focus), XMLoadFloat3(&up));
	return viewMatrix;
}

XMMATRIX Camera::getProjectionMatrix()
{
	XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);
	return projectionMatrix;
}