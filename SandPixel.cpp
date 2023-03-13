#pragma once
#include "SandPixel.h"
#include "Globals.h"
#include "raylib.h"
#include "CellStatus.h"
// #include <iostream>
// #include <string>

// Posiciones
//  0   1    2
//  3   4(p) 5
//	6	7	 8

SandPixel::SandPixel(Vector2 createdPosition) {
	_type = Powder::Type::Sand;
	_position = createdPosition;
	nCells = std::vector<CellStatus>(9, CellStatus()); // Fill vector

	// std::cout << "Pixel Created" << std::endl;
}

SandPixel::~SandPixel() {
	// std::cout << "Pixel Destroyed" << std::endl;
}

void SandPixel::Update(float deltaTime) {
	// Si abajo está disponible cae por "gravedad"
	if (nCells[7].free == true) {
		_position.y += 1 * Globals::Scale;
	}
	else if (nCells[6].free == true && nCells[3].free) {
		_position.x -= 1 * Globals::Scale;
		_position.y += 1 * Globals::Scale;
	}
	else if (nCells[8].free == true && nCells[5].free) {
		_position.x += 1 * Globals::Scale;
		_position.y += 1 * Globals::Scale;
	}
}

void SandPixel::Draw() {
	if (Globals::Scale > 1) {
		DrawRectangle(_position.x, _position.y, Globals::Scale, Globals::Scale, _color);
	}
	else {
		DrawPixel(_position.x, _position.y, _color);
	}	
}