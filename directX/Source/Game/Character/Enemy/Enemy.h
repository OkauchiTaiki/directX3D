#pragma once

class Enemy
{
public:
	Enemy(Cube* _appearance);
	~Enemy();

	//������
	Cube* appearance;

private:
	//��������Ă���̃t���[���@�J�E���g
	int count = 0;

	//���X�|�[���֌W
	static const int respawnFrame = 40;
	int respawnFrameCount = 0;
	XMFLOAT3 respawnPosition{};

public:
	//�ʒu�̈ړ�
	void movePosition();
	
	void die();

	void checkRespawn();
	void respawn();
};
