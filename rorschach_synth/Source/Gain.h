/*
  ==============================================================================

    Gain.h
    Created: 9 Nov 2019 10:43:32am
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "VertSliderLookAndFeel.h"

//==============================================================================
/*
*/
class Gain    : public Component
{
public:
    Gain(Rorschach_synthAudioProcessor& p) : processor(p)
    {
        gainSlider.setLookAndFeel(&vertSliderLookAndFeel);
        gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        
        addAndMakeVisible(&gainSlider);
        
        gainVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, GAIN_ID, gainSlider);
    }

    ~Gain()
    {
    }

    void paint (Graphics& g) override
    {
        juce::Rectangle<int> title = getLocalBounds().removeFromBottom(20);
        g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
        
        g.drawText("Gain", title, Justification::centredTop);
    }

    void resized() override
    {
        juce::Rectangle<int> sliderArea = getLocalBounds();
        sliderArea.removeFromBottom(15);
        gainSlider.setBounds(sliderArea);
    }

private:
    Rorschach_synthAudioProcessor& processor;
    
    Slider gainSlider;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> gainVal;
    
    VertSliderLookAndFeel vertSliderLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Gain)
};
