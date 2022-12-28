#pragma once

struct Vertex
{
	XMFLOAT3 pos;	// ���W
	XMFLOAT4 color;	// �F
};

//���W�ϊ�����萔�o�b�t�@�p�\����
struct ConstantBuffer {
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

class Cube
{
public:
	//���W
	XMFLOAT3 position;
	//�T�C�Y
	XMFLOAT3 size;
	//�X�P�[��
	XMFLOAT3 scale;

	//���_��
	static const int vertexNum = 8;
	//���_�f�[�^
	Vertex vertex[vertexNum];

private:
	//��]�i�N�H�[�^�j�I���j
	XMVECTOR rotation;
	//���s��Ԃ̊Ǘ�(execute�֐������s����)
	bool canExecute;
	//�`���Ԃ̊Ǘ�(render�֐������s����)
	bool canRender;

	//���_�o�b�t�@
	ID3D11Buffer* pVertexBuffer;

	//�ÓI���ʃf�[�^
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[36];
	static ID3D11Buffer* pLineIndexBuffer;
	static const WORD lineIndexList[24];
	static ID3D11Buffer* pConstantBuffer;
	static ConstantBuffer constantBuffer;
	static UINT	vertexStrides;
	static UINT	vertexOffsets;

public:
	Cube(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color);
	~Cube();

	//�ÓI���ʃf�[�^������
	static bool initializeCommon();

	//�ÓI���ʃf�[�^�폜
	static void terminateCommon();

	//����
    void execute();

	//�`��
	void render();

	//���s��Ԃ̐ݒ�
	void enableExecuting();
	void disableExecuting();

	//�`���Ԃ̐ݒ�
	void enableRendering();
	void disableRendering();

	//�`���ԂƎ��s��ԗ����̐ݒ�
	void enableAll();
	void disableAll();

	//���s��Ԃ̎擾
	bool isPossibleExecuting() const;
	//�`���Ԃ̎擾
	bool isPossibleRendering() const;

	//�F��ς���
	void changeColor(XMFLOAT4 color);

	//��]������
	void rotateLocalAxisX(float rotationAngle);
	void rotateLocalAxisY(float rotationAngle);
	void rotateLocalAxisZ(float rotationAngle);
	void rotateQuaternion(XMFLOAT3 axis, float rotationAngle);

private:
	//���_�f�[�^�ւ̊e����̐ݒ�
	virtual void setVertexPosition();
};


