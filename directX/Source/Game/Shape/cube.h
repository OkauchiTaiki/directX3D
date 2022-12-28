#pragma once

class Cube : public Shape
{
private:
	//���_��
	static const int vertexNum = 8;
	static const int indexListNum = 36;
	static const int lineIndexListNum = 24;

	//�h���N���X���Ƃ̐ÓI���ʃf�[�^
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[indexListNum];
	static ID3D11Buffer* pLineIndexBuffer;
	static const WORD lineIndexList[lineIndexListNum];

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
	ID3D11Buffer* getLineIndexBuffer() override;
};

