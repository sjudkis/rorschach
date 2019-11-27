/*
  ==============================================================================

    SideBarLookAndFeel.cpp
    Created: 27 Nov 2019 3:52:30pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#include "SideBarLookAndFeel.h"
#include "Constants.h"


void SideBarLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
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


void SideBarLookAndFeel::drawLinearSlider(Graphics& g,
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
    
    g.setColour(Constants::brown);
    Rectangle< float > rectangle((width / 2) - 10, sliderPos, 20, 5);
    g.drawRoundedRectangle(rectangle, 0.5, 4);
    g.setColour(Constants::tan);
    g.fillRect(rectangle);
}