#pragma once

class Line : public Object
{
private:
	//���_��
	static const int vertexNum = 2;
	static const int indexListSize = 2;

	//�h���N���X���Ƃ̐ÓI���ʃf�[�^
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[indexListSize];

public:
	Line(XMFLOAT3 _position, float _size, XMFLOAT4 color);
	~Line() override;

	//�ÓI���ʃf�[�^������
	static bool initializeCommon();

	//�ÓI���ʃf�[�^�폜
	static void terminateCommon();

	void render() override;

private:
	//���_�f�[�^�ւ̊e����̐ݒ�
	void setVertexPosition() override;
	ID3D11Buffer* getIndexBuffer() override;
	int getIndexNum() override;
};