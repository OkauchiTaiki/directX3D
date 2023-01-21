#include "framework.h"
#include "Source\environment.h"

//èâä˙âª
bool GameScene::initialize()
{
	rectangle = new RectAngle(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(12.0f, 1.0f, 12.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	player = new Player(new Cube(XMFLOAT3(0.0f, 2.0f, -2.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i] = new Enemy(new Cube(XMFLOAT3(-2.0f + (float)i * 2.0f, 2.0f , 2.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)));
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i] = new Bullet(new Sphere(XMFLOAT3(0.0f, 0.0f, 0.0f), 0.4f, XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)));
	}
	sphere = new Sphere(XMFLOAT3(3.0f, 2.0f, 0.0f), 0.5f, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	cube = new Cube(XMFLOAT3(0.0f, 2.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	groundLines = new GroundLines();

	Camera::setTracking(&(player->appearance->position), player->getRotation());

	return true;
}

//èIóπ
void GameScene::terminate()
{
	delete rectangle;
	delete player;
	for (auto& enemy : enemys)
	{
		delete enemy;
	}
	for (auto& bullet : bullets)
	{
		delete bullet;
	}
	delete sphere;
	delete cube;
	delete groundLines;
}

//èàóù
void GameScene::execute()
{
	//ìñÇΩÇËîªíË
	for (auto enemy : enemys)
	{
		if (!enemy->appearance->isRendering())   continue;
		for (auto& bullet : bullets)
		{
			if (!bullet->appearance->isRendering())   continue;
			if (CollisionDetection::detectCollision(enemy->appearance, bullet->appearance))
			{
				enemy->die();
				bullet->die();
			}
		}
	}

	//ÉvÉåÉCÉÑÅ[ìÆÇ©Ç∑
	player->movePosition();
	player->changeViewPoint();
	player->updateAppearance();

	//íeî≠éÀ
	if (Mouse::trgL())
	{
		for (auto& bullet : bullets)
		{
			if (!bullet->appearance->isRendering())
			{
				bullet->generateBullet(player->appearance->getFrontVector(), player->appearance->position);
				break;
			}
		}
	}

	//ìGìÆÇ©Ç∑
	for (auto& enemy : enemys)
	{
		if (enemy->appearance->isRendering())
		{
			enemy->movePosition();
		}
		else
		{
			enemy->checkRespawn();
		}
	}

	//íeìÆÇ©Ç∑
	for (auto& bullet : bullets)
	{
		if (bullet->appearance->isRendering())
		{
			bullet->move();
		}
	}

	Camera::tracking();
}

//ï`âÊ
void GameScene::render()
{
	Object::updateCommon();

	rectangle->render();
	//sphere->render();
	//cube->render();
	player->appearance->render();
	for (auto& enemy : enemys)
	{
		if (enemy->appearance->isRendering())   enemy->appearance->render();
	}
	for (auto& bullet : bullets)
	{
		if (bullet->appearance->isRendering())   bullet->appearance->render();
	}
	groundLines->render();
}