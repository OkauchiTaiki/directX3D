#include "framework.h"
#include "Source\environment.h"

// ゲームの初期設定を行う
void GameSystem::initialize()
{
	initializeShapes();
	rectAngle = new RectAngle(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(6.0f, 1.0f, 6.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	player = new Player(new Cube(XMFLOAT3(0.0f, 2.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
	sphere = new Sphere(XMFLOAT3(3.0f, 2.0f, 0.0f), 1.0f, XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	groundLines = new GroundLines();

	Camera::setTracking(&(player->appearance->position), player->getRotation());
}

// このゲームの時間を進める(処理を実行する)
void GameSystem::execute()
{
	//フレームの開始時間をセット
	frameRateManager.setStartCount();

	//画面と深度ステンシルバッファをリセット
	float clearColor[4] = { 0.53f, 0.42f, 0.38f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), clearColor);
	D3D.m_deviceContext->ClearDepthStencilView(D3D.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	//-------------------------------------------
	//ゲームの内容
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


    // バックバッファの内容を画面に表示
    D3D.m_swapChain->Present(0, 0);

	//指定のフレームになるように待機
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