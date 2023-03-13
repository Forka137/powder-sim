#pragma once
#include "raylib.h"
#include "Globals.h"
#include <vector>
#include "CellStatus.h"


class BasePixel {
public:
	Vector2 GetPosition();
	Powder::Type GetType();

	virtual ~BasePixel(); // Leer archivo .cpp

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	// Positions to be able to move
	std::vector<CellStatus> nCells;	// neighboor cells

protected:
	Powder::Type _type = Powder::Type::Sand;
	Vector2 _position;
};