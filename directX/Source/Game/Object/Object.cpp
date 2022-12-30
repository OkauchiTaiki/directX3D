#include "framework.h"
#include "Source\environment.h"

ID3D11Buffer* Object::pConstantBuffer = NULL;
ConstantBuffer Object::constantBuffer = {};
UINT Object::vertexStrides = sizeof(Vertex);
UINT Object::vertexOffsets = 0;

Object::Object(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color, int vertexNum) : position(_position), size(_size)
{
	vertex.resize(vertexNum);

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;
	rotation = XMQuaternionIdentity();

	//���_�J���[��ݒ�
	changeColor(color);

	//���_�o�b�t�@
	HRESULT hr;

	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// �f�o�C�X�Ƀo�C���h����Ƃ��̎��(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�萔�o�b�t�@�Ȃ�)
	vbDesc.ByteWidth = sizeof(Vertex) * vertexNum;	// �쐬����o�b�t�@�̃o�C�g�T�C�Y
	vbDesc.MiscFlags = 0;							// ���̑��̃t���O
	vbDesc.StructureByteStride = 0;	                // �\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y
	vbDesc.Usage = D3D11_USAGE_DEFAULT;				// �쐬����o�b�t�@�̎g�p�@
	vbDesc.CPUAccessFlags = 0;

	// ��̎d�l��n���Ē��_�o�b�t�@������Ă��炤
	D3D11_SUBRESOURCE_DATA vbData = { &vertex[0], 0, 0 };	// �������ރf�[�^
	// ���_�o�b�t�@�̍쐬
	hr = D3D.m_device->CreateBuffer(&vbDesc, &vbData, &pVertexBuffer);
	if (FAILED(hr)) assert(false);   //���s����ƃ_�C�A���O���o��

	canExecute = true;
	canRender = true;
}

Object::~Object()
{
	SAFE_RELEASE(pVertexBuffer);
}

//�ÓI���ʃf�[�^������
bool Object::initializeCommon()
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
	updateCommon();

	return true;
}

//�ÓI���ʃf�[�^�̃A�b�v�f�[�g
void Object::updateCommon()
{
	XMStoreFloat4x4(&constantBuffer.world, XMMatrixTranspose(Camera::getWorldMatrix()));
	XMStoreFloat4x4(&constantBuffer.view, XMMatrixTranspose(Camera::getViewMatrix()));
	XMStoreFloat4x4(&constantBuffer.projection, XMMatrixTranspose(Camera::getProjectionMatrix()));
	XMStoreFloat4(&constantBuffer.light, DirectionalLight::getDirection());
	D3D.m_deviceContext->UpdateSubresource(pConstantBuffer, 0, NULL, &constantBuffer, 0, 0);
}

//�ÓI���ʃf�[�^�폜
void Object::terminateCommon()
{
	SAFE_RELEASE(pConstantBuffer);
}

//����
void Object::execute()
{

}

//�`��
void Object::render()
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
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�V�F�[�_�[���R���e�L�X�g�ɐݒ�
	D3D.m_deviceContext->VSSetShader(D3D.m_lightVS.Get(), 0, 0);
	D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);

	//�`��R�[��
	D3D.m_deviceContext->DrawIndexed(getIndexNum(), 0, 0);
}

//���s��Ԃ̐ݒ�
void Object::enableExecuting()
{
	canExecute = true;
}

void Object::disableExecuting()
{
	canExecute = false;
}

//�`���Ԃ̐ݒ�
void Object::enableRendering()
{
	canRender = true;
}

void Object::disableRendering()
{
	canRender = false;
}

//�`���ԂƎ��s��ԗ����̐ݒ�
void Object::enableAll()
{
	canExecute = true;
	canRender = true;
}

void Object::disableAll()
{
	canExecute = false;
	canRender = false;
}

//���s��Ԃ̎擾
bool Object::isPossibleExecuting() const
{
	return canExecute;
}

//�`���Ԃ̎擾
bool Object::isPossibleRendering() const
{
	return canRender;
}

//�F��ς���
void Object::changeColor(XMFLOAT4 color)
{
	for (int i = 0; i < vertex.size(); i++)
	{
		vertex[i].color = color;
	}
}

//��]������
void Object::rotateLocalAxisX(float rotationAngle)
{
	XMMATRIX rotationMatrix = XMMatrixMultiply(XMMatrixRotationQuaternion(rotation), XMMatrixRotationX(rotationAngle));
	rotation = XMQuaternionRotationMatrix(rotationMatrix);
}

void Object::rotateLocalAxisY(float rotationAngle)
{
	XMMATRIX rotationMatrix = XMMatrixMultiply(XMMatrixRotationQuaternion(rotation), XMMatrixRotationY(rotationAngle));
	rotation = XMQuaternionRotationMatrix(rotationMatrix);
}

void Object::rotateLocalAxisZ(float rotationAngle)
{
	XMMATRIX rotationMatrix = XMMatrixMultiply(XMMatrixRotationQuaternion(rotation), XMMatrixRotationZ(rotationAngle));
	rotation = XMQuaternionRotationMatrix(rotationMatrix);
}

void Object::rotateQuaternion(XMFLOAT3 axis, float rotationAngle)
{
	rotation = XMQuaternionRotationAxis(XMVectorSet(axis.x, axis.y, axis.z, 0.0f), rotationAngle);
}

//���_�f�[�^�ւ̊e����̐ݒ�
void Object::setVertexPosition()
{
	//��]��K�p�������W�𒸓_�f�[�^�ɓ����
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
	for (int i = 0; i < vertex.size(); i++)
	{
		XMStoreFloat3(&vertex[i].pos, XMVector4Transform(XMLoadFloat3(&vertex[i].pos), rotationMatrix));
		vertex[i].pos = vertex[i].pos + position;

		//���łɖ@���x�N�g���ɂ���]��������
		XMStoreFloat3(&vertex[i].normal, XMVector4Transform(XMLoadFloat3(&vertex[i].normal), rotationMatrix));
	}
}
