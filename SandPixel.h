#pragma once
#include "BasePixel.h"
#include "raylib.h"
#include <vector>
#include "Globals.h"

class SandPixel : public BasePixel {

public:
	SandPixel(Vector2 createdPosition);
	~SandPixel();
	void Update(float deltaTime);
	void Draw();
	
private:
	Color _color = GOLD;
};