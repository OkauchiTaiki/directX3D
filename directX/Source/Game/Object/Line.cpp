#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* Line::pIndexBuffer = NULL;

const WORD Line::indexList[indexListSize] = {
		0,1
};

Line::Line(XMFLOAT3 _position, float _size, XMFLOAT4 color) : Object(_position, XMFLOAT3(_size, 0.0f, 0.0f), color, vertexNum)
{

}

Line::~Line()
{

}

//静的共通データ初期化
bool Line::initializeCommon()
{
	HRESULT hr;

	//インデックスバッファの作成
	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.ByteWidth = sizeof(WORD) * indexListSize;
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
void Line::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
}

void Line::render()
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
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//シェーダーをコンテキストに設定
	D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
	D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);

	//描画コール
	D3D.m_deviceContext->DrawIndexed(getIndexNum(), 0, 0);
}

//頂点データへの各種情報の設定
void Line::setVertexPosition()
{
	//回転無しのときの各頂点の座標
	vertex[0].pos = { (-size.x * 0.5f) * scale.x, 0.0f, 0.0f };
	vertex[1].pos = { (+size.x * 0.5f) * scale.x, 0.0f, 0.0f };

	//回転無しのときの法線ベクトル
	vertex[0].normal = vertex[1].normal = { 0.0f,  1.0f,  0.0f };

	Object::setVertexPosition();
}

ID3D11Buffer* Line::getIndexBuffer()
{
	return pIndexBuffer;
}

int Line::getIndexNum()
{
	return indexListSize;
}