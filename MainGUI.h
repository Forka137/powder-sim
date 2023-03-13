#pragma once
#include "BaseGUI.h"
#include "TextButton.h"
#include "TemporalText.h"
#include "StaticText.h"
#include <memory>
#include <string>
#include "Globals.h"

class MainGUI :
    public BaseGUI
{
public:
    MainGUI();

    std::unique_ptr<TextButton> _helpButton;
    std::unique_ptr<TextButton> _leftScale;
    std::unique_ptr<TextButton> _rightScale;

    std::unique_ptr<TextButton> _leftBrush;
    std::unique_ptr<TextButton> _rightBrush;

    std::unique_ptr<TemporalText> _helpText;
    std::unique_ptr<TemporalText> _autoText;
    std::unique_ptr<TemporalText> _signatureText;

    std::unique_ptr<StaticText> _totalPixelsText;
    std::unique_ptr<StaticText> _tickText;
    std::unique_ptr<StaticText> _scaleText;
    std::unique_ptr<StaticText> _materialText;
    std::unique_ptr<StaticText> _materialValue;
    std::unique_ptr<StaticText> _brushText;
    
    void GetInput();
    void Update(float deltaTime);
    
    // User Input
    void ShowHelp();

    int totalActivePixels = 0;
    float timeOut = 0.0f;
    std::string maxTRString = "";

private:
    void TickCalculation(float deltaTime);
    Font _font = LoadFontEx("resources/anonymous_pro_bold.ttf", 16, 0, 256);
};

