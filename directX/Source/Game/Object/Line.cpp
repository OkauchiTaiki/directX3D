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

//�ÓI���ʃf�[�^������
bool Line::initializeCommon()
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
void Line::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
}

void Line::render()
{
	//���_���W�̐ݒ�
	setVertexPosition();

	//���_�o�b�t�@�̍X�V
	D3D.m_deviceContext->UpdateSubresource(pVertexBuffer, 0, NULL, &vertex[0], 0, 0);

	//���_���C�A�E�g���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());
	//�R���X�^���g�o�b�t�@���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	//���_�o�b�t�@���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &vertexStrides, &vertexOffsets);
	//�C���f�b�N�X�o�b�t�@���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->IASetIndexBuffer(getIndexBuffer(), DXGI_FORMAT_R16_UINT, 0);
	//�v���~�e�B�u(�|���S���̌`��)���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//�V�F�[�_�[���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
	D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);

	//�`��R�[��
	D3D.m_deviceContext->DrawIndexed(getIndexNum(), 0, 0);
}

//���_�f�[�^�ւ̊e����̐ݒ�
void Line::setVertexPosition()
{
	//��]�����̂Ƃ��̊e���_�̍��W
	vertex[0].pos = { (-size.x * 0.5f) * scale.x, 0.0f, 0.0f };
	vertex[1].pos = { (+size.x * 0.5f) * scale.x, 0.0f, 0.0f };

	//��]�����̂Ƃ��̖@���x�N�g��
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