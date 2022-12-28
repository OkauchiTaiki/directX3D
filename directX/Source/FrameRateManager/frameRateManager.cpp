#include "framework.h"
#include "Source\environment.h"

const int FrameRateManager::framePerSecond = 60;
const float FrameRateManager::waitingTimeOffset = 0.5f;

FrameRateManager::FrameRateManager()
{
	//�p�t�H�[�}���X�J�E���^�̏�����
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
	{	//�t���[���̊J�n���Ԃ��擾
		QueryPerformanceCounter(&startCount);
	}
}

void FrameRateManager::stopTime()
{
	//�w��̃t���[���ɂȂ�悤�Ɏ��Ԃ��~�߂�
	if (performanceCounter)
	{	//�t���[���̏I�����Ԃ��擾
		static float frame_msec = 1.0f / (float)framePerSecond;
		QueryPerformanceCounter(&finishCount);
		//(���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
		count = ((float)(finishCount.QuadPart - startCount.QuadPart) / (float)freq.QuadPart);

		if (count < frame_msec)
		{	//1/60�b���o�܂ő҂�
			DWORD wait = (DWORD)((frame_msec - count) * 1000.0f - waitingTimeOffset);
			timeBeginPeriod(1);   //����\���グ��
			Sleep(wait);
			timeEndPeriod(1);     //����\��߂�
		}
	}
}