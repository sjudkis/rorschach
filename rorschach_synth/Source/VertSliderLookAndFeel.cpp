/*
  ==============================================================================

    VertSliderLookAndFeel.cpp
    Created: 28 Oct 2019 5:18:37pm
    Author:  Andrew

  ==============================================================================
*/

#include "VertSliderLookAndFeel.h"
#include "Constants.h"

void VertSliderLookAndFeel::drawLinearSlider(Graphics& g,
	int 	x,
	int 	y,
	int 	width,
	int 	height,
	float 	sliderPos,
	float 	minSliderPos,
	float 	maxSliderPos,
	const Slider::SliderStyle,
	Slider&
)
{
	g.setColour(Constants::brown);
    g.drawLine((float)x + (width / 2), (float)y, (float)x + (width / 2), (float)height + (float)y, 4.0);
//	g.drawLine((float)x + (width / 2), (float)y, (float)x + (width / 2), (float)maxSliderPos, 4.0);

	g.setColour(Constants::brown);
	Rectangle< float > rectangle((width / 2) - 10, sliderPos, 20, 5);
	g.drawRoundedRectangle(rectangle, 0.5, 4);
	g.setColour(Constants::tan);
	g.fillRect(rectangle);
}
