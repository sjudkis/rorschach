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
    g.setFont(Font(height/2, Font::bold));
    g.drawText("i", x, y, width, height, Justification::centred);
}

void InfoLookAndFeel::drawLabel (Graphics& g, Label& label)
{
    auto area = label.getLocalBounds();
    auto width = area.getWidth();
    auto height = area.getHeight();
    auto x = area.getX();
    auto y = area.getY();
    
    g.setColour(Constants::brown);
    g.setFillType(FillType(Constants::brown));
    g.fillRoundedRectangle(x, y, width, height, 5.0f);
    g.setColour(Constants::tan);
    g.setFont((Font(label.getFont().getHeight(), Font::bold)));
    g.drawText(label.getText(), x, y, width, height, Justification::centred);
}