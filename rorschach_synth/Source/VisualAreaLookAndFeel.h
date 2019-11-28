/*
  ==============================================================================

    VisualAreaLookAndFeel.h
    Created: 27 Nov 2019 3:52:57pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class VisualAreaLookAndFeel : public LookAndFeel_V4
{
public:
    VisualAreaLookAndFeel() {};
    
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, Slider&) override;
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
};
