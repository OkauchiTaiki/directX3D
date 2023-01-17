#pragma once

class Enemy
{
public:
	Enemy(Cube* _appearance);
	~Enemy();

	//見た目
	Cube* appearance;

private:
	//Z軸回転のアニメーションを無視したクォータニオン
	XMVECTOR rotation = XMQuaternionIdentity();
	//Z軸回転の量
	float rotationZ = 0.0f;

public:
	const XMVECTOR* getRotation() const;

	//位置の移動
	void movePosition();

	//生成されてからのフレーム　カウント
	int count;
};
