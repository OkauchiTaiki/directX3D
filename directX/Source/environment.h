#pragma once

//ライブラリ
#pragma comment(lib, "winmm.lib")

//画面サイズ
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

#include "DirectX\Direct3D.h"
#include "DirectX\XMFloatOperator.h"
#include "FrameRateManager\frameRateManager.h"   //フレームレートを管理するクラス
#include "OriginalMath\OriginalMath.h"           //数学関連の定数や関数

//ゲーム内で使うクラスのヘッダー
#include "Game\Camera\Camera.h"
#include "Game\Light\DirectionalLight.h"
#include "Game\Object\Object.h"
#include "Game\Object\Line.h"
#include "Game\Object\RectAngle.h"
#include "Game\Object\Cube.h"
#include "Game\EnvironmentObjects\GroundLines.h"

//ゲーム本体のヘッダー
#include "Game\GameSystem.h"
