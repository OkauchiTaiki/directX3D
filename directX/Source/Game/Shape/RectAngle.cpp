#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* RectAngle::pIndexBuffer = NULL;
ID3D11Buffer* RectAngle::pLineIndexBuffer = NULL;

const WORD RectAngle::indexList[indexListNum] = {
		0,3,1,
		3,2,1,
};

const WORD RectAngle::lineIndexList[lineIndexListNum] = {
	0,1,1,2,2,3,3,0
};

RectAngle::RectAngle(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color) : Shape(_position, _size, color, vertexNum)
{

}

RectAngle::~RectAngle()
{

}

//静的共通データ初期化
bool RectAngle::initializeCommon()
{
	HRESULT hr;

	//インデックスバッファの作成
	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.ByteWidth = sizeof(WORD) * indexListNum;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA ibData = { indexList, 0, 0 };
	hr = D3D.m_device->CreateBuffer(&ibDesc, &ibData, &pIndexBuffer);
	if (FAILED(hr))   return false;

	//ライン用のインデックスバッファの作成
	ibDesc.ByteWidth = sizeof(WORD) * lineIndexListNum;
	ibData = { lineIndexList, 0, 0 };
	hr = D3D.m_device->CreateBuffer(&ibDesc, &ibData, &pLineIndexBuffer);
	if (FAILED(hr))   return false;

	return true;
}

//静的共通データ削除
void RectAngle::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
	SAFE_RELEASE(pLineIndexBuffer);
}

//頂点データへの各種情報の設定
void RectAngle::setVertexPosition()
{
	//標準状態での各頂点の座標
	vertex[0].pos = { (-size.x * 0.5f) * scale.x, 0.0f, (-size.z * 0.5f) * scale.z };
	vertex[1].pos = { (+size.x * 0.5f) * scale.x, 0.0f, (-size.z * 0.5f) * scale.z };
	vertex[2].pos = { (+size.x * 0.5f) * scale.x, 0.0f, (+size.z * 0.5f) * scale.z };
	vertex[3].pos = { (-size.x * 0.5f) * scale.x, 0.0f, (+size.z * 0.5f) * scale.z };

	Shape::setVertexPosition();
}

ID3D11Buffer* RectAngle::getIndexBuffer()
{
	return pIndexBuffer;
}

ID3D11Buffer* RectAngle::getLineIndexBuffer()
{
	return pLineIndexBuffer;
}