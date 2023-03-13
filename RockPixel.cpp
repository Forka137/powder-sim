#pragma once
#include "RockPixel.h"
#include "Globals.h"
#include "raylib.h"
#include "CellStatus.h"

// Posiciones
//  0   1    2
//  3   4(p) 5
//	6	7	 8

RockPixel::RockPixel(Vector2 createdPosition) {
	_type = Powder::Type::Rock;
	_position = createdPosition;
	nCells = std::vector<CellStatus>(9, CellStatus()); // Fill vector
	// std::cout << "Pixel Created" << std::endl;
}

RockPixel::~RockPixel() {
	// std::cout << "Pixel Destroyed" << std::endl;
}

void RockPixel::Update(float deltaTime) {
	// La roca se pega a otras rocas
	// Si no hay más rocas, cae
	if (nCells[3].type == Powder::Type::Rock || nCells[5].type == Powder::Type::Rock) {
		return;
	}
	else if (nCells[7].free == true) {
		_position.y += 1 * Globals::Scale;
	}
}

void RockPixel::Draw() {
	if (Globals::Scale > 1) {
		DrawRectangle(_position.x, _position.y, Globals::Scale, Globals::Scale, _color);
	}
	else {
		DrawPixel(_position.x, _position.y, _color);
	}
}