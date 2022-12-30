#pragma once

// Direct3Dのライブラリを使用できるようにする
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// Direct3Dの型・クラス・関数などを呼べるようにする
#include <d3d11.h>
#include <d3dcompiler.h>

// DirectXMath(数学ライブラリ)を使用できるようにする
#include <DirectXMath.h>

//DirectXのネームスペース
using namespace DirectX;

//リリース
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}

// ComPtrを使用できるようにする
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

//=========================================
// Direct3Dクラス
//=========================================
class Direct3D
{
public:

	// ※変数は今回は全てpublicにしますが、本来はprivateで隠すべき※

	// Direct3Dデバイス
	ComPtr<ID3D11Device>		m_device;
	// Direct3Dデバイスコンテキスト
	ComPtr<ID3D11DeviceContext>	m_deviceContext;
	// スワップチェイン
	ComPtr<IDXGISwapChain>		m_swapChain;
	// バックバッファーのRTビュー
	ComPtr<ID3D11RenderTargetView> m_backBufferView;
	//深度ステンシルバッファ
	ComPtr<ID3D11Texture2D>        pDepthStencilTexture;
	ComPtr<ID3D11DepthStencilView> pDepthStencilView;

	//--------------------------------------------
	// Direct3Dを初期化し、使用できるようにする関数
	// hWnd		: ウィンドウハンドル
	// width	: 画面の幅
	// height	: 画面の高さ
	//--------------------------------------------
	bool Initialize(HWND hWnd, int width, int height);

	// 2D描画用のシェーダー
	ComPtr<ID3D11VertexShader>	m_spriteVS = nullptr;	// 頂点シェーダー
	ComPtr<ID3D11PixelShader>	m_spritePS = nullptr;	// ピクセルシェーダー
	ComPtr<ID3D11VertexShader>	m_lightVS = nullptr;	    // 光源込みの頂点シェーダー
	ComPtr<ID3D11InputLayout>	m_spriteInputLayout = nullptr;    // 入力レイアウト

	//=========================================
	// 今回このクラスは、どこからでもアクセスできるように
	// シングルトンパターンにします
	// ↓↓↓以下、シングルトンパターンのコード
	//=========================================
private:
	// 唯一のインスタンス用のポインタ
	static inline Direct3D* s_instance;
	// コンストラクタはprivateにする
	Direct3D() {}
public:
	// インスタンス作成
	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new Direct3D();
	}
	// インスタンス削除
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	// 唯一のインスタンスを取得
	static Direct3D& GetInstance()
	{
		return *s_instance;
	}
};

// Direct3Dの唯一のインスタンスを簡単に取得するためのマクロ
#define D3D Direct3D::GetInstance()
