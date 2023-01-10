#pragma once

class DirectInput
{
private:
	static LPDIRECTINPUT8		pDI;					// DirectInput�I�u�W�F�N�g
	static LPDIRECTINPUTDEVICE8	pDIKeyboard;			// �f�o�C�X:keyboard
	static LPDIRECTINPUTDEVICE8	pDIMouse;				// �f�o�C�X:mouse

	static DIMOUSESTATE2	diMouse;			// �}�E�X�p
	static int				Mouse_x;			// �}�E�X�̍��W
	static int				Mouse_y;			// �}�E�X�̍��W
	static BYTE				diKeyboard[256];	// �L�[�{�[�h�p
	static BYTE				oldKeyboard[256];	// 1�t���[���O�̃L�[�{�[�h�̏��

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
