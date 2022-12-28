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

class Shape
{
public:
	//���W
	XMFLOAT3 position;
	//�T�C�Y
	XMFLOAT3 size;
	//�X�P�[��
	XMFLOAT3 scale;

	//���_�f�[�^
	std::vector<Vertex> vertex;

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
	static ID3D11Buffer* pConstantBuffer;
	static ConstantBuffer constantBuffer;
	static UINT	vertexStrides;
	static UINT	vertexOffsets;

public:
	Shape(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color, int vertexNum);
	virtual ~Shape();

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

protected:
	//���_�f�[�^�ւ̊e����̐ݒ�
	virtual void setVertexPosition();

private:
	virtual ID3D11Buffer* getIndexBuffer() = 0;
	virtual ID3D11Buffer* getLineIndexBuffer() = 0;
};