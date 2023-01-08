#include "framework.h"
#include "Source\environment.h"

// �Q�[���̏����ݒ���s��
void GameSystem::initialize()
{
	initializeShapes();
	rectAngle = new RectAngle(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(6.0f, 1.0f, 6.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	cube = new Cube(XMFLOAT3(0.0f, 2.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	line1 = new Line(XMFLOAT3(0.0f, 0.0f, 0.0f), 100.0f, XMFLOAT4(0.6f, 0.6f, 0.6f, 0.6f));
	groundLines = new GroundLines();
}

// ���̃Q�[���̎��Ԃ�i�߂�(���������s����)
void GameSystem::execute()
{
	//�t���[���̊J�n���Ԃ��Z�b�g
	frameRateManager.setStartCount();

	//��ʂƐ[�x�X�e���V���o�b�t�@�����Z�b�g
	float clearColor[4] = { 0.53f, 0.42f, 0.38f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), clearColor);
	D3D.m_deviceContext->ClearDepthStencilView(D3D.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	//-------------------------------------------
	//�Q�[���̓��e
	//-------------------------------------------
	{
		cube->rotateLocalAxisY(0.01f);
		if (Keyboard::on(DIK_A))   cube->position.x -= 0.02f;
		if (Keyboard::on(DIK_D))   cube->position.x += 0.02f;
		Object::updateCommon();
		rectAngle->render();
		cube->render();
		//groundLines->render();
	}


    // �o�b�N�o�b�t�@�̓��e����ʂɕ\��
    D3D.m_swapChain->Present(0, 0);

	//�w��̃t���[���ɂȂ�悤�ɑҋ@
	frameRateManager.stopTime();
}

void GameSystem::terminate()
{
	terminateShapes();
	delete rectAngle;
	delete cube;
	delete line1;
	delete line2;
	delete groundLines;
}

void GameSystem::initializeShapes()
{
	Object::initializeCommon();
	RectAngle::initializeCommon();
	Cube::initializeCommon();
	Line::initializeCommon();
}

void GameSystem::terminateShapes()
{
	Object::terminateCommon();
	RectAngle::terminateCommon();
	Cube::terminateCommon();
	Line::terminateCommon();
}