#pragma once

//=========================================
// GameSystem�N���X
// �E���̃Q�[���̓y��ƂȂ����
//=========================================
class GameSystem
{
private:
	//��ʂ��N���A����F
	static const float clearColor[4];
	//�t���[�����[�g���Œ�ɂ��邽�߂̃N���X
	FrameRateManager frameRateManager = {};
	//�Q�[���V�[��
	GameScene* gameScene = nullptr;

public:

	// ���̃Q�[���̏����ݒ���s��
	bool initialize(HWND hWnd, HINSTANCE hInst);

	// ���̃Q�[�����E�̎��Ԃ�i�߂�(���������s����)
	void execute();

	//�I������
	void terminate();

private:
	void initializeShapes();
	void terminateShapes();

//=========================================
//�V���O���g���p�^�[��
//=========================================
private:
	// �B��̃C���X�^���X�p�̃|�C���^
	static inline GameSystem* s_instance;
	// �R���X�g���N�^��private�ɂ���
	GameSystem() {}

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