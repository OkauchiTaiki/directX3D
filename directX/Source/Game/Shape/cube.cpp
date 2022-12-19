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
	//�ϐ��̏�����
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;
	rotation = XMQuaternionIdentity();

	//���_���W��ݒ�
	setVertexPosition();

	//���_�J���[��ݒ�
	changeColor(color);

	HRESULT hr;

	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// �f�o�C�X�Ƀo�C���h����Ƃ��̎��(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�萔�o�b�t�@�Ȃ�)
	vbDesc.ByteWidth = sizeof(Vertex) * vertexNum;	// �쐬����o�b�t�@�̃o�C�g�T�C�Y
	vbDesc.MiscFlags = 0;							// ���̑��̃t���O
	vbDesc.StructureByteStride = 0;	                // �\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y
	vbDesc.Usage = D3D11_USAGE_DEFAULT;				// �쐬����o�b�t�@�̎g�p�@
	vbDesc.CPUAccessFlags = 0;

	// ��̎d�l��n���Ē��_�o�b�t�@������Ă��炤
	D3D11_SUBRESOURCE_DATA vbData = { vertex, 0, 0 };	// �������ރf�[�^
	// ���_�o�b�t�@�̍쐬
	hr = D3D.m_device->CreateBuffer(&vbDesc, &vbData, &pVertexBuffer);
	if (FAILED(hr)) assert(false);   //���s����ƃ_�C�A���O���o��

	canExecute = true;
	canRender = true;
}

Cube::~Cube()
{
	SAFE_RELEASE(pVertexBuffer);
}

//�ÓI���ʃf�[�^������
bool Cube::initializeCommon()
{
	HRESULT hr;

	//�萔�o�b�t�@�̏�����
	D3D11_BUFFER_DESC cbDesc = {};
	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	hr = D3D.m_device->CreateBuffer(&cbDesc, NULL, &pConstantBuffer);
	if (FAILED(hr))   return false;

	//�萔�o�b�t�@�ɒl������  
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

	//�C���f�b�N�X�o�b�t�@�̍쐬
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

//�ÓI���ʃf�[�^�폜
void Cube::terminateCommon()
{
	SAFE_RELEASE(pIndexBuffer);
	SAFE_RELEASE(pConstantBuffer);
}

//����
void Cube::execute()
{

}

//�`��
void Cube::render()
{
	//���_���W�̐ݒ�
	setVertexPosition();

	//���_�o�b�t�@�̍X�V
	D3D.m_deviceContext->UpdateSubresource(pVertexBuffer, 0, NULL, vertex, 0, 0);

	//���_���C�A�E�g���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());
	//�R���X�^���g�o�b�t�@���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	//���_�o�b�t�@���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &vertexStrides, &vertexOffsets);
	//�v���~�e�B�u(�|���S���̌`��)���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�V�F�[�_�[���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
	D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);

	//�`��R�[��
	D3D.m_deviceContext->DrawIndexed(36, 0, 0);
}

//���s��Ԃ̐ݒ�
void Cube::enableExecuting()
{
	canExecute = true;
}

void Cube::disableExecuting()
{
	canExecute = false;
}

//�`���Ԃ̐ݒ�
void Cube::enableRendering()
{
	canRender = true;
}

void Cube::disableRendering()
{
	canRender = false;
}

//�`���ԂƎ��s��ԗ����̐ݒ�
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

//���s��Ԃ̎擾
bool Cube::isPossibleExecuting() const
{
	return canExecute;
}

//�`���Ԃ̎擾
bool Cube::isPossibleRendering() const
{
	return canRender;
}

//�F��ς���
void Cube::changeColor(XMFLOAT4 color)
{
	for (int i = 0; i < vertexNum; i++)
	{
		vertex[i].color = color;
	}
}

//���_�f�[�^�ւ̊e����̐ݒ�
void Cube::setVertexPosition()
{
	//�W����Ԃł̊e���_�̍��W
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

	//��]��K�p�������W�𒸓_�f�[�^�ɓ����
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
	for (int i = 0; i < vertexNum; i++)
	{
		XMStoreFloat3(&vertexPosition[i], XMVector3Transform(XMLoadFloat3(&vertexPosition[i]), rotationMatrix));
		vertex[i].pos = vertexPosition[i];
	}
}