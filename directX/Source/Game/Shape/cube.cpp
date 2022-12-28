#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* Cube::pIndexBuffer = NULL;
ID3D11Buffer* Cube::pLineIndexBuffer = NULL;

const WORD Cube::indexList[indexListNum] = {
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

//�ÓI���ʃf�[�^������
bool Cube::initializeCommon()
{
	HRESULT hr;

	//�C���f�b�N�X�o�b�t�@�̍쐬
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

	//���C���p�̃C���f�b�N�X�o�b�t�@�̍쐬
	ibDesc.ByteWidth = sizeof(WORD) * lineIndexListNum;
    ibData = { lineIndexList, 0, 0 };
	hr = D3D.m_device->CreateBuffer(&ibDesc, &ibData, &pLineIndexBuffer);
	if (FAILED(hr))   return false;

	return true;
}

//�ÓI���ʃf�[�^�폜
void Cube::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
	SAFE_RELEASE(pLineIndexBuffer);
}

//���_�f�[�^�ւ̊e����̐ݒ�
void Cube::setVertexPosition()
{
	//�W����Ԃł̊e���_�̍��W
	vertex[0].pos = { (-size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z };
	vertex[1].pos = { (+size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z };
	vertex[2].pos = { (+size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z };
	vertex[3].pos = { (-size.x * 0.5f) * scale.x, (+size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z };
	vertex[4].pos = { (-size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z };
	vertex[5].pos = { (+size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (-size.z * 0.5f) * scale.z };
	vertex[6].pos = { (+size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z };
	vertex[7].pos = { (-size.x * 0.5f) * scale.x, (-size.y * 0.5f) * scale.y, (+size.z * 0.5f) * scale.z };
	
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