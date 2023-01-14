#include "framework.h"
#include "Source\environment.h"

const float GameSystem::clearColor[4] = { 0.53f, 0.42f, 0.38f, 1.0f };

// �Q�[���̏����ݒ���s��
bool GameSystem::initialize(HWND hWnd, HINSTANCE hInst)
{
	//�e�R���|�[�l���g�̏�����
	D3D.Initialize(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	DirectInput::initialize(hInst);

	initializeShapes();

	gameScene = new GameScene();
	gameScene->initialize();

	return true;
}

// ���̃Q�[���̎��Ԃ�i�߂�(���������s����)
void GameSystem::execute()
{
	//�t���[���̊J�n���Ԃ��Z�b�g
	frameRateManager.setStartCount();

	//�L�[���́A�}�E�X���͂̌��ʂ��Z�b�g
	DirectInput::KeyManager();

	//�Q�[���̏���
	gameScene->execute();

	//�����_�[�^�[�Q�b�g���Z�b�g
	D3D.m_deviceContext->OMSetRenderTargets(1, D3D.m_backBufferView.GetAddressOf(), D3D.pDepthStencilView.Get());
	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���o�b�t�@���N���A
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), clearColor);
	D3D.m_deviceContext->ClearDepthStencilView(D3D.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Z�l�e�N�X�`��
	//D3D.m_deviceContext->OMSetRenderTargets(1, D3D.pRenderZTextureView.GetAddressOf(), D3D.pDepthStencilZView.Get());
	////�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���o�b�t�@���N���A
	//D3D.m_deviceContext->ClearRenderTargetView(D3D.pRenderZTextureView.Get(), clearColor);
	//D3D.m_deviceContext->ClearDepthStencilView(D3D.pDepthStencilZView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//�I�u�W�F�N�g�̕`��
	gameScene->render();

    // �o�b�N�o�b�t�@�̓��e����ʂɕ\��
    D3D.m_swapChain->Present(0, 0);

	//�w��̃t���[���ɂȂ�悤�ɑҋ@
	frameRateManager.stopTime();
}

void GameSystem::terminate()
{
	gameScene->terminate();
	delete gameScene;

	//�e�R���|�[�l���g�̏I��
	DirectInput::terminate();
	D3D.terminate();

	terminateShapes();
}

void GameSystem::initializeShapes()
{
	Object::initializeCommon();
	RectAngle::initializeCommon();
	Cube::initializeCommon();
	Line::initializeCommon();
	Sphere::initializeCommon();
}

void GameSystem::terminateShapes()
{
	Object::terminateCommon();
	RectAngle::terminateCommon();
	Cube::terminateCommon();
	Line::terminateCommon();
	Sphere::terminateCommon();
}