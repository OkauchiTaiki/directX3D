#include "framework.h"
#include "Source\environment.h"

// �Q�[���̏����ݒ���s��
void GameSystem::initialize()
{
	Cube::initializeCommon();
	cube = new Cube(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
}

// ���̃Q�[���̎��Ԃ�i�߂�(���������s����)
void GameSystem::execute()
{
	//�t���[���̊J�n���Ԃ��Z�b�g
	frameRateManager.setStartCount();

	//��ʂƐ[�x�X�e���V���o�b�t�@�����Z�b�g
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), clearColor);
	D3D.m_deviceContext->ClearDepthStencilView(D3D.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	//-------------------------------------------
	//�Q�[���̓��e
	//-------------------------------------------
	{
		cube->rotateLocalAxisY(0.01f);
		cube->render();
	}


    // �o�b�N�o�b�t�@�̓��e����ʂɕ\��
    D3D.m_swapChain->Present(0, 0);

	//�w��̃t���[���ɂȂ�悤�ɑҋ@
	frameRateManager.stopTime();
}

void GameSystem::terminate()
{
	Cube::terminateCommon();
	delete cube;
}