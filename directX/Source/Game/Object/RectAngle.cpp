#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* RectAngle::pIndexBuffer = NULL;

const WORD RectAngle::indexList[indexListSize] = {
		0,1,3,
		3,1,2,
};

RectAngle::RectAngle(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color) : Object(_position, _size, color, vertexNum)
{
	
}

RectAngle::~RectAngle()
{

}

//�ÓI���ʃf�[�^������
bool RectAngle::initializeCommon()
{
	HRESULT hr;

	//�C���f�b�N�X�o�b�t�@�̍쐬
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

//�ÓI���ʃf�[�^�폜
void RectAngle::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
}

//���_�f�[�^�ւ̊e����̐ݒ�
void RectAngle::setVertexPosition()
{
	//��]�����̂Ƃ��̊e���_�̍��W
	vertex[0].pos = { (-size.x * 0.5f) * scale.x, 0.0f, (+size.z * 0.5f) * scale.z };
	vertex[1].pos = { (+size.x * 0.5f) * scale.x, 0.0f, (+size.z * 0.5f) * scale.z };
	vertex[2].pos = { (+size.x * 0.5f) * scale.x, 0.0f, (-size.z * 0.5f) * scale.z };
	vertex[3].pos = { (-size.x * 0.5f) * scale.x, 0.0f, (-size.z * 0.5f) * scale.z };

	//��]�����̂Ƃ��̖@���x�N�g��
	vertex[0].normal = vertex[1].normal = vertex[2].normal = vertex[3].normal = { 0.0f,  1.0f,  0.0f };

	Object::setVertexPosition();
}

ID3D11Buffer* RectAngle::getIndexBuffer()
{
	return pIndexBuffer;
}

int RectAngle::getIndexNum()
{
	return indexListSize;
}