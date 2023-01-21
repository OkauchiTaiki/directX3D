#pragma once

class Line : public Object
{
private:
	//頂点数
	static const int vertexNum = 2;
	static const int indexListSize = 2;

	//派生クラスごとの静的共通データ
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[indexListSize];

public:
	Line(XMFLOAT3 _position, float _size, XMFLOAT4 color);
	~Line() override;

	int getType() const { return OBJECT_LINE; }

	//静的共通データ初期化
	static bool initializeCommon();

	//静的共通データ削除
	static void terminateCommon();

	void render() override;

	//頂点データへの各種情報の設定
	void setVertexPosition() override;

private:
	ID3D11Buffer* getIndexBuffer() override;
	int getIndexNum() override;
};