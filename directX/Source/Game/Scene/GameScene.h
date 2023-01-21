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
	//������
	bool initialize();
	//�I��
	void terminate();
	//����
	void execute();
	//�`��
	void render();
};
