#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* Sphere::pIndexBuffer = NULL;
WORD Sphere::indexList[indexListSize] = { 0 };

Sphere::Sphere(XMFLOAT3 _position, float radius, XMFLOAT4 color) : Object(_position, XMFLOAT3(radius, radius, radius), color, vertexNum)
{
	
}

Sphere::~Sphere()
{

}

//静的共通データ初期化
bool Sphere::initializeCommon()
{
	for (int i = 0; i < verticalFaceNum; i++)
	{
		int verticalOffset = i * (horizontalFaceNum + 1);
		int indexOffset = horizontalFaceNum * 6 * i;
		for (int j = 0; j < horizontalFaceNum; j++)
		{
			indexList[indexOffset + j * 6]     = verticalOffset + j;
			indexList[indexOffset + j * 6 + 1] = verticalOffset + j + 1;
			indexList[indexOffset + j * 6 + 2] = verticalOffset + j + horizontalFaceNum + 1;
			indexList[indexOffset + j * 6 + 3] = verticalOffset + j + horizontalFaceNum + 1;
			indexList[indexOffset + j * 6 + 4] = verticalOffset + j + 1;
			indexList[indexOffset + j * 6 + 5] = verticalOffset + j + horizontalFaceNum + 2;
		}
	}

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
void Sphere::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
}

//頂点データへの各種情報の設定
void Sphere::setVertexPosition()
{
	//回転無しのときの各頂点の座標と法線ベクトル
	for (int i = 0; i <= verticalFaceNum; i++)
	{
		float ph = PI * (float)i / (float)verticalFaceNum;
		float y = scale.y * cosf(ph);
		float r = sinf(ph);
		for (int j = 0; j <= horizontalFaceNum; j++)
		{
			float th = 2.0f * PI * (float)j / (float)horizontalFaceNum;
			float x = scale.x * r * cosf(th);
			float z = scale.z * r * sinf(th);

			int index = (horizontalFaceNum + 1) * i + j;
			vertex[index].pos = { x, y, z };

			//法線ベクトル
			vertex[index].normal = vertex[index].pos;
		}
	}

	Object::setVertexPosition();
}

ID3D11Buffer* Sphere::getIndexBuffer()
{
	return pIndexBuffer;
}

int Sphere::getIndexNum()
{
	return indexListSize;
}