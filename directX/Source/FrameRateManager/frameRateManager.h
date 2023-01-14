#pragma once

class FrameRateManager
{
private:
	static const int framePerSecond;        //フレーム数
	static const float waitingTimeOffset;   //待つ時間のオフセット

	//パフォーマンスカウンター
	bool performanceCounter;
	LARGE_INTEGER freq, startCount, finishCount;
	float count;

public:
	FrameRateManager();
	~FrameRateManager();

	//フレームのスタート時間をセットする
	void setStartCount();
	//指定のフレームになるように余った時間を待つ
	void stopTime();

private:

};
