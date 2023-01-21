#pragma once

class Sphere : public Object
{
private:
	//�ʂ̐�
	static const int verticalFaceNum = 12;
	static const int horizontalFaceNum = 18;
	//���_��
	static const int vertexNum = (verticalFaceNum + 1) * (horizontalFaceNum + 1);
	static const int indexListSize = verticalFaceNum * horizontalFaceNum * 6;

	//�h���N���X���Ƃ̐ÓI���ʃf�[�^
	static ID3D11Buffer* pIndexBuffer;
	static WORD indexList[indexListSize];

public:
	Sphere(XMFLOAT3 _position, float radius, XMFLOAT4 color);
	~Sphere() override;

	int getType() const { return OBJECT_SPHERE; }

	//�ÓI���ʃf�[�^������
	static bool initializeCommon();

	//�ÓI���ʃf�[�^�폜
	static void terminateCommon();

	//���_�f�[�^�ւ̊e����̐ݒ�
	void setVertexPosition() override;

private:
	ID3D11Buffer* getIndexBuffer() override;
	int getIndexNum() override;
};
