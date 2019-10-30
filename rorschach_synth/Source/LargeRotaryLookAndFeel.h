/*
  ==============================================================================

    LargeRotaryLookAndFeel.h
    Created: 28 Oct 2019 5:40:53pm
    Author:  Andrew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class LargeRotaryLookAndFeel : public LookAndFeel_V4
{
public:
	LargeRotaryLookAndFeel() {};
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider&) override;
};