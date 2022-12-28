#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* Shape::pConstantBuffer = NULL;
ConstantBuffer Shape::constantBuffer = {};
UINT Shape::vertexStrides = sizeof(Vertex);
UINT Shape::vertexOffsets = 0;

Shape::Shape(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color, int vertexNum) : position(_position), size(_size)
{
	vertex.resize(vertexNum);

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;
	rotation = XMQuaternionIdentity();

	//頂点カラーを設定
	changeColor(color);

	//頂点バッファ
	HRESULT hr;

	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// デバイスにバインドするときの種類(頂点バッファ、インデックスバッファ、定数バッファなど)
	vbDesc.ByteWidth = sizeof(Vertex) * vertexNum;	// 作成するバッファのバイトサイズ
	vbDesc.MiscFlags = 0;							// その他のフラグ
	vbDesc.StructureByteStride = 0;	                // 構造化バッファの場合、その構造体のサイズ
	vbDesc.Usage = D3D11_USAGE_DEFAULT;				// 作成するバッファの使用法
	vbDesc.CPUAccessFlags = 0;

	// 上の仕様を渡して頂点バッファを作ってもらう
	D3D11_SUBRESOURCE_DATA vbData = { &vertex[0], 0, 0 };	// 書き込むデータ
	// 頂点バッファの作成
	hr = D3D.m_device->CreateBuffer(&vbDesc, &vbData, &pVertexBuffer);
	if (FAILED(hr)) assert(false);   //失敗するとダイアログが出る

	canExecute = true;
	canRender = true;
}

Shape::~Shape()
{
	SAFE_RELEASE(pVertexBuffer);
}

//静的共通データ初期化
bool Shape::initializeCommon()
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

	XMVECTOR eye = XMVectorSet(0.0f, 5.0f, 6.0f, 0.0f);
	XMVECTOR focus = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);

	float    fov = DirectX::XMConvertToRadians(60.0f);
	float    aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	float    nearZ = 0.1f;
	float    farZ = 100.0f;
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	XMStoreFloat4x4(&constantBuffer.world, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&constantBuffer.view, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&constantBuffer.projection, XMMatrixTranspose(projMatrix));
	D3D.m_deviceContext->UpdateSubresource(pConstantBuffer, 0, NULL, &constantBuffer, 0, 0);

	return true;
}

//静的共通データ削除
void Shape::terminateCommon()
{
	SAFE_RELEASE(pConstantBuffer);
}

//処理
void Shape::execute()
{

}

//描画
void Shape::render()
{
	//頂点座標の設定
	setVertexPosition();

	//頂点バッファの更新
	D3D.m_deviceContext->UpdateSubresource(pVertexBuffer, 0, NULL, &vertex[0], 0, 0);

	//頂点レイアウトをコンテキストに設定
	D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());
	//コンスタントバッファをコンテキストに設定
	D3D.m_deviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	//頂点バッファをコンテキストに設定
	D3D.m_deviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &vertexStrides, &vertexOffsets);
	//インデックスバッファをコンテキストに設定
	D3D.m_deviceContext->IASetIndexBuffer(getIndexBuffer(), DXGI_FORMAT_R16_UINT, 0);
	//プリミティブ(ポリゴンの形状)をコンテキストに設定
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//シェーダーをコンテキストに設定
	D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
	D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);

	//描画コール
	D3D.m_deviceContext->DrawIndexed(36, 0, 0);

	//ラインの描画
	//ライン用のプリミティブ(ポリゴンの形状)をコンテキストに設定
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//ライン用のインデックスバッファをコンテキストに設定
	D3D.m_deviceContext->IASetIndexBuffer(getLineIndexBuffer(), DXGI_FORMAT_R16_UINT, 0);
	//ライン用のシェーダーをコンテキストに設定
	D3D.m_deviceContext->VSSetShader(D3D.m_lineVS.Get(), 0, 0);
	D3D.m_deviceContext->PSSetShader(D3D.m_linePS.Get(), 0, 0);
	//ライン用の描画コール
	D3D.m_deviceContext->DrawIndexed(24, 0, 0);
}

//実行状態の設定
void Shape::enableExecuting()
{
	canExecute = true;
}

void Shape::disableExecuting()
{
	canExecute = false;
}

//描画状態の設定
void Shape::enableRendering()
{
	canRender = true;
}

void Shape::disableRendering()
{
	canRender = false;
}

//描画状態と実行状態両方の設定
void Shape::enableAll()
{
	canExecute = true;
	canRender = true;
}

void Shape::disableAll()
{
	canExecute = false;
	canRender = false;
}

//実行状態の取得
bool Shape::isPossibleExecuting() const
{
	return canExecute;
}

//描画状態の取得
bool Shape::isPossibleRendering() const
{
	return canRender;
}

//色を変える
void Shape::changeColor(XMFLOAT4 color)
{
	for (int i = 0; i < vertex.size(); i++)
	{
		vertex[i].color = color;
	}
}

//回転させる
void Shape::rotateLocalAxisX(float rotationAngle)
{
	XMMATRIX rotationMatrix = XMMatrixMultiply(XMMatrixRotationQuaternion(rotation), XMMatrixRotationX(rotationAngle));
	rotation = XMQuaternionRotationMatrix(rotationMatrix);
}

void Shape::rotateLocalAxisY(float rotationAngle)
{
	XMMATRIX rotationMatrix = XMMatrixMultiply(XMMatrixRotationQuaternion(rotation), XMMatrixRotationY(rotationAngle));
	rotation = XMQuaternionRotationMatrix(rotationMatrix);
}

void Shape::rotateLocalAxisZ(float rotationAngle)
{
	XMMATRIX rotationMatrix = XMMatrixMultiply(XMMatrixRotationQuaternion(rotation), XMMatrixRotationZ(rotationAngle));
	rotation = XMQuaternionRotationMatrix(rotationMatrix);
}

void Shape::rotateQuaternion(XMFLOAT3 axis, float rotationAngle)
{
	rotation = XMQuaternionRotationAxis(XMVectorSet(axis.x, axis.y, axis.z, 0.0f), rotationAngle);
}

//頂点データへの各種情報の設定
void Shape::setVertexPosition()
{
	//回転を適用した座標を頂点データに入れる
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
	for (int i = 0; i < vertex.size(); i++)
	{
		XMStoreFloat3(&vertex[i].pos, XMVector4Transform(XMLoadFloat3(&vertex[i].pos), rotationMatrix));
		vertex[i].pos = vertex[i].pos + position;
	}
}
