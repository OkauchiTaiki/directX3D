#include "framework.h"
#include "Source\environment.h"

int	Mouse::x = 0;
int	Mouse::y = 0;
int	Mouse::r = 0;
int	Mouse::dx = 0;
int Mouse::dy = 0;
int	Mouse::On = 0;
int	Mouse::Trg = 0;
int	Mouse::Rel = 0;

int	Mouse::getX(void) { return x; }
int	Mouse::getY(void) { return y; }
int	Mouse::getR(void) { return r; }
int	Mouse::getDX(void) { return dx; }
int	Mouse::getDY(void) { return dy; }
bool Mouse::on(eButton btn) { return btn & On ? true : false; }
bool Mouse::trg(eButton btn) { return btn & Trg ? true : false; }
bool Mouse::rel(eButton btn) { return btn & Rel ? true : false; }

void Mouse::setMouseStatus(void)
{
	x = DirectInput::getMouseX();
	y = DirectInput::getMouseY();
	r = DirectInput::getMouseState()->lZ;
	dx = DirectInput::getMouseState()->lX;
	dy = DirectInput::getMouseState()->lY;
	int Old = On;
	On = 0;
	if (DirectInput::getMouseState()->rgbButtons[0])   On |= LT;
	if (DirectInput::getMouseState()->rgbButtons[1])   On |= RT;
	if (DirectInput::getMouseState()->rgbButtons[2])   On |= MD;

	Trg = (On ^ Old) & On;
	Rel = (On ^ Old) & Old;
}