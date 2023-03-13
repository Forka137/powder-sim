#include "StaticText.h"
#include "raylib.h"
#include <iostream>
#include <string>

StaticText::StaticText(std::string label,Font font) {
	_label = label;
	ttfFont = font;
}

StaticText::StaticText(std::string label, Vector2 position,Font font) {
	_label = label;
	_position = position;
	ttfFont = font;
}

void StaticText::SetLabel(std::string label) {
	Show();
	_label = label;
}

std::string StaticText::GetLabel() {
	return _label;
}

void StaticText::Show() {
	Opacity = 255;
}

void StaticText::Hide() {
	Opacity = 0;
}

void StaticText::Draw() {
	if (Opacity > 0) {
		DrawTextEx(ttfFont, _label.c_str(), _position, (float)ttfFont.baseSize, 2, { TextColor.r, TextColor.g, TextColor.b, (unsigned char)Opacity });
	}
}

void StaticText::Update(float deltaTime) {
	// Nothing
}
