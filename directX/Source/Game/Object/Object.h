#pragma once

struct Vertex
{
	XMFLOAT3 pos;	// 座標
	XMFLOAT4 color;	// 色
	XMFLOAT3 normal;
};

//定数バッファ用構造体
struct ConstantBuffer {
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
	XMFLOAT4   light;
};

enum ObjectType
{
	OBJECT_LINE,
	OBJECT_RECTANGLE,
	OBJECT_CUBE,
	OBJECT_SPHERE,

	OBJECT_TYPE_NUM,
};

class Object
{
public:
	//オブジェクトの正面方向
	static const XMFLOAT3 worldFrontVector;

	//座標
	XMFLOAT3 position;
	//サイズ
	XMFLOAT3 size;
	//スケール
	XMFLOAT3 scale;

	//頂点データ
	std::vector<Vertex> vertex;

protected:
	//回転（クォータニオン）
	XMVECTOR rotation;
	//実行状態の管理(execute関数を実行する)
	bool canExecute;
	//描画状態の管理(render関数を実行する)
	bool canRender;

	//頂点バッファ
	ID3D11Buffer* pVertexBuffer;

	//静的共通データ
	static ID3D11Buffer* pConstantBuffer;
	static ConstantBuffer constantBuffer;
	static UINT	vertexStrides;
	static UINT	vertexOffsets;

public:
	Object(XMFLOAT3 _position, XMFLOAT3 _size, XMFLOAT4 color, int vertexNum);
	virtual ~Object();

	virtual int getType() const = 0;

	//静的共通データ初期化
	static bool initializeCommon();

	//静的共通データのアップデート
	static void updateCommon();

	//静的共通データ削除
	static void terminateCommon();

	//処理
	void execute();

	//描画
	virtual void render();

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
	bool isExecuting() const;
	//描画状態の取得
	bool isRendering() const;

	//色を変える
	void changeColor(XMFLOAT4 color);

	//回転
	XMVECTOR getRotation() const;
	void setRotation(const XMVECTOR _rotation);
	//回転させる
	void rotateLocalAxisX(float rotationAngle);
	void rotateLocalAxisY(float rotationAngle);
	void rotateLocalAxisZ(float rotationAngle);
	void rotateWorldAxisX(float rotationAngle);
	void rotateWorldAxisY(float rotationAngle);
	void rotateWorldAxisZ(float rotationAngle);
	void rotateQuaternion(XMFLOAT3 axis, float rotationAngle);

	//正面方向の取得
	XMFLOAT3 getFrontVector();

	//頂点データへの各種情報の設定
	virtual void setVertexPosition();

private:
	virtual ID3D11Buffer* getIndexBuffer() = 0;
	virtual int getIndexNum() = 0;
};
