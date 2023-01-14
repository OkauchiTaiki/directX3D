#pragma once

class GroundLines
{
private:
	static const int horizontalLineNum = 31;
	static const int verticalLineNum = 31;
	static const float length;
	static const float distance;
	static const XMFLOAT4 color;

	std::vector<Line*> horizontalLines{ horizontalLineNum };
	std::vector<Line*> verticalLines{verticalLineNum};

public:
	GroundLines();
	~GroundLines();

	void render();
};
