#include "framework.h"
#include "Source\environment.h"

Player::Player(Cube* _appearance) : appearance(_appearance)
{

}

Player::~Player()
{
	delete appearance;
}

const XMVECTOR* Player::getRotation() const
{
	return &rotation;
}

//位置の移動
void Player::movePosition()
{
	//移動ベクトルを作る
	XMFLOAT3 worldMovingVector = {0.0f, 0.0f, 0.0f};

	if (Keyboard::on(DIK_W))   worldMovingVector.z += 0.02f;
	if (Keyboard::on(DIK_S))   worldMovingVector.z -= 0.02f;
	if (Keyboard::on(DIK_D))   worldMovingVector.x += 0.02f;
	if (Keyboard::on(DIK_A))   worldMovingVector.x -= 0.02f;
	if (Keyboard::on(DIK_Q))   worldMovingVector.y += 0.02f;
	if (Keyboard::on(DIK_E))   worldMovingVector.y -= 0.02f;

	//上のままだとワールド座標で移動してしまうのでローカル座標に直す
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
	XMFLOAT3 localMovingVector;
	XMStoreFloat3(&localMovingVector, XMVector3Transform(XMLoadFloat3(&worldMovingVector), rotationMatrix));

	appearance->position = appearance->position + localMovingVector;
}

//向きを変える
void Player::changeViewPoint()
{
	//マウスのx軸の移動量から回転させる
	XMMATRIX rotationMatrixDX = XMMatrixMultiply(XMMatrixRotationQuaternion(rotation), XMMatrixRotationY((float)Mouse::getDX() / 300.0f));
	rotation = XMQuaternionRotationMatrix(rotationMatrixDX);

	//マウスのy軸の移動量から回転させる
	XMMATRIX rotationMatrixDY = XMMatrixMultiply(XMMatrixRotationX((float)Mouse::getDY() / 300.0f), XMMatrixRotationQuaternion(rotation));
	rotation = XMQuaternionRotationMatrix(rotationMatrixDY);
}

//見た目のアニメーションと回転の反映
void Player::updateAppearance()
{
	//z軸回転のアニメーションとそれを反映したrotationを見た目に反映
	rotationZ += 0.01f;
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
	XMMATRIX rotationMatrixZ = XMMatrixRotationZ(rotationZ);
	XMVECTOR rotationQuaternion = XMQuaternionRotationMatrix(XMMatrixMultiply(rotationMatrixZ, rotationMatrix));
	appearance->setRotation(rotationQuaternion);
}