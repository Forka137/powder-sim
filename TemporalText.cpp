#pragma once
#include "TemporalText.h"
#include "raylib.h"
#include <iostream>
#include <string>

TemporalText::TemporalText(std::string label, Font font) {
	_label = label;
	_screenTime = 1.0;
	ttfFont = font;
}

TemporalText::TemporalText(std::string label, Vector2 position, Font font) {
	_label = label;
	_position = position;
	_screenTime = 1.0;
	ttfFont = font;
}


TemporalText::TemporalText(std::string label, Vector2 position, float screenTime, Font font) {
	_label = label;
	_position = position;
	_screenTime = screenTime;
	ttfFont = font;
}

void TemporalText::SetLabel(std::string label) {
	Show();
	_label = label;
}

std::string TemporalText::GetLabel() {
	return _label;
}

void TemporalText::SetScreenTime(float time) {
	_screenTime = time;
}

void TemporalText::Show() {
	Opacity = 255;
}

void TemporalText::Hide() {
	Opacity = 0;
}

void TemporalText::Draw() {
	// std::cout << "Dibujando texto" << std::endl;
	if (Opacity > 0) {
		DrawTextEx(ttfFont, _label.c_str(), _position, (float)ttfFont.baseSize, 2, { TextColor.r, TextColor.g, TextColor.b, (unsigned char)Opacity});
	}
}

void TemporalText::Update(float deltaTime) {
	if (Opacity > 0) {
		Opacity = Opacity - ((deltaTime * 255.0f) / _screenTime);
	}
	if (Opacity < 0) {
		Opacity = 0.0f;
	}
}