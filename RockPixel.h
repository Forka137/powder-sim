#pragma once
#include "BasePixel.h"
#include "raylib.h"
#include <vector>
#include "Globals.h"

class RockPixel : public BasePixel {

public:
	RockPixel(Vector2 createdPosition);
	~RockPixel();
	void Update(float deltaTime);
	void Draw();

private:
	Color _color = GRAY;
};