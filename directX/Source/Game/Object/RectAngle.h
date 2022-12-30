#pragma once

class RectAngle : public Object
{
private:
	//���_��
	static const int vertexNum = 4;
	static const int indexListSize = 6;

	//�h���N���X���Ƃ̐ÓI���ʃf�[�^
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[indexListSize];

public:
	RectAngle(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color);
	~RectAngle() override;

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