#pragma once

class Cube : public Object
{
private:
	//頂点数
	static const int vertexNum = 24;
	static const int indexListSize = 36;

	//派生クラスごとの静的共通データ
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[indexListSize];

public:
	Cube(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color);
	~Cube() override;

	int getType() const { return OBJECT_CUBE; }

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


