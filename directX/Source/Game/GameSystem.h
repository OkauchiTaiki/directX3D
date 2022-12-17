#pragma once

//=========================================
// GameSystem�N���X
// �E���̃Q�[���̓y��ƂȂ����
//=========================================
class GameSystem
{
public:

	// ���̃Q�[���̏����ݒ���s��
	void initialize();

	// ���̃Q�[�����E�̎��Ԃ�i�߂�(���������s����)
	void execute();

	// ���̑��A�Q�[���p�̃f�[�^�Ȃǂ��R�R�ɏ���

//=========================================
// ���񂱂̃N���X���A�ǂ�����ł��A�N�Z�X�ł���悤��
// �V���O���g���p�^�[���ɂ��Ă����܂��B
// �������ȉ��A�V���O���g���p�^�[���̃R�[�h
//=========================================
private:
	// �B��̃C���X�^���X�p�̃|�C���^
	static inline GameSystem* s_instance;
	// �R���X�g���N�^��private�ɂ���
	GameSystem() {}
	float rotation = 0.0f;
public:
	// �C���X�^���X�쐬
	static void createInstance()
	{
		deleteInstance();

		s_instance = new GameSystem();
	}
	// �C���X�^���X�폜
	static void deleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	// �B��̃C���X�^���X���擾
	static GameSystem& getInstance()
	{
		return *s_instance;
	}
};

// GameSystem�̗B��̃C���X�^���X���ȒP�Ɏ擾���邽�߂̃}�N��
#define GAMESYS GameSystem::getInstance()