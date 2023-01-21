#pragma once

struct Vertex
{
	XMFLOAT3 pos;	// ���W
	XMFLOAT4 color;	// �F
	XMFLOAT3 normal;
};

//�萔�o�b�t�@�p�\����
struct ConstantBuffer {
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
	XMFLOAT4   light;
};

enum ObjectType
{
	OBJECT_LINE,
	OBJECT_RECTANGLE,
	OBJECT_CUBE,
	OBJECT_SPHERE,

	OBJECT_TYPE_NUM,
};

class Object
{
public:
	//�I�u�W�F�N�g�̐��ʕ���
	static const XMFLOAT3 worldFrontVector;

	//���W
	XMFLOAT3 position;
	//�T�C�Y
	XMFLOAT3 size;
	//�X�P�[��
	XMFLOAT3 scale;

	//���_�f�[�^
	std::vector<Vertex> vertex;

protected:
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
	Object(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color, int vertexNum);
	virtual ~Object();

	virtual int getType() const = 0;

	//�ÓI���ʃf�[�^������
	static bool initializeCommon();

	//�ÓI���ʃf�[�^�̃A�b�v�f�[�g
	static void updateCommon();

	//�ÓI���ʃf�[�^�폜
	static void terminateCommon();

	//����
	void execute();

	//�`��
	virtual void render();

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
	bool isExecuting() const;
	//�`���Ԃ̎擾
	bool isRendering() const;

	//�F��ς���
	void changeColor(XMFLOAT4 color);

	//��]
	XMVECTOR getRotation() const;
	void setRotation(const XMVECTOR _rotation);
	//��]������
	void rotateLocalAxisX(float rotationAngle);
	void rotateLocalAxisY(float rotationAngle);
	void rotateLocalAxisZ(float rotationAngle);
	void rotateWorldAxisX(float rotationAngle);
	void rotateWorldAxisY(float rotationAngle);
	void rotateWorldAxisZ(float rotationAngle);
	void rotateQuaternion(XMFLOAT3 axis, float rotationAngle);

	//���ʕ����̎擾
	XMFLOAT3 getFrontVector();

	//���_�f�[�^�ւ̊e����̐ݒ�
	virtual void setVertexPosition();

private:
	virtual ID3D11Buffer* getIndexBuffer() = 0;
	virtual int getIndexNum() = 0;
};
