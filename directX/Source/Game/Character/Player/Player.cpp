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

//�ʒu�̈ړ�
void Player::movePosition()
{
	//�ړ��x�N�g�������
	XMFLOAT3 worldMovingVector = {0.0f, 0.0f, 0.0f};

	if (Keyboard::on(DIK_W))   worldMovingVector.z += 0.02f;
	if (Keyboard::on(DIK_S))   worldMovingVector.z -= 0.02f;
	if (Keyboard::on(DIK_D))   worldMovingVector.x += 0.02f;
	if (Keyboard::on(DIK_A))   worldMovingVector.x -= 0.02f;
	if (Keyboard::on(DIK_Q))   worldMovingVector.y += 0.02f;
	if (Keyboard::on(DIK_E))   worldMovingVector.y -= 0.02f;

	//��̂܂܂��ƃ��[���h���W�ňړ����Ă��܂��̂Ń��[�J�����W�ɒ���
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
	XMFLOAT3 localMovingVector;
	XMStoreFloat3(&localMovingVector, XMVector3Transform(XMLoadFloat3(&worldMovingVector), rotationMatrix));

	appearance->position = appearance->position + localMovingVector;
}

//������ς���
void Player::changeViewPoint()
{
	//�}�E�X��x���̈ړ��ʂ����]������
	XMMATRIX rotationMatrixDX = XMMatrixMultiply(XMMatrixRotationQuaternion(rotation), XMMatrixRotationY((float)Mouse::getDX() / 300.0f));
	rotation = XMQuaternionRotationMatrix(rotationMatrixDX);

	//�}�E�X��y���̈ړ��ʂ����]������
	XMMATRIX rotationMatrixDY = XMMatrixMultiply(XMMatrixRotationX((float)Mouse::getDY() / 300.0f), XMMatrixRotationQuaternion(rotation));
	rotation = XMQuaternionRotationMatrix(rotationMatrixDY);
}

//�����ڂ̃A�j���[�V�����Ɖ�]�̔��f
void Player::updateAppearance()
{
	//z����]�̃A�j���[�V�����Ƃ���𔽉f����rotation�������ڂɔ��f
	rotationZ += 0.01f;
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
	XMMATRIX rotationMatrixZ = XMMatrixRotationZ(rotationZ);
	XMVECTOR rotationQuaternion = XMQuaternionRotationMatrix(XMMatrixMultiply(rotationMatrixZ, rotationMatrix));
	appearance->setRotation(rotationQuaternion);
}