#pragma once

class GameScene
{
public:
	GameScene() {}
	~GameScene() {}

private:
	RectAngle* rectAngle = nullptr;
	Player* player = nullptr;
	Sphere* sphere = nullptr;
	GroundLines* groundLines = nullptr;
	float cameraAdditionalPositionX = 0.01f;

public:
	//初期化
	bool initialize();
	//終了
	void terminate();
	//処理
	void execute();
	//描画
	void render();
};
