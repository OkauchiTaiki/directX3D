#pragma once

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


	//Z値テクスチャ
	ComPtr<ID3D11Texture2D>        pRenderZTexture;
	ComPtr<ID3D11RenderTargetView> pRenderZTextureView;
	//Z値テクスチャ用の深度ステンシルバッファ
	ComPtr<ID3D11Texture2D>        pDepthStencilZTexture;
	ComPtr<ID3D11DepthStencilView> pDepthStencilZView;



	//--------------------------------------------
	// Direct3Dを初期化し、使用できるようにする関数
	// hWnd		: ウィンドウハンドル
	// width	: 画面の幅
	// height	: 画面の高さ
	//--------------------------------------------
	bool Initialize(HWND hWnd, int width, int height);
	void terminate();

	// 2D描画用のシェーダー
	ComPtr<ID3D11VertexShader>	m_spriteVS = nullptr;	// 頂点シェーダー
	ComPtr<ID3D11PixelShader>	m_spritePS = nullptr;	// ピクセルシェーダー
	ComPtr<ID3D11VertexShader>	m_lightVS = nullptr;	    // 光源込みの頂点シェーダー
	ComPtr<ID3D11VertexShader>	m_zVS = nullptr;	// Z値テクスチャ用の頂点シェーダー
	ComPtr<ID3D11PixelShader>	m_zPS = nullptr;	// Z値テクスチャ用のピクセルシェーダー
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
