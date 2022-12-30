#pragma once

//���C�u����
#pragma comment(lib, "winmm.lib")

//��ʃT�C�Y
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

#include "DirectX\Direct3D.h"
#include "DirectX\XMFloatOperator.h"
#include "FrameRateManager\frameRateManager.h"   //�t���[�����[�g���Ǘ�����N���X
#include "OriginalMath\OriginalMath.h"           //���w�֘A�̒萔��֐�

//�Q�[�����Ŏg���N���X�̃w�b�_�[
#include "Game\Camera\Camera.h"
#include "Game\Light\DirectionalLight.h"
#include "Game\Object\Object.h"
#include "Game\Object\Line.h"
#include "Game\Object\RectAngle.h"
#include "Game\Object\Cube.h"
#include "Game\EnvironmentObjects\GroundLines.h"

//�Q�[���{�̂̃w�b�_�[
#include "Game\GameSystem.h"
