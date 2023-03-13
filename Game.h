#pragma once
#include <string>
#include "MainGUI.h"
#include <memory>
#include "GridPlane.h"

class Game
{
public:
	Game();
	~Game();

	void Initialize(std::string title);
	void RunLoop();
	void Terminate();

private:
	void ProcessInput();
	void Update();
	void DrawObjects();

	std::unique_ptr<MainGUI> _mainGUI;
	std::unique_ptr<GridPlane> _mainGrid;
	float _pTickCounter = 0.0f;			// Physics tick counter
};

