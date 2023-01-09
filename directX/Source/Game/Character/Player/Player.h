#pragma once

class Player
{
public:
	Player(Cube* _appearance);
	~Player();

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
	//向きを変える
	void changeViewPoint();
	
	//見た目のアニメーションと回転の反映
	void updateAppearance();
};
