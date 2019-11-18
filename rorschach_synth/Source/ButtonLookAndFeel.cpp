/*
  ==============================================================================

    smallButtonLookAndFeel.cpp
    Created: 17 Nov 2019 12:10:00am
    Author:  Zachary Anderson

  ==============================================================================
*/

#include "ButtonLookAndFeel.h"
#include "Constants.h"

void ButtonLookAndFeel::drawButtonBackground (Graphics& g,
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
    auto radius = jmin(width / 2, height / 2) - 4.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    
    
    
    // outline background
    //if (!button.getToggleState())
    g.setColour(backgroundColour);
    //else g.setColour(Constants::tan);
    g.drawEllipse(rx, ry, rw, rw, 10.0f);
    
}