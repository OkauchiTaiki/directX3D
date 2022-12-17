#pragma once

//=========================================
// GameSystemクラス
// ・このゲームの土台となるもの
//=========================================
class GameSystem
{
public:

	// このゲームの初期設定を行う
	void initialize();

	// このゲーム世界の時間を進める(処理を実行する)
	void execute();

	// その他、ゲーム用のデータなどをココに書く

//=========================================
// 今回このクラスも、どこからでもアクセスできるように
// シングルトンパターンにしておきます。
// ↓↓↓以下、シングルトンパターンのコード
//=========================================
private:
	// 唯一のインスタンス用のポインタ
	static inline GameSystem* s_instance;
	// コンストラクタはprivateにする
	GameSystem() {}
	float rotation = 0.0f;
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