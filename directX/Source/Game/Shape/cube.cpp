#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* Cube::pIndexBuffer = NULL;
ID3D11Buffer* Cube::pConstantBuffer = NULL;
ConstantBuffer Cube::constantBuffer = {};
UINT Cube::vertexStrides = sizeof(Vertex);
UINT Cube::vertexOffsets = 0;

const WORD Cube::indexList[36] = {
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
};

Cube::Cube(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color) : position(_position), size(_size)
{
	//変数の初期化
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;
	rotation = XMQuaternionIdentity();

	//頂点座標を設定
	setVertexPosition();

	//頂点カラーを設定
	changeColor(color);

	HRESULT hr;

	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// デバイスにバインドするときの種類(頂点バッファ、インデックスバッファ、定数バッファなど)
	vbDesc.ByteWidth = sizeof(Vertex) * vertexNum;	// 作成するバッファのバイトサイズ
	vbDesc.MiscFlags = 0;							// その他のフラグ
	vbDesc.StructureByteStride = 0;	                // 構造化バッファの場合、その構造体のサイズ
	vbDesc.Usage = D3D11_USAGE_DEFAULT;				// 作成するバッファの使用法
	vbDesc.CPUAccessFlags = 0;

	// 上の仕様を渡して頂点バッファを作ってもらう
	D3D11_SUBRESOURCE_DATA vbData = { vertex, 0, 0 };	// 書き込むデータ
	// 頂点バッファの作成
	hr = D3D.m_device->CreateBuffer(&vbDesc, &vbData, &pVertexBuffer);
	if (FAILED(hr)) assert(false);   //失敗するとダイアログが出る

	canExecute = true;
	canRender = true;
}

Cube::~Cube()
{
	SAFE_RELEASE(pVertexBuffer);
}

//静的共通データ初期化
bool Cube::initializeCommon()
{
	HRESULT hr;

	//定数バッファの初期化
	D3D11_BUFFER_DESC cbDesc = {};
	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	hr = D3D.m_device->CreateBuffer(&cbDesc, NULL, &pConstantBuffer);
	if (FAILED(hr))   return false;

	//定数バッファに値を入れる  
	XMMATRIX worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	XMVECTOR eye = XMVectorSet(0.0f, 0.0f, 5.0f, 0.0f);
	XMVECTOR focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);

	float    fov = DirectX::XMConvertToRadians(60.0f);
	float    aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	float    nearZ = 0.1f;
	float    farZ = 100.0f;
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	XMStoreFloat4x4(&constantBuffer.world, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&constantBuffer.view, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&constantBuffer.projection, XMMatrixTranspose(projMatrix));
	D3D.m_deviceContext->UpdateSubresource(pConstantBuffer, 0, NULL, &constantBuffer, 0, 0);

	//インデックスバッファの作成
	D3D11_BUFFER_DESC ibDesc = {};
    ibDesc.ByteWidth = sizeof(WORD) * 36;
    ibDesc.Usage = D3D11_USAGE_DEFAULT;
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibDesc.CPUAccessFlags = 0;
    ibDesc.MiscFlags = 0;
    ibDesc.StructureByteStride = 0;
    
    D3D11_SUBRESOURCE_DATA ibData = { indexList, 0, 0 };
    hr = D3D.m_device->CreateBuffer(&ibDesc, &ibData, &pIndexBuffer);
	if (FAILED(hr))   return false;

	return true;
}

//静的共通データ削除
void Cube::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
	SAFE_RELEASE(pConstantBuffer);
}

//処理
void Cube::execute()
{

}

//描画
void Cube::render()
{
	//頂点座標の設定
	setVertexPosition();

	//頂点バッファの更新
	D3D.m_deviceContext->UpdateSubresource(pVertexBuffer, 0, NULL, vertex, 0, 0);

	//頂点レイアウトをコンテキストに設定
	D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());
	//コンスタントバッファをコンテキストに設定
	D3D.m_deviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	//頂点バッファをコンテキストに設定
	D3D.m_deviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &vertexStrides, &vertexOffsets);
	//プリミティブ(ポリゴンの形状)をコンテキストに設定
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//シェーダーをコンテキストに設定
	D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
	D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);

	//描画コール
	D3D.m_deviceContext->DrawIndexed(36, 0, 0);
}

//実行状態の設定
void Cube::enableExecuting()
{
	canExecute = true;
}

void Cube::disableExecuting()
{
	canExecute = false;
}

//描画状態の設定
void Cube::enableRendering()
{
	canRender = true;
}

void Cube::disableRendering()
{
	canRender = false;
}

//描画状態と実行状態両方の設定
void Cube::enableAll()
{
	canExecute = true;
	canRender = true;
}

void Cube::disableAll()
{
	canExecute = false;
	canRender = false;
}

//実行状態の取得
bool Cube::isPossibleExecuting() const
{
	return canExecute;
}

//描画状態の取得
bool Cube::isPossibleRendering() const
{
	return canRender;
}

//色を変える
void Cube::changeColor(XMFLOAT4 color)
{
	for (int i = 0; i < vertexNum; i++)
	{
		vertex[i].color = color;
	}
}

//頂点データへの各種情報の設定
void Cube::setVertexPosition()
{
	//標準状態での各頂点の座標
	XMFLOAT3 vertexPosition[vertexNum]{
		{ (-size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z },
	    { (+size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z },
	    { (+size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z },
	    { (-size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z },
	    { (-size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z },
	    { (+size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z },
	    { (+size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z },
	    { (-size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z }
	};

	//回転を適用した座標を頂点データに入れる
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
	for (int i = 0; i < vertexNum; i++)
	{
		XMStoreFloat3(&vertexPosition[i], XMVector3Transform(XMLoadFloat3(&vertexPosition[i]), rotationMatrix));
		vertex[i].pos = vertexPosition[i];
	}
}