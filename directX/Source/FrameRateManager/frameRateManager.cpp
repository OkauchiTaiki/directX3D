#include "framework.h"
#include "Source\environment.h"

const int FrameRateManager::framePerSecond = 60;
const float FrameRateManager::waitingTimeOffset = 0.5f;

FrameRateManager::FrameRateManager()
{
	//パフォーマンスカウンタの初期化
	memset(&freq, 0, sizeof(freq));
	memset(&startCount, 0, sizeof(startCount));
	memset(&finishCount, 0, sizeof(finishCount));
	count = 0.0f;
	performanceCounter = QueryPerformanceFrequency(&freq);
}

FrameRateManager::~FrameRateManager()
{
}

void FrameRateManager::setStartCount()
{
	if (performanceCounter)
	{	//フレームの開始時間を取得
		QueryPerformanceCounter(&startCount);
	}
}

void FrameRateManager::stopTime()
{
	//指定のフレームになるように時間を止める
	if (performanceCounter)
	{	//フレームの終了時間を取得
		static float frame_msec = 1.0f / (float)framePerSecond;
		QueryPerformanceCounter(&finishCount);
		//(今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
		count = ((float)(finishCount.QuadPart - startCount.QuadPart) / (float)freq.QuadPart);

		if (count < frame_msec)
		{	//1/60秒が経つまで待つ
			DWORD wait = (DWORD)((frame_msec - count) * 1000.0f - waitingTimeOffset);
			timeBeginPeriod(1);   //分解能を上げる
			Sleep(wait);
			timeEndPeriod(1);     //分解能を戻す
		}
	}
}