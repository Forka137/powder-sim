#pragma once
#include "GridPlane.h"
#include "raylib.h"
#include "SandPixel.h"
#include "WaterPixel.h"
#include "RockPixel.h"
#include <memory>
#include <vector>
#include "Globals.h"
#include "CellStatus.h"
#include <iostream>

GridPlane::GridPlane() {
	// No vi mejoras en el rendimiento con esto
	// _pixels.reserve(10000);

	// Se crea una vector de vectores con cada posición de la grilla según Globals::Scale;
	ClearGrid();
}

void GridPlane::GetInput() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		_mousePosition = GetMousePosition();

		if (_mousePosition.x < 0 || _mousePosition.x > Globals::WindowWidth) {
			// Evita generar arena fuera de la pantalla
			return;
		}

		_mousePosition = AdjustToGrid(_mousePosition);

		if (_mousePosition.y < Globals::GroundLevel) {
			if (CheckNeighbour(4, CoordsToGrid(_mousePosition)).free) {
				// 4 significa misma posición

				if (Globals::bSize > 1) {
					// Brush sizes
					for (int i = 0; i < Globals::bSize; i++) {
						for (int j = 0; j < Globals::bSize; j++) {
							_mousePosition.x += i * Globals::Scale;
							_mousePosition.y += j * Globals::Scale;
							if (CheckNeighbour(4, CoordsToGrid(_mousePosition)).free) CreatePixel(_mousePosition);
							_mousePosition.x -= i * Globals::Scale;
							_mousePosition.y -= j * Globals::Scale;
						}
					}
				}
				else {
					// Create pixel normally
					CreatePixel(_mousePosition);
				}
			}
		}
	}

	else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		// Delete Pixel
		_mousePosition = GetMousePosition();
		if (_mousePosition.x < 0 || _mousePosition.x > Globals::WindowWidth) {
			return;
		}
		_mousePosition = AdjustToGrid(_mousePosition);

		if (_mousePosition.y <= Globals::GroundLevel) {
			if (Globals::bSize > 1) {
				// Oversize delete
				for (int i = 0; i < Globals::bSize; i++) {
					for (int j = 0; j < Globals::bSize; j++) {
						_mousePosition.x += i * Globals::Scale;
						_mousePosition.y += j * Globals::Scale;
						int pixelIndex = GetPixelAtPos(_mousePosition);
						if (pixelIndex > -1)  DeletePixel(pixelIndex);
						_mousePosition.x -= i * Globals::Scale;
						_mousePosition.y -= j * Globals::Scale;
					}
				}
			}
			else {
				// delete normally
				int pixelIndex = GetPixelAtPos(_mousePosition);
				if (pixelIndex > -1) {
					DeletePixel(pixelIndex);
				}
			}
		}
	}
}

void GridPlane::Update(float deltaTime) {
	// Collision check
	for (int i = 0; i < _pixels.size(); i++) {
		CheckBoundaries(_pixels[i].get());
		Vector2 prevGridPos = CoordsToGrid(_pixels[i]->GetPosition());
		// Update pixel and add to virtual grid after movement

		_pixels[i]->Update(deltaTime);
		Vector2 gridPos = CoordsToGrid(_pixels[i]->GetPosition());

		// If pixel changed position update
		if (prevGridPos.x != gridPos.x || prevGridPos.y != gridPos.y) {

			_grid[prevGridPos.x][prevGridPos.y] = CellStatus();

			_grid[gridPos.x][gridPos.y].free = false;
			_grid[gridPos.x][gridPos.y].type = _pixels[i]->GetType();
		}
	}
	_activePixels = _pixels.size();

// debug
	/*for (int j = 0; j < _grid[0].size(); j++) {
		for (int i = 0; i < _grid.size(); i++) {
			std::cout << int(_grid[i][j].type);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/
}

void GridPlane::Draw() {
	for (int i = 0; i < _pixels.size(); i++) {
		_pixels[i]->Draw();
	}
}

void GridPlane::CreatePixel(Vector2 coords) {
	Vector2 gridPos = CoordsToGrid(coords);
	// Porsiaca
	if (gridPos.x >= _grid.size() || gridPos.y >= _grid[0].size()) return;

	_grid[gridPos.x][gridPos.y].free = false;

	// Create pixel in real coordinates
	// Add pixel to virtual grid

	if (Globals::SelectedMaterial == Powder::Type::Sand) {
		_pixels.push_back(std::make_unique<SandPixel>(coords));
		_grid[gridPos.x][gridPos.y].type = Powder::Type::Sand;
	}
	else if (Globals::SelectedMaterial == Powder::Type::Water) {
		_pixels.push_back(std::make_unique<WaterPixel>(coords));
		_grid[gridPos.x][gridPos.y].type = Powder::Type::Water;
	}
	else if (Globals::SelectedMaterial == Powder::Type::Rock) {
		_pixels.push_back(std::make_unique<RockPixel>(coords));
		_grid[gridPos.x][gridPos.y].type = Powder::Type::Rock;
	}
}

int GridPlane::GetActivePixels() {
	return _activePixels;
}

void GridPlane::CheckBoundaries(BasePixel* pixel) {
	// Posiciones
	//  0   1    2
	//  3   4(p) 5
	//	6	7	 8

	// Actualiza la detección de bordes de cada pixel o bloque
	Vector2 posOnGrid = CoordsToGrid(pixel->GetPosition());

	pixel->nCells[1] = CheckNeighbour(1, posOnGrid);
	pixel->nCells[3] = CheckNeighbour(3, posOnGrid);
	pixel->nCells[5] = CheckNeighbour(5, posOnGrid);
	pixel->nCells[6] = CheckNeighbour(6, posOnGrid);
	pixel->nCells[7] = CheckNeighbour(7, posOnGrid);
	pixel->nCells[8] = CheckNeighbour(8, posOnGrid);
}

CellStatus GridPlane::CheckNeighbour(int nPos, Vector2 pixelPosition) {
	Vector2 posToCheck = { 0.0f, 0.0f };
	CellStatus status = CellStatus();

	// Map
	switch (nPos) {
	case 0:
		// TopLeft
		posToCheck.x = pixelPosition.x - 1;
		posToCheck.y = pixelPosition.y - 1;
		break;

	case 1:
		// Top
		posToCheck.x = pixelPosition.x;
		posToCheck.y = pixelPosition.y - 1;
		break;

	case 2:
		// TopRight
		posToCheck.x = pixelPosition.x + 1;
		posToCheck.y = pixelPosition.y - 1;
		break;

	case 3:
		// Left
		posToCheck.x = pixelPosition.x - 1;
		posToCheck.y = pixelPosition.y;
		break;

	case 4:
		// Center
		posToCheck.x = pixelPosition.x;
		posToCheck.y = pixelPosition.y;
		break;

	case 5:
		// Right
		posToCheck.x = pixelPosition.x + 1;
		posToCheck.y = pixelPosition.y;
		break;

	case 6:
		// BottomLeft
		posToCheck.x = pixelPosition.x - 1;
		posToCheck.y = pixelPosition.y + 1;
		break;

	case 7:
		// Bottom
		posToCheck.x = pixelPosition.x;
		posToCheck.y = pixelPosition.y + 1;
		break;

	case 8:
		// BottomRight
		posToCheck.x = pixelPosition.x + 1;
		posToCheck.y = pixelPosition.y + 1;
		break;

	default:
		posToCheck.x = pixelPosition.x;
		posToCheck.y = pixelPosition.y;
	}

	// Checkear techo
	if (posToCheck.y < 0) {
		status.free = false;
		status.type = Powder::Type::Ceiling;
		return status;
	}
	
	// Checkear si está en el suelo
	if (posToCheck.y > int(Globals::GroundLevel / Globals::Scale)) {
		status.free = false;
		status.type = Powder::Type::Ground;
		return status;
	}

	// Checkear si está en los bordes
	if (posToCheck.x < 0 || posToCheck.x >= (Globals::WindowWidth / Globals::Scale)) {
		status.free = false;
		status.type = Powder::Type::Wall;
		return status;
	}

	// Get collision on the selected neighbor
	if (_grid[posToCheck.x][posToCheck.y].free == false) {
		return _grid[posToCheck.x][posToCheck.y];
	}

	// No encontró la posición, debe estar libre
	status.free = true;
	status.type = Powder::Type::Empty;
	return status;
}

int GridPlane::GetPixelAtPos(Vector2 mousePosition) {
	for (int i = 0; i < _pixels.size(); i++) {
		Vector2 newPosition = _pixels[i]->GetPosition();
		if (newPosition.x == mousePosition.x && newPosition.y == mousePosition.y) {
			// Si la posición está ocupada, devuelve la posición del que está ocupando.
			return i;
		}
	}
	return -1;
}

Vector2 GridPlane::AdjustToGrid(Vector2 mousePosition) {
	// Devuelve una posición valida para que siempre se genera algo dentro de la grilla
	if (Globals::Scale > 1) {
		// Esencialmente esto evita que los pixeles queden entre medio de la grilla reducida (escala mayor a 1).
		// Debe devolver la posición menor más cercana, restandole el resto de la división
		int x_remainder = int(mousePosition.x) % Globals::Scale;
		int y_remainder = int(mousePosition.y) % Globals::Scale;

		if (x_remainder != 0) {
			mousePosition.x -= x_remainder;
		}

		if (y_remainder != 0) {
			mousePosition.y -= y_remainder;
		}
	}
	return mousePosition;
}

Vector2 GridPlane::CoordsToGrid(Vector2 coords) {
	// Convierte la posición real en una posición x,y en la grilla
	Vector2 gridPos;
	gridPos.x = int(coords.x / Globals::Scale);
	gridPos.y = int(coords.y / Globals::Scale);

	return gridPos;
}

void GridPlane::ClearGrid() {
	_grid.clear();
	for (int i = 0; i <= int(Globals::WindowWidth / Globals::Scale); i++) {
		_grid.push_back(std::vector<CellStatus>());
		for (int j = 0; j <= int(Globals::GroundLevel / Globals::Scale); j++) {
			_grid[i].push_back(CellStatus());
		}
	}
}

void GridPlane::DeletePixel(int i) {
	if (i >= _pixels.size()) return;

	BasePixel* pixel = _pixels[i].get();
	Vector2 gridPos = CoordsToGrid(pixel->GetPosition());
	_grid[gridPos.x][gridPos.y] = CellStatus();
	_pixels.erase(_pixels.begin() + i);
}

void GridPlane::Reset() {
	// Clearing the vector wont resize it
	_pixels.clear();
	ClearGrid();
}