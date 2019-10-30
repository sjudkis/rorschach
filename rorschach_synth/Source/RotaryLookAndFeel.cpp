/*
  ==============================================================================

    SideBarRotaryLookAndFeel.cpp
    Created: 28 Oct 2019 4:07:08pm
    Author:  Andrew

  ==============================================================================
*/

#include "RotaryLookAndFeel.h"
#include "Constants.h"

void RotaryLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider&)
{
	auto radius = jmin(width / 2, height / 2) - 4.0f;
	auto centreX = x + width * 0.5f;
	auto centreY = y + height * 0.5f;
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

	// fill
	g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
	g.fillEllipse(rx, ry, rw, rw);

	Path p;
	auto pointerLength = radius * 1.0f;
	auto pointerThickness = 3.0f;
	p.addRectangle(-pointerThickness * 0.7f, -radius, pointerThickness, pointerLength);
	p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

	// pointer
	g.setColour(Constants::tan);
	g.fillPath(p);
}