/*
  ==============================================================================

    SideBarLookAndFeel.h
    Created: 27 Nov 2019 3:52:13pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class SideBarLookAndFeel : public LookAndFeel_V4
{
public:
    SideBarLookAndFeel() {};
    
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, Slider&) override;
    
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
