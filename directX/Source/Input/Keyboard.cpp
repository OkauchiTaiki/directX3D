#include "framework.h"
#include "Source\environment.h"

bool Keyboard::on(BYTE key)
{
	BYTE* cur = DirectInput::getCurrentKeyboardState();
	return (cur[key] != 0);
}

bool Keyboard::trg(BYTE key)
{
	BYTE* cur = DirectInput::getCurrentKeyboardState();
	BYTE* old = DirectInput::getOldKeyboardState();
	return (cur[key] != 0 && old[key] == 0);
}

bool Keyboard::rel(BYTE key)
{
	BYTE* cur = DirectInput::getCurrentKeyboardState();
	BYTE* old = DirectInput::getOldKeyboardState();
	return (cur[key] == 0 && old[key] != 0);
}