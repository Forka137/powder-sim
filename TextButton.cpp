#pragma once
#include "raylib.h"
#include "TextButton.h"
#include <string>
// #include <iostream>

TextButton::TextButton(std::string label, Font font) {
	Label = label;
	ttfFont = font;
	FitInRectangle();
}

TextButton::TextButton(std::string label, Vector2 position, Font font) {
	Label = label;
	RectPosition = position;
	ttfFont = font;
	FitInRectangle();
}

void TextButton::Update(float deltaTime) {
	MouseListening();
}

void TextButton::Draw() {
	DrawRectangle(RectPosition.x, RectPosition.y, Width, Height, BackgroundColor);
	DrawRectangleLines(RectPosition.x, RectPosition.y, Width, Height, BorderColor);
	DrawTextEx(ttfFont, Label.c_str(), _textPosition, FontSize, FontSpacing, TextColor);
}

void TextButton::FitInRectangle() {
	_textColor = TextColor;
	Vector2 textSize = MeasureTextEx(ttfFont, Label.c_str(), FontSize, FontSpacing);
	_minWidth = textSize.x;
	_minHeight = textSize.y;

	Width = LeftPadding + _minWidth + RightPadding;
	Height = TopPadding + _minHeight + BottomPadding;

	_textPosition.x = LeftPadding + RectPosition.x;
	_textPosition.y = TopPadding + RectPosition.y;
}

void TextButton::MouseListening() {
	Vector2 mousePos = GetMousePosition();
	// If mouse inside area
	if (IsInsideRectangle(mousePos)) {
		TextColor = HoverTextColor;
		if (!_mouseEntered) _mouseEntered = true;
		if (_buttonPressed) _buttonPressed = false;

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			// Button Down
			if (!_buttonDown) _buttonDown = true;
			TextColor = ClickedTextColor;

			if (_buttonDown && !_clickedOnce) {
				_clickedOnce = true;
				_buttonPressed = true;
				// std::cout << "clicked Once" << std::endl;
			}
		}
		else if (_buttonDown) {
			// Button Released
			_buttonDown = false;
			_clickedOnce = false;
			// std::cout << "Mouse released" << std::endl;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			TextColor = ClickedTextColor;
		}
	}
	else 
	{
		if (_mouseEntered) {
			// Mouse out
			TextColor = _textColor;
			_mouseEntered = false;
			_buttonDown = false;
			_clickedOnce = false;
			// std::cout << "mouse out" << std::endl;
		}
	}
}

bool TextButton::IsInsideRectangle(Vector2 mousePos) {
	if (mousePos.x > RectPosition.x && mousePos.x < RectPosition.x + Width) {
		if (mousePos.y > RectPosition.y && mousePos.y < RectPosition.y + Height) {
			return true;
		}
	}

	return false;
}

bool TextButton::IsDown() {
	return _buttonDown;
}

bool TextButton::IsPressed() {
	return _buttonPressed;
}

bool TextButton::IsMouseOver() {
	return _mouseEntered;
}