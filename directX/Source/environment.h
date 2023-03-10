#pragma once

//ライブラリ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")

//DirectXのヘッダー
#include <d3d11.h>
#include <d3dcompiler.h>
#define	DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

#include <DirectXMath.h>

//DirectXのネームスペース
using namespace DirectX;

//画面サイズ
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720
//リリース
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}

// ComPtrを使用できるようにする
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

//フレームワークヘッダー
#include "DirectX\Direct3D.h"
#include "DirectX\DirectInput.h"
#include "DirectX\XMFloatOperator.h"

#include "FrameRateManager\frameRateManager.h"   //フレームレートを管理するクラス
#include "OriginalMath\OriginalMath.h"           //数学関連の定数や関数
#include "Input\Keyboard.h"
#include "Input\Mouse.h"

//ゲーム内で使うクラスのヘッダー
#include "Game\Object\Object.h"
#include "Game\Camera\Camera.h"
#include "Game\Light\DirectionalLight.h"
#include "Game\CollisionDetection\CollisionDetection.h"
#include "Game\Object\Line.h"
#include "Game\Object\RectAngle.h"
#include "Game\Object\Cube.h"
#include "Game\Object\Sphere.h"
#include "Game\EnvironmentObjects\GroundLines.h"

#include "Game\Character\Bullet\Bullet.h"
#include "Game\Character\Player\Player.h"
#include "Game\Character\Enemy\Enemy.h"

//ゲーム本体のヘッダー
#include "Game\Scene\GameScene.h"
#include "Game\GameSystem.h"
