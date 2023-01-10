#pragma once

//=========================================
// GameSystemクラス
// ・このゲームの土台となるもの
//=========================================
class GameSystem
{
private:
	//画面をクリアする色
	static const float clearColor[4];
	//フレームレートを固定にするためのクラス
	FrameRateManager frameRateManager = {};
	//ゲームシーン
	GameScene* gameScene = nullptr;

public:

	// このゲームの初期設定を行う
	bool initialize(HWND hWnd, HINSTANCE hInst);

	// このゲーム世界の時間を進める(処理を実行する)
	void execute();

	//終了処理
	void terminate();

private:
	void initializeShapes();
	void terminateShapes();

//=========================================
//シングルトンパターン
//=========================================
private:
	// 唯一のインスタンス用のポインタ
	static inline GameSystem* s_instance;
	// コンストラクタはprivateにする
	GameSystem() {}

public:
	// インスタンス作成
	static void createInstance()
	{
		deleteInstance();

		s_instance = new GameSystem();
	}
	// インスタンス削除
	static void deleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	// 唯一のインスタンスを取得
	static GameSystem& getInstance()
	{
		return *s_instance;
	}
};

// GameSystemの唯一のインスタンスを簡単に取得するためのマクロ
#define GAMESYS GameSystem::getInstance()