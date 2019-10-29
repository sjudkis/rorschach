/*
  ==============================================================================

    VertSliderLookAndFeel.h
    Created: 28 Oct 2019 5:18:37pm
    Author:  Andrew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class VertSliderLookAndFeel : public LookAndFeel_V4
{
public:
	VertSliderLookAndFeel() {};
	void drawLinearSlider(Graphics&,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		float 	sliderPos,
		float 	minSliderPos,
		float 	maxSliderPos,
		const Slider::SliderStyle,
		Slider&
	) override;
};