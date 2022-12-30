#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* Cube::pIndexBuffer = NULL;
ID3D11Buffer* Cube::pLineIndexBuffer = NULL;

const WORD Cube::indexList[indexListNum] = {
		0,1,3,
		3,1,2,

		8,9,11,
		11,9,10,

		12,13,15,
		15,13,14,

		16,17,19,
		19,17,18,

		20,21,23,
		23,21,22,

		7,6,4,
		4,6,5,
};

const WORD Cube::lineIndexList[lineIndexListNum] = {
	0,1,1,2,2,3,3,0,

	4,5,5,6,6,7,7,4,

	0,4,1,5,2,6,3,7,
};

Cube::Cube(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color) : Shape(_position, _size, color, vertexNum)
{

}

Cube::~Cube()
{
	
}

//静的共通データ初期化
bool Cube::initializeCommon()
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
void Cube::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
	SAFE_RELEASE(pLineIndexBuffer);
}

//頂点データへの各種情報の設定
void Cube::setVertexPosition()
{
	//回転無しのときの各頂点の座標
	vertex[0].pos = vertex[13].pos = vertex[16].pos = { (-size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z };
	vertex[1].pos = vertex[12].pos = vertex[21].pos = { (+size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z };
	vertex[2].pos = vertex[9].pos  = vertex[20].pos = { (+size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z };
	vertex[3].pos = vertex[8].pos  = vertex[17].pos = { (-size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z };
	vertex[4].pos = vertex[14].pos = vertex[19].pos = { (-size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z };
	vertex[5].pos = vertex[15].pos = vertex[22].pos = { (+size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z };
	vertex[6].pos = vertex[10].pos = vertex[23].pos = { (+size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z };
	vertex[7].pos = vertex[11].pos = vertex[18].pos = { (-size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z };

	//回転無しのときの法線ベクトル
	vertex[0].normal = vertex[1].normal = vertex[2].normal = vertex[3].normal =     {  0.0f,  1.0f,  0.0f };
	vertex[4].normal = vertex[5].normal = vertex[6].normal = vertex[7].normal =     {  0.0f, -1.0f,  0.0f };
	vertex[8].normal = vertex[9].normal = vertex[10].normal = vertex[11].normal =   {  0.0f,  0.0f, -1.0f };
	vertex[12].normal = vertex[13].normal = vertex[14].normal = vertex[15].normal = {  0.0f,  0.0f,  1.0f };
	vertex[16].normal = vertex[17].normal = vertex[18].normal = vertex[19].normal = { -1.0f,  0.0f,  0.0f };
	vertex[20].normal = vertex[21].normal = vertex[22].normal = vertex[23].normal = {  1.0f,  0.0f,  0.0f };
	
	Shape::setVertexPosition();
}

ID3D11Buffer* Cube::getIndexBuffer()
{
	return pIndexBuffer;
}

ID3D11Buffer* Cube::getLineIndexBuffer()
{
	return pLineIndexBuffer;
}