#include "framework.h"
#include "Source\environment.h"

//‰Šú‰»
bool GameScene::initialize()
{
	rectAngle = new RectAngle(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(6.0f, 1.0f, 6.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	player = new Player(new Cube(XMFLOAT3(0.0f, 2.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
	sphere = new Sphere(XMFLOAT3(3.0f, 2.0f, 0.0f), 1.0f, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	groundLines = new GroundLines();

	Camera::setTracking(&(player->appearance->position), player->getRotation());

	return true;
}

//I—¹
void GameScene::terminate()
{
	delete rectAngle;
	delete player;
	delete sphere;
	delete groundLines;
}

//ˆ—
void GameScene::execute()
{
	player->movePosition();
	player->changeViewPoint();
	player->updateAppearance();

	Camera::tracking();
}

//•`‰æ
void GameScene::render()
{
	Object::updateCommon();

	rectAngle->render();
	sphere->render();
	player->appearance->render();
	//groundLines->render();
}