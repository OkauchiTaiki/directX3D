#pragma once

//���C�u����
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")

//DirectX�̃w�b�_�[
#include <d3d11.h>
#include <d3dcompiler.h>
#define	DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

#include <DirectXMath.h>

//DirectX�̃l�[���X�y�[�X
using namespace DirectX;

//��ʃT�C�Y
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720
//�����[�X
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}

// ComPtr���g�p�ł���悤�ɂ���
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

//�t���[�����[�N�w�b�_�[
#include "DirectX\Direct3D.h"
#include "DirectX\DirectInput.h"
#include "DirectX\XMFloatOperator.h"

#include "FrameRateManager\frameRateManager.h"   //�t���[�����[�g���Ǘ�����N���X
#include "OriginalMath\OriginalMath.h"           //���w�֘A�̒萔��֐�
#include "Input\KeyBoard.h"
#include "Input\Mouse.h"

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
