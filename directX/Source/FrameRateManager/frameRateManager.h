#pragma once

class FrameRateManager
{
private:
	static const int framePerSecond;        //�t���[����
	static const float waitingTimeOffset;   //�҂��Ԃ̃I�t�Z�b�g

	//�p�t�H�[�}���X�J�E���^�[
	bool performanceCounter;
	LARGE_INTEGER freq, startCount, finishCount;
	float count;

public:
	FrameRateManager();
	~FrameRateManager();

	//�t���[���̃X�^�[�g���Ԃ��Z�b�g����
	void setStartCount();
	//�w��̃t���[���ɂȂ�悤�ɗ]�������Ԃ�҂�
	void stopTime();

private:

};
