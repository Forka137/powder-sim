#pragma once
#include "GUIElement.h"
#include "raylib.h"
#include <string>

class TemporalText : public GUIElement {
public:
	TemporalText(std::string label, Font font);
	TemporalText(std::string label, Vector2 position, Font font);
	TemporalText(std::string label, Vector2 position, float screenTime, Font font);

	void Draw();
	void Update(float deltaTime);

	Color TextColor = RAYWHITE;
	float Opacity = 255.0;
	void SetLabel(std::string label);
	void Show();
	void Hide();
	std::string GetLabel();
	void SetScreenTime(float time);
	Font ttfFont;

private:
	std::string _label;
	Vector2 _position = { 0, 0 };
	float _screenTime = 1.0; // in seconds
};

