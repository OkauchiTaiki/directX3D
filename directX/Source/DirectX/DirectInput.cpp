#include "framework.h"
#include "Source\environment.h"

LPDIRECTINPUT8			DirectInput::pDI = NULL;				// DirectInputオブジェクト
LPDIRECTINPUTDEVICE8	DirectInput::pDIKeyboard = NULL;		// keyboard
LPDIRECTINPUTDEVICE8	DirectInput::pDIMouse = NULL;			// mouse

DIMOUSESTATE2	DirectInput::diMouse;	// マウスの状態
int				DirectInput::Mouse_x;	// マウスの座標X
int				DirectInput::Mouse_y;	// マウスの座標Y
BYTE			DirectInput::diKeyboard[256];	// キーボード用
BYTE			DirectInput::oldKeyboard[256];	// 1フレーム前のキーボードの状態

HRESULT DirectInput::initialize(HINSTANCE hInst)
{
	HRESULT	hr;

	//IDirectInput8インターフェイスの取得
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDI, NULL);
	if (FAILED(hr))
	{
		return hr;
	}

	//IDirectInputDevice8インターフェイスの取得
	//マウス
	hr = pDI->CreateDevice(GUID_SysMouse, &pDIMouse, NULL);
	if (FAILED(hr))
	{
		terminate();
		return E_FAIL;
	}
	hr = pDIMouse->SetDataFormat(&c_dfDIMouse2);//データフォーマットの設定
	if (FAILED(hr))
	{
		terminate();
		return E_FAIL;
	}

	//キーボード
	hr = pDI->CreateDevice(GUID_SysKeyboard, &pDIKeyboard, NULL);
	if (FAILED(hr))
	{
		terminate();
		return E_FAIL;
	}
	hr = pDIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		terminate();
		return E_FAIL;
	}

	return	S_OK;
}

void DirectInput::terminate()
{
	//入力制御停止
	if (pDIKeyboard)	pDIKeyboard->Unacquire();
	SAFE_RELEASE(pDIKeyboard);

	//入力制御停止
	if (pDIMouse)	pDIMouse->Unacquire();
	SAFE_RELEASE(pDIMouse);
	SAFE_RELEASE(pDI);
}

void DirectInput::setMousePosition(int x, int y)
{
	Mouse_x = x;
	Mouse_y = y;
}

void DirectInput::KeyManager()
{
	HRESULT hr;

	//マウス
	hr = pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &diMouse);
	if (FAILED(hr))
	{
		//入力制御開始
		hr = pDIMouse->Acquire();
	}

	//キーボード
	memcpy(oldKeyboard, diKeyboard, sizeof(oldKeyboard));	//前フレームのキー状態を保存
	hr = pDIKeyboard->GetDeviceState(256, diKeyboard);
	if (FAILED(hr))
	{
		//入力制御開始
		hr = pDIKeyboard->Acquire();
	}

	//マウスの状態を設定
	Mouse::setMouseStatus();
}

int DirectInput::getMouseX()
{
	return Mouse_x;
}

int DirectInput::getMouseY()
{
	return Mouse_y;
}

DIMOUSESTATE2* DirectInput::getMouseState()
{
	return &diMouse;
}

BYTE* DirectInput::getCurrentKeyboardState()
{
	return diKeyboard;
}

BYTE* DirectInput::getOldKeyboardState()
{
	return oldKeyboard;
}