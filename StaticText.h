#pragma once
#include "GUIElement.h"
#include "raylib.h"
#include <string>
class StaticText : public GUIElement
{
public:
	StaticText(std::string label, Font font);
	StaticText(std::string label, Vector2 position, Font font);

	void Draw();
	void Update(float deltaTime);

	Color TextColor = RAYWHITE;
	int Opacity = 255;

	void Show();
	void Hide();
	void SetLabel(std::string label);
	std::string GetLabel();
	Font ttfFont;

	// Add font size method

private:
	std::string _label;
	Vector2 _position = { 0, 0 };
};

