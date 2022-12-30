#include "framework.h"
#include "Source\environment.h"

const float GroundLines::length = 60.0f;
const float GroundLines::distance = 2.0f;
const XMFLOAT4 GroundLines::color = { 0.6f, 0.6f, 0.6f, 0.6f };

GroundLines::GroundLines()
{
	//xé≤Ç…ïΩçsÇ»ê¸
	for (int i = 0; i < horizontalLineNum; i++)
	{
		horizontalLines[i] = new Line(XMFLOAT3(0.0f, 0.0f, distance * (float)(-horizontalLineNum / 2 + i)), length, color);
	}
	//zé≤Ç…ïΩçsÇ»ê¸
	for (int i = 0; i < verticalLineNum; i++)
	{
		verticalLines[i] = new Line(XMFLOAT3(distance * (float)(-verticalLineNum / 2 + i), 0.0f, 0.0f), length, color);
		verticalLines[i]->rotateLocalAxisY(PI / 2.0f);
	}
}

GroundLines::~GroundLines()
{
	for (int i = 0; i < horizontalLineNum; i++)
	{
		delete horizontalLines[i];
	}
	for (int i = 0; i < verticalLineNum; i++)
	{
		delete verticalLines[i];
	}
}

void GroundLines::render()
{
	for (int i = 0; i < horizontalLineNum; i++)
	{
		horizontalLines[i]->render();
	}
	for (int i = 0; i < verticalLineNum; i++)
	{
		verticalLines[i]->render();
	}
}