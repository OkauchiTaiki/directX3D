#include "framework.h"
#include "Source\environment.h"

bool Direct3D::Initialize(HWND hWnd, int width, int height)
{
	//=====================================================
	// ファクトリー作成(ビデオ グラフィックの設定の列挙や指定に使用されるオブジェクト)
	//=====================================================
	ComPtr<IDXGIFactory> factory;

	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
	{
		return false;
	}

	//=====================================================
	//デバイス生成(主にリソース作成時に使用するオブジェクト)
	//=====================================================
	UINT creationFlags = 0;

#ifdef _DEBUG
	// DEBUGビルド時はDirect3Dのデバッグを有効にする
	// (すごく重いが細かいエラーがわかる)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,	// Direct3D 11.1  ShaderModel 5
		D3D_FEATURE_LEVEL_11_0,	// Direct3D 11    ShaderModel 5
		D3D_FEATURE_LEVEL_10_1,	// Direct3D 10.1  ShaderModel 4
		D3D_FEATURE_LEVEL_10_0,	// Direct3D 10.0  ShaderModel 4
		D3D_FEATURE_LEVEL_9_3,	// Direct3D 9.3   ShaderModel 3
		D3D_FEATURE_LEVEL_9_2,	// Direct3D 9.2   ShaderModel 3
		D3D_FEATURE_LEVEL_9_1,	// Direct3D 9.1   ShaderModel 3
	};

	// デバイスとデバイスコンテキストを作成
	D3D_FEATURE_LEVEL futureLevel;
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&m_device,
		&futureLevel,
		&m_deviceContext)))
	{
		return false;
	}

	//=====================================================
	// スワップチェイン作成(フロントバッファに表示可能なバックバッファを持つもの)
	//=====================================================
	DXGI_SWAP_CHAIN_DESC scDesc = {};		// スワップチェーンの設定データ
	scDesc.BufferDesc.Width = width;						// 画面の幅
	scDesc.BufferDesc.Height = height;						// 画面の高さ
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バッファの形式
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scDesc.BufferDesc.RefreshRate.Numerator = 0;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.SampleDesc.Count = 1;							// MSAAは使用しない
	scDesc.SampleDesc.Quality = 0;							// MSAAは使用しない
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バッファの使用方法
	scDesc.BufferCount = 2;									// バッファの数
	scDesc.OutputWindow = hWnd;
	scDesc.Windowed = TRUE;									// ウィンドウモード
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// スワップチェインの作成
	if (FAILED(factory->CreateSwapChain(m_device.Get(), &scDesc, &m_swapChain)))
	{
		return false;
	}

	// スワップチェインからバックバッファリソース取得
	ComPtr<ID3D11Texture2D> pBackBuffer;
	if (FAILED(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer))))
	{
		return false;
	}

	// バックバッファリソース用のRTVを作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = scDesc.BufferDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	if (FAILED(m_device->CreateRenderTargetView(pBackBuffer.Get(), &rtvDesc, &m_backBufferView)))
	{
		return false;
	}

	//深度ステンシルバッファを作成
	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = (UINT)width;
	txDesc.Height = (UINT)height;
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = 0;
	txDesc.MiscFlags = 0;

	m_device->CreateTexture2D(&txDesc, NULL, &pDepthStencilTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;

	m_device->CreateDepthStencilView(pDepthStencilTexture.Get(), &dsDesc, &pDepthStencilView);

	//-----------------------------------------------------
	//Z値テクスチャもろもろ
	//-----------------------------------------------------
	//深度データを書き込むテクスチャを生成
	//D3D11_TEXTURE2D_DESC renderZTextureDesc;
	//renderZTextureDesc.Width = (UINT)width;
	//renderZTextureDesc.Height = (UINT)height;
	//renderZTextureDesc.MipLevels = 1;
	//renderZTextureDesc.ArraySize = 1;
	//renderZTextureDesc.Format = DXGI_FORMAT_R32_FLOAT;
	//renderZTextureDesc.SampleDesc.Count = 1;
	//renderZTextureDesc.SampleDesc.Quality = 0;
	//renderZTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	//renderZTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	//renderZTextureDesc.CPUAccessFlags = 0;
	//renderZTextureDesc.MiscFlags = 0;
	//if (FAILED(m_device->CreateTexture2D(&renderZTextureDesc, NULL, &pRenderZTexture)))
	//{
	//	return false;
	//}
	//// テクスチャをレンダリングターゲットとして扱う為のインターフェースを生成
	//// (深度データを書き込む為)
	//if (FAILED(m_device->CreateRenderTargetView(pRenderZTexture.Get(), nullptr, &pRenderZTextureView)))
	//{
	//	return false;
	//}

	//// 深度データのレンダリングに使う深度バッファ(ややこしい)
	//// こいつをShader resourceとして使う方法があれば単純化出来るかも？
	//D3D11_TEXTURE2D_DESC depthTextureDesc;
	//depthTextureDesc.Width = (UINT)width;
	//depthTextureDesc.Height = (UINT)height;
	//depthTextureDesc.MipLevels = 1;
	//depthTextureDesc.ArraySize = 1;
	//depthTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	//depthTextureDesc.SampleDesc.Count = 1;
	//depthTextureDesc.SampleDesc.Quality = 0;
	//depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	//depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//depthTextureDesc.CPUAccessFlags = 0;
	//depthTextureDesc.MiscFlags = 0;

	//if (FAILED(m_device->CreateTexture2D(&depthTextureDesc, nullptr, pDepthStencilZTexture.GetAddressOf())))
	//{
	//	return false;
	//}

	//// 深度ステンシルビューの作成
	//D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	//depthStencilViewDesc.Format = depthTextureDesc.Format;
	//depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	//depthStencilViewDesc.Flags = 0;

	//if (FAILED(m_device->CreateDepthStencilView(pDepthStencilZTexture.Get(), &depthStencilViewDesc, pDepthStencilZView.GetAddressOf())))
	//{
	//	return false;
	//}

	//=====================================================
	// デバイスコンテキストに描画に関する設定を行っておく
	//=====================================================

	// ビューポートの設定
	D3D11_VIEWPORT vp = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f };
	m_deviceContext->RSSetViewports(1, &vp);

	//=====================================================
	// シェーダーの作成
	//=====================================================
	// 頂点シェーダーを読み込み＆コンパイル
	ComPtr<ID3DBlob> compiledVS;
	if (FAILED(D3DCompileFromFile(L"Shader/SpriteShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compiledVS, nullptr)))
	{
		return false;
	}
	// ピクセルシェーダーを読み込み＆コンパイル
	ComPtr<ID3DBlob> compiledPS;
	if (FAILED(D3DCompileFromFile(L"Shader/SpriteShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compiledPS, nullptr)))
	{
		return false;
	}
	// 頂点シェーダー作成
	if (FAILED(m_device->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &m_spriteVS)))
	{
		return false;
	}
	// ピクセルシェーダー作成
	if (FAILED(m_device->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &m_spritePS)))
	{
		return false;
	}

	// 光源込み
	// 頂点シェーダーを読み込み＆コンパイル
	if (FAILED(D3DCompileFromFile(L"Shader/SpriteShader.hlsl", nullptr, nullptr, "LVS", "vs_5_0", 0, 0, &compiledVS, nullptr)))
	{
		return false;
	}
	// 頂点シェーダー作成
	if (FAILED(m_device->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &m_lightVS)))
	{
		return false;
	}

	//Z値テクスチャ用のシェーダー
	//// 頂点シェーダーを読み込み＆コンパイル
	//if (FAILED(D3DCompileFromFile(L"Shader/ZTextureShader.hlsl", nullptr, nullptr, "ZVS", "vs_5_0", 0, 0, &compiledVS, nullptr)))
	//{
	//	return false;
	//}
	//// ピクセルシェーダーを読み込み＆コンパイル
	//if (FAILED(D3DCompileFromFile(L"Shader/ZTextureShader.hlsl", nullptr, nullptr, "ZPS", "ps_5_0", 0, 0, &compiledPS, nullptr)))
	//{
	//	return false;
	//}
	//// 頂点シェーダー作成
	//if (FAILED(m_device->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &m_zVS)))
	//{
	//	return false;
	//}
	//// ピクセルシェーダー作成
	//if (FAILED(m_device->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &m_zPS)))
	//{
	//	return false;
	//}

	// １頂点の詳細な情報
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// 頂点インプットレイアウト作成
	if (FAILED(m_device->CreateInputLayout(layout, ARRAYSIZE(layout), compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &m_spriteInputLayout)))
	{
		return false;
	}

	return true;
}

void Direct3D::terminate()
{

}