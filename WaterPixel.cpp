#include "WaterPixel.h"
#include "Globals.h"
#include "raylib.h"
#include "CellStatus.h"
//#include <iostream>
//#include <string>

// Posiciones
//  0   1    2
//  3   4(p) 5
//	6	7	 8

WaterPixel::WaterPixel(Vector2 createdPosition) {
	_type = Powder::Type::Water;
	_position = createdPosition;
	nCells = std::vector<CellStatus>(9, CellStatus()); // Fill vector

	// std::cout << "Pixel Created" << std::endl;
}

WaterPixel::~WaterPixel() {
	// std::cout << "Pixel Destroyed" << std::endl;
}

void WaterPixel::Update(float deltaTime) {
	// Water logic

	if (nCells[7].free == true) {
		_position.y += 1 * Globals::Scale;
	}
	else if (nCells[6].free && nCells[3].free) {
		_position.x -= 1 * Globals::Scale;
		_position.y += 1 * Globals::Scale;
	}
	else if (nCells[8].free && nCells[5].free) {
		_position.x += 1 * Globals::Scale;
		_position.y += 1 * Globals::Scale;
	}
	else if (nCells[3].free) {
		_position.x -= 1 * Globals::Scale;
		_position.y;
	}
	else if (nCells[5].free) {
		_position.x += 1 * Globals::Scale;
		_position.y;
	}

	// Debug
	// std::cout << std::to_string(int(nCells[0].type)) + std::to_string(int(nCells[1].type)) + std::to_string(int(nCells[2].type)) + '\n' << std::endl;
	// std::cout << std::to_string(int(nCells[3].type)) + std::to_string(int(nCells[4].type)) + std::to_string(int(nCells[5].type)) + '\n' << std::endl;
	// std::cout << std::to_string(int(nCells[6].type)) + std::to_string(int(nCells[7].type)) + std::to_string(int(nCells[8].type)) + "\n\n" << std::endl;
}

void WaterPixel::Draw() {
	if (Globals::Scale > 1) {
		DrawRectangle(_position.x, _position.y, Globals::Scale, Globals::Scale, _color);
	}
	else {
		DrawPixel(_position.x, _position.y, _color);
	}
}
