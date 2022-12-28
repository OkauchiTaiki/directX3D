#pragma once

struct Vertex
{
	XMFLOAT3 pos;	// 座標
	XMFLOAT4 color;	// 色
};

//座標変換する定数バッファ用構造体
struct ConstantBuffer {
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

class Cube
{
public:
	//座標
	XMFLOAT3 position;
	//サイズ
	XMFLOAT3 size;
	//スケール
	XMFLOAT3 scale;

	//頂点数
	static const int vertexNum = 8;
	//頂点データ
	Vertex vertex[vertexNum];

private:
	//回転（クォータニオン）
	XMVECTOR rotation;
	//実行状態の管理(execute関数を実行する)
	bool canExecute;
	//描画状態の管理(render関数を実行する)
	bool canRender;

	//頂点バッファ
	ID3D11Buffer* pVertexBuffer;

	//静的共通データ
	static ID3D11Buffer* pIndexBuffer;
	static const WORD indexList[36];
	static ID3D11Buffer* pLineIndexBuffer;
	static const WORD lineIndexList[24];
	static ID3D11Buffer* pConstantBuffer;
	static ConstantBuffer constantBuffer;
	static UINT	vertexStrides;
	static UINT	vertexOffsets;

public:
	Cube(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color);
	~Cube();

	//静的共通データ初期化
	static bool initializeCommon();

	//静的共通データ削除
	static void terminateCommon();

	//処理
    void execute();

	//描画
	void render();

	//実行状態の設定
	void enableExecuting();
	void disableExecuting();

	//描画状態の設定
	void enableRendering();
	void disableRendering();

	//描画状態と実行状態両方の設定
	void enableAll();
	void disableAll();

	//実行状態の取得
	bool isPossibleExecuting() const;
	//描画状態の取得
	bool isPossibleRendering() const;

	//色を変える
	void changeColor(XMFLOAT4 color);

	//回転させる
	void rotateLocalAxisX(float rotationAngle);
	void rotateLocalAxisY(float rotationAngle);
	void rotateLocalAxisZ(float rotationAngle);
	void rotateQuaternion(XMFLOAT3 axis, float rotationAngle);

private:
	//頂点データへの各種情報の設定
	virtual void setVertexPosition();
};


