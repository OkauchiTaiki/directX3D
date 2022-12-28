#include "framework.h"
#include "Source\environment.h"

// ゲームの初期設定を行う
void GameSystem::initialize()
{
	Cube::initializeCommon();
	cube = new Cube(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
}

// このゲームの時間を進める(処理を実行する)
void GameSystem::execute()
{
	//フレームの開始時間をセット
	frameRateManager.setStartCount();

	//画面と深度ステンシルバッファをリセット
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), clearColor);
	D3D.m_deviceContext->ClearDepthStencilView(D3D.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	//-------------------------------------------
	//ゲームの内容
	//-------------------------------------------
	{
		cube->rotateLocalAxisY(0.01f);
		cube->render();
	}


    // バックバッファの内容を画面に表示
    D3D.m_swapChain->Present(0, 0);

	//指定のフレームになるように待機
	frameRateManager.stopTime();
}

void GameSystem::terminate()
{
	Cube::terminateCommon();
	delete cube;
}