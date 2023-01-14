#pragma once

class RectAngle : public Object
{
private:
	//頂点数
	static const int vertexNum = 4;
	static const int indexListSize = 6;

	//派生クラスごとの静的共通データ
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[indexListSize];

public:
	RectAngle(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color);
	~RectAngle() override;

	//静的共通データ初期化
	static bool initializeCommon();

	//静的共通データ削除
	static void terminateCommon();

private:
	//頂点データへの各種情報の設定
	void setVertexPosition() override;
	ID3D11Buffer* getIndexBuffer() override;
	int getIndexNum() override;
};
