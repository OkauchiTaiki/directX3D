#pragma once

class GameScene
{
public:
	GameScene() {}
	~GameScene() {}

private:
	RectAngle* rectangle = nullptr;
	Player* player = nullptr;
	std::vector<Enemy*> enemys{ 3 , nullptr};
	std::vector<Bullet*> bullets{ 15 , nullptr };
	Sphere* sphere = nullptr;
	Cube* cube = nullptr;
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
