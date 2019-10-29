/*
  ==============================================================================

    LargeRotaryLookAndFeel.cpp
    Created: 28 Oct 2019 5:40:53pm
    Author:  Andrew

  ==============================================================================
*/

#include "LargeRotaryLookAndFeel.h"
#include "Constants.h"

void LargeRotaryLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider&)
{
	auto radius = jmin(width / 2, height / 2) - 4.0f;
	auto centreX = x + width * 0.5f;
	auto centreY = y + height * 0.5f;
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

	// set a static image background
	Image background = ImageCache::getFromMemory(BinaryData::static_dial_png, BinaryData::static_dial_pngSize);
	g.drawImageTransformed(background, AffineTransform::rotation(angle - rotaryStartAngle, centreX, centreY), 0);

	// outline background
	g.setColour(Colours::whitesmoke);
	g.drawEllipse(rx, ry, rw, rw, 10.0f);

	// progress online indicator
	Path pointer;
	Path progress;
	auto pointerLength = radius * 1.0f;
	auto pointerThickness = 5.0f;
	pointer.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength - 1);
	progress.addCentredArc(centreX, centreY, radius, radius, 0, rotaryStartAngle, angle, true);
	pointer.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

	// pointer
	g.setColour(Constants::tan);
	g.strokePath(pointer, PathStrokeType(10.0f, PathStrokeType::JointStyle::curved));
	g.strokePath(progress, PathStrokeType(10.0f, PathStrokeType::JointStyle::curved));
}