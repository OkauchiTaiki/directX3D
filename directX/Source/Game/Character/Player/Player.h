#pragma once

class Player
{
public:
	Player(Cube* _appearance);
	~Player();

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
	//������ς���
	void changeViewPoint();
	
	//�����ڂ̃A�j���[�V�����Ɖ�]�̔��f
	void updateAppearance();
};
