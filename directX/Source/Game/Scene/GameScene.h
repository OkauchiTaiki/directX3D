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
	//‰Šú‰»
	bool initialize();
	//I—¹
	void terminate();
	//ˆ—
	void execute();
	//•`‰æ
	void render();
};
