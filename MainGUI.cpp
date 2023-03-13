#pragma once
#include "MainGUI.h"
#include "TextButton.h"
#include "TemporalText.h"
#include "StaticText.h"
#include <memory>
#include <iostream>
#include "Globals.h"


MainGUI::MainGUI() {
	// Help Button
	_helpButton = std::make_unique<TextButton>("Controls", _font);
	_leftScale = std::make_unique<TextButton>("<", Vector2{ 420.0, float(Globals::WindowHeight) - 38 }, _font);
	_rightScale = std::make_unique<TextButton>(">", Vector2{ 440.0, float(Globals::WindowHeight) - 38 }, _font);

	_brushText = std::make_unique<StaticText>(
		"Brush\nSize: " + std::to_string(Globals::bSize),
		Vector2{ 480.0, float(Globals::WindowHeight) - 60 },
		_font
		);
	_leftBrush = std::make_unique<TextButton>("<", Vector2{ 570.0, float(Globals::WindowHeight) - 38 }, _font);
	_rightBrush = std::make_unique<TextButton>(">", Vector2{ 590.0, float(Globals::WindowHeight) - 38 }, _font);

	_helpText = std::make_unique<TemporalText>(
		"Left Click:    Creates pixels\n"
		"Right Click:   Deletes pixels\n"
		"Up/Down:       Changes the Tick Rate\n"
		"R:             Deletes everything\n"
		"A,S,D:         Change between materials\n\n"
		"Maximum Tick Rate is giving by computer performance",
		Vector2{100.0, 100.0}, 10.0, _font);

	_totalPixelsText = std::make_unique<StaticText>(
		"Total\nPixels: 0",
		Vector2{ float(Globals::WindowWidth) - 160, 20},
		_font
		);

	_tickText = std::make_unique<StaticText>(
		"Target Tick rate: " + std::to_string(Globals::TickRate) + "\n"
		"Current Maximum: " + maxTRString,
		Vector2{ 20, float(Globals::WindowHeight) - 60 },
		_font
		);

	_scaleText = std::make_unique<StaticText>(
		"Scale: " + std::to_string(Globals::Scale),
		Vector2{ 300.0, float(Globals::WindowHeight) - 36 },
		_font
		);

	_materialText = std::make_unique<StaticText>(
		"Material: ",
		Vector2{ 270.0, float(Globals::WindowHeight) - 60 },
		_font
		);

	_materialValue = std::make_unique<StaticText>(
		"Sand",
		Vector2{ 370.0, float(Globals::WindowHeight) - 60 },
		_font
		);
	_materialValue->TextColor = GOLD;

	_signatureText = std::make_unique<TemporalText>(
		"Forka137 - 2023 ",
		Vector2{ 630.0, float(Globals::WindowHeight) - 30 }, 10.0, _font);

	_signatureText->TextColor = GOLD;
	
	_helpText->Opacity = 0;

	// Elements added for its Update and Draw
	AddElement(_helpButton.get());
	AddElement(_helpText.get());
	AddElement(_totalPixelsText.get());
	AddElement(_tickText.get());
	AddElement(_scaleText.get());
	AddElement(_leftScale.get());
	AddElement(_rightScale.get());
	AddElement(_brushText.get());
	AddElement(_leftBrush.get());
	AddElement(_rightBrush.get());
	AddElement(_materialText.get());
	AddElement(_materialValue.get());
	AddElement(_signatureText.get());
}

void MainGUI::GetInput() {
	ShowHelp();
}

void MainGUI::ShowHelp() {
	if (_helpButton->IsDown()) {
		_helpText->Show();
	}
}

void MainGUI::TickCalculation(float deltaTime) {
	int calc = 1.0f / deltaTime;
	maxTRString = std::to_string(calc);
}

// Override method
void MainGUI::Update(float deltaTime) {
	for (int i = 0; i < _elements.size(); i++) {
		_elements[i]->Update(deltaTime);
	}
	timeOut += deltaTime;

	if (timeOut > 1) {
		TickCalculation(deltaTime);
		timeOut = 0.0f;
	}
	
	// Update extra elements
	_tickText.get()->SetLabel("Target Tick rate: " + std::to_string(Globals::TickRate) + '\n' + "Current Maximum: " + maxTRString);
	_totalPixelsText.get()->SetLabel("Total\nPixels: " + std::to_string(totalActivePixels));
	_scaleText.get()->SetLabel("Scale: " + std::to_string(Globals::Scale));
	_brushText.get()->SetLabel("Brush\nSize: " + std::to_string(Globals::bSize));

	// Material Selection
	if (Globals::SelectedMaterial == Powder::Type::Sand) {
		_materialValue.get()->SetLabel("Sand");
		_materialValue.get()->TextColor = GOLD;
	} 
	else if (Globals::SelectedMaterial == Powder::Type::Water) {
		_materialValue.get()->SetLabel("Water");
		_materialValue.get()->TextColor = SKYBLUE;
	}
	else if (Globals::SelectedMaterial == Powder::Type::Rock) {
		_materialValue.get()->SetLabel("Rock");
		_materialValue.get()->TextColor = GRAY;
	}
}