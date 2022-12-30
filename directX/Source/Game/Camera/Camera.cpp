#include "framework.h"
#include "Source\environment.h"

const XMFLOAT3 Camera::worldTranslation = { 0.0f, 0.0f, 0.0f };
const XMVECTOR Camera::worldRotation = XMQuaternionIdentity();
const XMFLOAT3 Camera::worldScale = { 1.0f, 1.0f, 1.0f };

XMFLOAT3 Camera::position = { 0.0f, 5.0f, -5.0f };
XMFLOAT3 Camera::focus = { 0.0f, 1.0f, 0.0f };
const XMFLOAT3 Camera::up = { 0.0f, 1.0f, 0.0f };

const float Camera::fov = PI / 3.0f;
const float Camera::aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
const float Camera::nearZ = 0.1f;
const float Camera::farZ = 100.0f;

XMVECTOR Camera::getPosition()
{
	return XMLoadFloat3(&position);
}

void Camera::setPosition(float x, float y, float z)
{
	position = { x, y, z };
}

XMVECTOR Camera::getFocus()
{
	return XMLoadFloat3(&focus);
}

void Camera::setFocus(float x, float y, float z)
{
	focus = { x, y, z };
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