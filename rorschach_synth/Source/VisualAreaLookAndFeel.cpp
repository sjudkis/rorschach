/*
  ==============================================================================

    VisualAreaLookAndFeel.cpp
    Created: 27 Nov 2019 3:53:13pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#include "VisualAreaLookAndFeel.h"
#include "Constants.h"


void VisualAreaLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                                              const float rotaryStartAngle, const float rotaryEndAngle, Slider&)
{
    auto radius = jmin(width / 2, height / 2) - 8.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    g.setColour(Constants::tan);
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
    g.setColour(Constants::brown);
    g.strokePath(progress, PathStrokeType(10.0f, PathStrokeType::JointStyle::curved));
}


void VisualAreaLookAndFeel::drawButtonBackground (Graphics& g,
                                                  Button& button,
                                                  const Colour& backgroundColour,
                                                  bool isMouseOverButton,
                                                  bool isButtonDown)
{
    auto area = button.getLocalBounds();
    auto width = area.getWidth();
    auto height = area.getHeight();
    auto x = area.getX();
    auto y = area.getY();
    auto radius = jmin(width / 2, height / 2) - 8.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    
    g.setColour(backgroundColour);
    g.drawEllipse(rx, ry, rw, rw, 10.0f);
    
}

