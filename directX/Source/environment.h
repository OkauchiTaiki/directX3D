#pragma once

//ライブラリ
#pragma comment(lib, "winmm.lib")

//画面サイズ
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

#include "DirectX\Direct3D.h"

//ゲーム内で使うクラスのヘッダー
#include "Game\Shape\Shape.h"
#include "Game\Shape\Cube.h"

//ゲーム本体のヘッダー
#include "FrameRateManager\frameRateManager.h"
#include "Game\GameSystem.h"
