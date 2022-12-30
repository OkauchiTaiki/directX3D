#pragma once

class Cube : public Shape
{
private:
	//頂点数
	static const int vertexNum = 24;
	static const int indexListNum = 36;
	static const int lineIndexListNum = 24;

	//派生クラスごとの静的共通データ
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[indexListNum];
	static ID3D11Buffer* pLineIndexBuffer;
	static const WORD lineIndexList[lineIndexListNum];

public:
	Cube(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color);
	~Cube() override;

	//静的共通データ初期化
	static bool initializeCommon();

	//静的共通データ削除
	static void terminateCommon();

private:
	//頂点データへの各種情報の設定
	void setVertexPosition() override;
	ID3D11Buffer* getIndexBuffer() override;
	ID3D11Buffer* getLineIndexBuffer() override;
};


