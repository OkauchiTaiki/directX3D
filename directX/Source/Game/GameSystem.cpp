#include "framework.h"
#include "Source\environment.h"

// �Q�[���̏����ݒ���s��
void GameSystem::initialize()
{
	initializeShapes();
	rectAngle = new RectAngle(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(6.0f, 1.0f, 6.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	player = new Player(new Cube(XMFLOAT3(0.0f, 2.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
	sphere = new Sphere(XMFLOAT3(3.0f, 2.0f, 0.0f), 1.0f, XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	groundLines = new GroundLines();

	Camera::setTracking(&(player->appearance->position), player->getRotation());
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
		//cube->rotateLocalAxisZ(0.01f);
		player->movePosition();
		player->changeViewPoint();
		player->updateAppearance();

		Camera::tracking();

		Object::updateCommon();
		rectAngle->render();
		player->appearance->render();
		sphere->render();
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
	delete player;
	delete sphere;
	delete groundLines;
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