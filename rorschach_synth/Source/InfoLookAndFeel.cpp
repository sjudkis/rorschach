/*
  ==============================================================================

    InfoButtonLookAndFeel.cpp
    Created: 22 Nov 2019 8:26:08pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#include "InfoLookAndFeel.h"
#include "Constants.h"

void InfoLookAndFeel::drawButtonBackground (Graphics& g,
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
    g.drawEllipse(rx, ry, rw, rw, 3.0f);
    g.setFont(Font("Arial", height/2, Font::bold));
    g.drawText("i", x, y, width, height, Justification::centred);
}