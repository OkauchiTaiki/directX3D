#include "framework.h"
#include "Source\environment.h"

//初期化
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

//終了
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

//処理
void GameScene::execute()
{
	//当たり判定
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

	//プレイヤー動かす
	player->movePosition();
	player->changeViewPoint();
	player->updateAppearance();

	//弾発射
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

	//敵動かす
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

	//弾動かす
	for (auto& bullet : bullets)
	{
		if (bullet->appearance->isRendering())
		{
			bullet->move();
		}
	}

	Camera::tracking();
}

//描画
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