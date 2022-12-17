#include "framework.h"
// GameSystemクラスを使えるようにする
#include "GameSystem.h"
// Direct3Dクラスを使えるようにする
#include "Source/DirectX/Direct3D.h"

// ゲームの初期設定を行う
void GameSystem::initialize()
{
	//吉永太洋です！
	//岡内大樹です！
	// 武井ヤマトです！
	//お尻
}

// このゲームの時間を進める(処理を実行する)
void GameSystem::execute()
{
    // 画面を青色で塗りつぶす
    /*float color[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
    D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);*/

	// 三角形の描画
	{
		// １頂点の形式(今回は座標だけ)
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;	// 座標
			float color[4];	// 色
		};
		Vertex vertexCube[36] = {
			 { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	         { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	         { { -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			 { { -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			 { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			 { {  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	         
	         { {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	         { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	         { {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			 { {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			 { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			 { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	         
	         { { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	         { { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	         { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
			 { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
			 { { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
			 { { -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	         
	         { {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	         { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	         { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	         
	         { { -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	         { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	         { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
			 { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	         
	         { { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	         { {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	         { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			 { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			 { {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			 { {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		};

		DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotation);
		for (int i = 0; i < 36; i++)
		{
			DirectX::XMStoreFloat3(&vertexCube[i].pos, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&vertexCube[i].pos), rotationMatrix));
		}
		rotation += 0.001f;

		/*WORD g_IndexList[]{
	         0,  1,  2,     3,  2,  1,
	         4,  5,  6,     7,  6,  5,
	         8,  9, 10,    11, 10,  9,
	        12, 13, 14,    15, 14, 13,
	        16, 17, 18,    19, 18, 17,
	        20, 21, 22,    23, 22, 21,
		};*/

		struct ConstantBuffer {
			DirectX::XMFLOAT4X4 world;
			DirectX::XMFLOAT4X4 view;
			DirectX::XMFLOAT4X4 projection;
		};

		//深度ステンシルバッファ作成
		D3D11_TEXTURE2D_DESC txDesc;
		ZeroMemory(&txDesc, sizeof(txDesc));
		txDesc.Width = 1280;
		txDesc.Height = 720;
		txDesc.MipLevels = 1;
		txDesc.ArraySize = 1;
		txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		txDesc.SampleDesc.Count = 1;
		txDesc.SampleDesc.Quality = 0;
		txDesc.Usage = D3D11_USAGE_DEFAULT;
		txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		txDesc.CPUAccessFlags = 0;
		txDesc.MiscFlags = 0;

		ID3D11Texture2D* m_depthStencilTexture;
		D3D.m_device->CreateTexture2D(&txDesc, NULL, &m_depthStencilTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(dsDesc));
		dsDesc.Format = txDesc.Format;
		dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsDesc.Texture2D.MipSlice = 0;

		ID3D11DepthStencilView* m_depthStencilView;
		D3D.m_device->CreateDepthStencilView(m_depthStencilTexture, &dsDesc, &m_depthStencilView);

		//-----------------------------
		// 頂点バッファ作成
		// ・上記で作った３つの頂点はそのままでは描画に使用できないんす…
		// ・ビデオメモリ側に「頂点バッファ」という形で作る必要があります！
		// ・今回は効率無視して、その場で作って、使って、すぐ捨てます。
		//-----------------------------
		// 作成するバッファの仕様を決める
		// ・今回は頂点バッファにするぞ！って感じの設定
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// デバイスにバインドするときの種類(頂点バッファ、インデックスバッファ、定数バッファなど)
		vbDesc.ByteWidth = sizeof(Vertex) * 36;			// 作成するバッファのバイトサイズ
		vbDesc.MiscFlags = 0;							// その他のフラグ
		vbDesc.StructureByteStride = 0;	                // 構造化バッファの場合、その構造体のサイズ
		vbDesc.Usage = D3D11_USAGE_DEFAULT;				// 作成するバッファの使用法
		vbDesc.CPUAccessFlags = 0;

		// 上の仕様を渡して頂点バッファを作ってもらう
		// もちろんデバイスさんにお願いする
		ID3D11Buffer* vb;
		D3D11_SUBRESOURCE_DATA vbData = { vertexCube, 0, 0 };	// 書き込むデータ
		// 頂点バッファの作成
		D3D.m_device->CreateBuffer(&vbDesc, &vbData, &vb);

		//---------------------------
		//インデックスバッファ
		//--------------------------
		/*D3D11_BUFFER_DESC ibDesc = {};
		ibDesc.ByteWidth = sizeof(WORD) * 6 * 6;
		ibDesc.Usage = D3D11_USAGE_DEFAULT;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;

		ID3D11Buffer* ib;
		D3D11_SUBRESOURCE_DATA ibData = { g_IndexList, 0, 0 };
		D3D.m_device->CreateBuffer(&ibDesc, &ibData, &ib);*/

		//-----------------------------------
		//定数バッファ
		//----------------------------------
		D3D11_BUFFER_DESC cbDesc = {};
		cbDesc.ByteWidth = sizeof(ConstantBuffer);
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;

		ID3D11Buffer* constantBuffer;
		D3D.m_device->CreateBuffer(&cbDesc, NULL, &constantBuffer);

		//定数バッファに値を入れる
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

		DirectX::XMVECTOR eye = DirectX::XMVectorSet(-4.0f, -4.0f, -4.0f, 0.0f);
		DirectX::XMVECTOR focus = DirectX::XMVectorSet(0.0f, 0.0f, 0.5f, 0.0f);
		DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(eye, focus, up);

		float    fov = DirectX::XMConvertToRadians(45.0f);
		float    aspect = 1280.0f / 720.0f;
		float    nearZ = 0.1f;
		float    farZ = 100.0f;
		DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

		ConstantBuffer cb;
		XMStoreFloat4x4(&cb.world, XMMatrixTranspose(worldMatrix));
		XMStoreFloat4x4(&cb.view, XMMatrixTranspose(viewMatrix));
		XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(projMatrix));
		D3D.m_deviceContext->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);

		//++++++++++++++++++++ ここから描画していきます ++++++++++++++++++++

		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
		// ここからは「描画の職人」デバイスコンテキストくんが大活躍

		// 頂点バッファを描画で使えるようにセットする
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());
		D3D.m_deviceContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
		//D3D.m_deviceContext->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);
		// プロミティブ・トポロジーをセット
		D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		D3D.m_deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
		D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), clearColor);
		D3D.m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//-----------------------------
		// シェーダーをセット
		//-----------------------------
		D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
		D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);

		// こんな感じで、ひたすらデバイスコンテキストに情報を渡す

		//-----------------------------
		// 描画実行
		//-----------------------------
		// デバイスコンテキストくん、上記のセットした内容で描画してください、とお願いする
		D3D.m_deviceContext->Draw(36, 0);
		vb->Release();
		constantBuffer->Release();
		m_depthStencilTexture->Release();
		m_depthStencilView->Release();
	}

    // バックバッファの内容を画面に表示
    D3D.m_swapChain->Present(0, 0);
}