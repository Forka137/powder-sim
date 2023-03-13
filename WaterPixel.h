#pragma once
#include "BasePixel.h"
#include "raylib.h"
#include <vector>
#include "Globals.h"

class WaterPixel : public BasePixel {

public:
	WaterPixel(Vector2 createdPosition);
	~WaterPixel();
	void Update(float deltaTime);
	void Draw();

private:
	Color _color = SKYBLUE;
};