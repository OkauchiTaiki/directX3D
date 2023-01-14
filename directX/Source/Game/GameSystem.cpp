#include "framework.h"
#include "Source\environment.h"

const float GameSystem::clearColor[4] = { 0.53f, 0.42f, 0.38f, 1.0f };

// ゲームの初期設定を行う
bool GameSystem::initialize(HWND hWnd, HINSTANCE hInst)
{
	//各コンポーネントの初期化
	D3D.Initialize(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	DirectInput::initialize(hInst);

	initializeShapes();

	gameScene = new GameScene();
	gameScene->initialize();

	return true;
}

// このゲームの時間を進める(処理を実行する)
void GameSystem::execute()
{
	//フレームの開始時間をセット
	frameRateManager.setStartCount();

	//キー入力、マウス入力の結果をセット
	DirectInput::KeyManager();

	//ゲームの処理
	gameScene->execute();

	//レンダーターゲットをセット
	D3D.m_deviceContext->OMSetRenderTargets(1, D3D.m_backBufferView.GetAddressOf(), D3D.pDepthStencilView.Get());
	//レンダーターゲットビューと深度ステンシルバッファをクリア
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), clearColor);
	D3D.m_deviceContext->ClearDepthStencilView(D3D.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Z値テクスチャ
	//D3D.m_deviceContext->OMSetRenderTargets(1, D3D.pRenderZTextureView.GetAddressOf(), D3D.pDepthStencilZView.Get());
	////レンダーターゲットビューと深度ステンシルバッファをクリア
	//D3D.m_deviceContext->ClearRenderTargetView(D3D.pRenderZTextureView.Get(), clearColor);
	//D3D.m_deviceContext->ClearDepthStencilView(D3D.pDepthStencilZView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//オブジェクトの描画
	gameScene->render();

    // バックバッファの内容を画面に表示
    D3D.m_swapChain->Present(0, 0);

	//指定のフレームになるように待機
	frameRateManager.stopTime();
}

void GameSystem::terminate()
{
	gameScene->terminate();
	delete gameScene;

	//各コンポーネントの終了
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