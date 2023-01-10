#include "framework.h"
#include "Source\environment.h"

LPDIRECTINPUT8			DirectInput::pDI = NULL;				// DirectInput�I�u�W�F�N�g
LPDIRECTINPUTDEVICE8	DirectInput::pDIKeyboard = NULL;		// keyboard
LPDIRECTINPUTDEVICE8	DirectInput::pDIMouse = NULL;			// mouse

DIMOUSESTATE2	DirectInput::diMouse;	// �}�E�X�̏��
int				DirectInput::Mouse_x;	// �}�E�X�̍��WX
int				DirectInput::Mouse_y;	// �}�E�X�̍��WY
BYTE			DirectInput::diKeyboard[256];	// �L�[�{�[�h�p
BYTE			DirectInput::oldKeyboard[256];	// 1�t���[���O�̃L�[�{�[�h�̏��

HRESULT DirectInput::initialize(HINSTANCE hInst)
{
	HRESULT	hr;

	//IDirectInput8�C���^�[�t�F�C�X�̎擾
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDI, NULL);
	if (FAILED(hr))
	{
		return hr;
	}

	//IDirectInputDevice8�C���^�[�t�F�C�X�̎擾
	//�}�E�X
	hr = pDI->CreateDevice(GUID_SysMouse, &pDIMouse, NULL);
	if (FAILED(hr))
	{
		terminate();
		return E_FAIL;
	}
	hr = pDIMouse->SetDataFormat(&c_dfDIMouse2);//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(hr))
	{
		terminate();
		return E_FAIL;
	}

	//�L�[�{�[�h
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
	//���͐����~
	if (pDIKeyboard)	pDIKeyboard->Unacquire();
	SAFE_RELEASE(pDIKeyboard);

	//���͐����~
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

	//�}�E�X
	hr = pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &diMouse);
	if (FAILED(hr))
	{
		//���͐���J�n
		hr = pDIMouse->Acquire();
	}

	//�L�[�{�[�h
	memcpy(oldKeyboard, diKeyboard, sizeof(oldKeyboard));	//�O�t���[���̃L�[��Ԃ�ۑ�
	hr = pDIKeyboard->GetDeviceState(256, diKeyboard);
	if (FAILED(hr))
	{
		//���͐���J�n
		hr = pDIKeyboard->Acquire();
	}

	//�}�E�X�̏�Ԃ�ݒ�
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