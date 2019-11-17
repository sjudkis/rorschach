/*
  ==============================================================================

    smallButtonLookAndFeel.h
    Created: 17 Nov 2019 12:09:49am
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SmallButtonLookAndFeel : public LookAndFeel_V4
{
public:
    SmallButtonLookAndFeel() {};
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
};
