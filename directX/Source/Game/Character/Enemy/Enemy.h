#pragma once

class Enemy
{
public:
	Enemy(Cube* _appearance);
	~Enemy();

	//������
	Cube* appearance;

private:
	//Z����]�̃A�j���[�V�����𖳎������N�H�[�^�j�I��
	XMVECTOR rotation = XMQuaternionIdentity();
	//Z����]�̗�
	float rotationZ = 0.0f;

public:
	const XMVECTOR* getRotation() const;

	//�ʒu�̈ړ�
	void movePosition();

	//��������Ă���̃t���[���@�J�E���g
	int count;
};
