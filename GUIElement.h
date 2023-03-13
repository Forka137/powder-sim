#pragma once
#include "raylib.h"

class GUIElement
{
public:
	Vector2 RectPosition = { 0.0 , 0.0 };
	unsigned int Width = 0;
	unsigned int Height = 0;

	unsigned int LeftPadding = 0;
	unsigned int RightPadding = 0;
	unsigned int TopPadding = 0;
	unsigned int BottomPadding = 0;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};

