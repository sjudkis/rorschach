/*
  ==============================================================================

    SideBarRotaryLookAndFeel.h
    Created: 28 Oct 2019 4:07:08pm
    Author:  Andrew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class RotaryLookAndFeel : public LookAndFeel_V4
{
public:
	RotaryLookAndFeel() {};
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider&) override;
};