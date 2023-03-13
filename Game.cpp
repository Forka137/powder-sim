#pragma once
#include "Game.h"
#include "raylib.h"
#include <string>
#include <memory>
#include "MainGUI.h"
#include "StaticText.h"
#include "Globals.h"
#include "GridPlane.h"

Game::Game() {
	// Nada de la raylib puede ir antes de InitWindow, por lo tanto el constructor de Game queda vacío
}

Game::~Game() {

}

void Game::Initialize(std::string title) {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(Globals::WindowWidth, Globals::WindowHeight, title.c_str());
	// SetTargetFPS(60); // Adjust to screen refresh rate
	// SetExitKey(0); // Disables ESC_KEY for Exit
	_mainGUI = std::make_unique<MainGUI>();
	_mainGrid = std::make_unique<GridPlane>();
}

void Game::RunLoop() {
	while (!WindowShouldClose()) {
		ProcessInput();
		Update();
		DrawObjects();
	}
}

void Game::Terminate() {
	CloseWindow();
}

void Game::Update() {
	float deltaTime = GetFrameTime();
	_pTickCounter += deltaTime;
	_mainGUI->Update(deltaTime);

	// Grid contiene la física del juego por lo que se actualizará con un tickRate en vez de FPS
	if (_pTickCounter > 1.0 / float(Globals::TickRate)) {
		_pTickCounter = 0.0f;
		_mainGrid->Update(deltaTime);
	}

	_mainGUI->totalActivePixels = _mainGrid->GetActivePixels();
}

// Private Methods
void Game::DrawObjects() {
	BeginDrawing();
	ClearBackground(BLACK);
	_mainGrid->Draw();
	_mainGUI->Draw();
	EndDrawing();
}

void Game::ProcessInput() {
	// Keyboard and mouse input
	_mainGUI->GetInput();
	_mainGrid->GetInput();

	//Global detections
	if (IsKeyDown(KEY_UP)) {
		if (Globals::TickRate < 144) {
			Globals::TickRate += 1;
		}
	}

	if (IsKeyDown(KEY_DOWN)) {
		if (Globals::TickRate > 1) {
			Globals::TickRate -= 1;
		}
	}

	if (_mainGUI->_leftScale->IsPressed()) {
		if (Globals::Scale > 1) {
			Globals::Scale -= 1;
			_mainGrid->Reset();
		}
	}

	if (_mainGUI->_rightScale->IsPressed()) {
		if (Globals::Scale < 20) {
			Globals::Scale += 1;
			_mainGrid->Reset();
		}
	}

	if (_mainGUI->_rightBrush->IsPressed()) {
		if (Globals::bSize < 6) {
			Globals::bSize += 1;
		}
	}

	if (_mainGUI->_leftBrush->IsPressed()) {
		if (Globals::bSize > 1) {
			Globals::bSize -= 1;
		}
	}

	if (IsKeyPressed(KEY_A)) {
		Globals::SelectedMaterial = Powder::Type::Sand;
	}

	if (IsKeyPressed(KEY_S)) {
		Globals::SelectedMaterial = Powder::Type::Water;
	}

	if (IsKeyPressed(KEY_D)) {
		Globals::SelectedMaterial = Powder::Type::Rock;
	}

	if (IsKeyPressed(KEY_R)) {
		_mainGrid->Reset();
	}
}