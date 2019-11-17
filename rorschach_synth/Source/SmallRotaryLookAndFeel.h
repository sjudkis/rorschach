/*
  ==============================================================================

    SmallRotaryLookAndFeel.h
    Created: 10 Nov 2019 12:00:23pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class SmallRotaryLookAndFeel : public LookAndFeel_V4
{
public:
	SmallRotaryLookAndFeel() {};
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider&) override;
};
