#pragma once

class DirectInput
{
private:
	static LPDIRECTINPUT8		pDI;					// DirectInputオブジェクト
	static LPDIRECTINPUTDEVICE8	pDIKeyboard;			// デバイス:keyboard
	static LPDIRECTINPUTDEVICE8	pDIMouse;				// デバイス:mouse

	static DIMOUSESTATE2	diMouse;			// マウス用
	static int				Mouse_x;			// マウスの座標
	static int				Mouse_y;			// マウスの座標
	static BYTE				diKeyboard[256];	// キーボード用
	static BYTE				oldKeyboard[256];	// 1フレーム前のキーボードの状態

public:
	static HRESULT initialize(HINSTANCE hInst);
	static void terminate();

	static void setMousePosition(int x, int y);
	static void KeyManager();

	static int getMouseX();
	static int getMouseY();
	static DIMOUSESTATE2* getMouseState();
	static BYTE* getCurrentKeyboardState();
	static BYTE* getOldKeyboardState();
};
