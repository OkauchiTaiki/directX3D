#pragma once

class Cube : public Object
{
private:
	//���_��
	static const int vertexNum = 24;
	static const int indexListSize = 36;

	//�h���N���X���Ƃ̐ÓI���ʃf�[�^
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[indexListSize];

public:
	Cube(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color);
	~Cube() override;

	//�ÓI���ʃf�[�^������
	static bool initializeCommon();

	//�ÓI���ʃf�[�^�폜
	static void terminateCommon();

private:
	//���_�f�[�^�ւ̊e����̐ݒ�
	void setVertexPosition() override;
	ID3D11Buffer* getIndexBuffer() override;
	int getIndexNum() override;
};

