#pragma once

class Sphere : public Object
{
private:
	//面の数
	static const int verticalFaceNum = 12;
	static const int horizontalFaceNum = 18;
	//頂点数
	static const int vertexNum = (verticalFaceNum + 1) * (horizontalFaceNum + 1);
	static const int indexListSize = verticalFaceNum * horizontalFaceNum * 6;

	//派生クラスごとの静的共通データ
	static ID3D11Buffer* pIndexBuffer;
	static WORD indexList[indexListSize];

public:
	Sphere(XMFLOAT3 _position, float radius, XMFLOAT4 color);
	~Sphere() override;

	int getType() const { return OBJECT_SPHERE; }

	//静的共通データ初期化
	static bool initializeCommon();

	//静的共通データ削除
	static void terminateCommon();

	//頂点データへの各種情報の設定
	void setVertexPosition() override;

private:
	ID3D11Buffer* getIndexBuffer() override;
	int getIndexNum() override;
};
