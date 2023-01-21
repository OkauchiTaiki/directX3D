#pragma once

class Enemy
{
public:
	Enemy(Cube* _appearance);
	~Enemy();

	//見た目
	Cube* appearance;

private:
	//生成されてからのフレーム　カウント
	int count = 0;

	//リスポーン関係
	static const int respawnFrame = 40;
	int respawnFrameCount = 0;
	XMFLOAT3 respawnPosition{};

public:
	//位置の移動
	void movePosition();
	
	void die();

	void checkRespawn();
	void respawn();
};
