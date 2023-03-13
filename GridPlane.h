#pragma once
#include "BasePixel.h"
#include "raylib.h"
#include <vector>
#include <memory>
#include "Globals.h"
#include "CellStatus.h"

class GridPlane {

public:
	GridPlane();

	void GetInput();
	void Update(float deltaTime);
	void Draw();

	int GetActivePixels();
	void Reset();

private:
	Vector2 _mousePosition = { 0.0f, 0.0f };
	Vector2 AdjustToGrid(Vector2 mousePosition);
	Vector2 CoordsToGrid(Vector2 coords);

	void CreatePixel(Vector2 coords);
	void DeletePixel(int i);
	
	int GetPixelAtPos(Vector2 mousePosition);

	void CheckBoundaries(BasePixel* pixel);
	void ClearGrid();

	CellStatus CheckNeighbour(int nPos, Vector2 pixelPosition);
	int _activePixels = 0;
	
	std::vector<std::vector<CellStatus>> _grid;
	std::vector<std::unique_ptr<BasePixel>> _pixels;

	// Debe ser vector de unique_ptr para evitar object slicing
	
	// Add available spaces, mouse interaction, etc
};