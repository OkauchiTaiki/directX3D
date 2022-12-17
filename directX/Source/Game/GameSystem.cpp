#include "framework.h"
// GameSystem�N���X���g����悤�ɂ���
#include "GameSystem.h"
// Direct3D�N���X���g����悤�ɂ���
#include "Source/DirectX/Direct3D.h"

// �Q�[���̏����ݒ���s��
void GameSystem::initialize()
{
	//�g�i���m�ł��I
	//��������ł��I
	// ���䃄�}�g�ł��I
	//���K
}

// ���̃Q�[���̎��Ԃ�i�߂�(���������s����)
void GameSystem::execute()
{
    // ��ʂ�F�œh��Ԃ�
    /*float color[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
    D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);*/

	// �O�p�`�̕`��
	{
		// �P���_�̌`��(����͍��W����)
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;	// ���W
			float color[4];	// �F
		};
		Vertex vertexCube[36] = {
			 { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	         { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	         { { -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			 { { -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			 { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			 { {  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	         
	         { {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	         { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	         { {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			 { {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			 { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			 { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	         
	         { { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	         { { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	         { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
			 { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
			 { { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
			 { { -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	         
	         { {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	         { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	         { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	         
	         { { -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	         { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	         { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
			 { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
			 { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	         
	         { { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	         { {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	         { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			 { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			 { {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			 { {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		};

		DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotation);
		for (int i = 0; i < 36; i++)
		{
			DirectX::XMStoreFloat3(&vertexCube[i].pos, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&vertexCube[i].pos), rotationMatrix));
		}
		rotation += 0.001f;

		/*WORD g_IndexList[]{
	         0,  1,  2,     3,  2,  1,
	         4,  5,  6,     7,  6,  5,
	         8,  9, 10,    11, 10,  9,
	        12, 13, 14,    15, 14, 13,
	        16, 17, 18,    19, 18, 17,
	        20, 21, 22,    23, 22, 21,
		};*/

		struct ConstantBuffer {
			DirectX::XMFLOAT4X4 world;
			DirectX::XMFLOAT4X4 view;
			DirectX::XMFLOAT4X4 projection;
		};

		//�[�x�X�e���V���o�b�t�@�쐬
		D3D11_TEXTURE2D_DESC txDesc;
		ZeroMemory(&txDesc, sizeof(txDesc));
		txDesc.Width = 1280;
		txDesc.Height = 720;
		txDesc.MipLevels = 1;
		txDesc.ArraySize = 1;
		txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		txDesc.SampleDesc.Count = 1;
		txDesc.SampleDesc.Quality = 0;
		txDesc.Usage = D3D11_USAGE_DEFAULT;
		txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		txDesc.CPUAccessFlags = 0;
		txDesc.MiscFlags = 0;

		ID3D11Texture2D* m_depthStencilTexture;
		D3D.m_device->CreateTexture2D(&txDesc, NULL, &m_depthStencilTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(dsDesc));
		dsDesc.Format = txDesc.Format;
		dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsDesc.Texture2D.MipSlice = 0;

		ID3D11DepthStencilView* m_depthStencilView;
		D3D.m_device->CreateDepthStencilView(m_depthStencilTexture, &dsDesc, &m_depthStencilView);

		//-----------------------------
		// ���_�o�b�t�@�쐬
		// �E��L�ō�����R�̒��_�͂��̂܂܂ł͕`��Ɏg�p�ł��Ȃ��񂷁c
		// �E�r�f�I���������Ɂu���_�o�b�t�@�v�Ƃ����`�ō��K�v������܂��I
		// �E����͌����������āA���̏�ō���āA�g���āA�����̂Ă܂��B
		//-----------------------------
		// �쐬����o�b�t�@�̎d�l�����߂�
		// �E����͒��_�o�b�t�@�ɂ��邼�I���Ċ����̐ݒ�
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// �f�o�C�X�Ƀo�C���h����Ƃ��̎��(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�萔�o�b�t�@�Ȃ�)
		vbDesc.ByteWidth = sizeof(Vertex) * 36;			// �쐬����o�b�t�@�̃o�C�g�T�C�Y
		vbDesc.MiscFlags = 0;							// ���̑��̃t���O
		vbDesc.StructureByteStride = 0;	                // �\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y
		vbDesc.Usage = D3D11_USAGE_DEFAULT;				// �쐬����o�b�t�@�̎g�p�@
		vbDesc.CPUAccessFlags = 0;

		// ��̎d�l��n���Ē��_�o�b�t�@������Ă��炤
		// �������f�o�C�X����ɂ��肢����
		ID3D11Buffer* vb;
		D3D11_SUBRESOURCE_DATA vbData = { vertexCube, 0, 0 };	// �������ރf�[�^
		// ���_�o�b�t�@�̍쐬
		D3D.m_device->CreateBuffer(&vbDesc, &vbData, &vb);

		//---------------------------
		//�C���f�b�N�X�o�b�t�@
		//--------------------------
		/*D3D11_BUFFER_DESC ibDesc = {};
		ibDesc.ByteWidth = sizeof(WORD) * 6 * 6;
		ibDesc.Usage = D3D11_USAGE_DEFAULT;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;

		ID3D11Buffer* ib;
		D3D11_SUBRESOURCE_DATA ibData = { g_IndexList, 0, 0 };
		D3D.m_device->CreateBuffer(&ibDesc, &ibData, &ib);*/

		//-----------------------------------
		//�萔�o�b�t�@
		//----------------------------------
		D3D11_BUFFER_DESC cbDesc = {};
		cbDesc.ByteWidth = sizeof(ConstantBuffer);
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;

		ID3D11Buffer* constantBuffer;
		D3D.m_device->CreateBuffer(&cbDesc, NULL, &constantBuffer);

		//�萔�o�b�t�@�ɒl������
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

		DirectX::XMVECTOR eye = DirectX::XMVectorSet(-4.0f, -4.0f, -4.0f, 0.0f);
		DirectX::XMVECTOR focus = DirectX::XMVectorSet(0.0f, 0.0f, 0.5f, 0.0f);
		DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(eye, focus, up);

		float    fov = DirectX::XMConvertToRadians(45.0f);
		float    aspect = 1280.0f / 720.0f;
		float    nearZ = 0.1f;
		float    farZ = 100.0f;
		DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

		ConstantBuffer cb;
		XMStoreFloat4x4(&cb.world, XMMatrixTranspose(worldMatrix));
		XMStoreFloat4x4(&cb.view, XMMatrixTranspose(viewMatrix));
		XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(projMatrix));
		D3D.m_deviceContext->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);

		//++++++++++++++++++++ ��������`�悵�Ă����܂� ++++++++++++++++++++

		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
		// ��������́u�`��̐E�l�v�f�o�C�X�R���e�L�X�g���񂪑劈��

		// ���_�o�b�t�@��`��Ŏg����悤�ɃZ�b�g����
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());
		D3D.m_deviceContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
		//D3D.m_deviceContext->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);
		// �v���~�e�B�u�E�g�|���W�[���Z�b�g
		D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		D3D.m_deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
		D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), clearColor);
		D3D.m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//-----------------------------
		// �V�F�[�_�[���Z�b�g
		//-----------------------------
		D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
		D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);

		// ����Ȋ����ŁA�Ђ�����f�o�C�X�R���e�L�X�g�ɏ���n��

		//-----------------------------
		// �`����s
		//-----------------------------
		// �f�o�C�X�R���e�L�X�g����A��L�̃Z�b�g�������e�ŕ`�悵�Ă��������A�Ƃ��肢����
		D3D.m_deviceContext->Draw(36, 0);
		vb->Release();
		constantBuffer->Release();
		m_depthStencilTexture->Release();
		m_depthStencilView->Release();
	}

    // �o�b�N�o�b�t�@�̓��e����ʂɕ\��
    D3D.m_swapChain->Present(0, 0);
}