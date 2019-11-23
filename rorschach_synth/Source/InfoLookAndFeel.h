/*
  ==============================================================================

    InfoButtonLookAndFeel.h
    Created: 22 Nov 2019 8:25:50pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class InfoLookAndFeel : public LookAndFeel_V4
{
public:
    InfoLookAndFeel() {};
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
};
