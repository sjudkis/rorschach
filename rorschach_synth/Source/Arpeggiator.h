/*
  ==============================================================================

    Arpeggiator.h
    Created: 20 Nov 2019 2:07:41pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Constants.h"
#include "VertSliderLookAndFeel.h"

//==============================================================================
/*
*/
class Arpeggiator    : public Component
{
public:
    Arpeggiator(Rorschach_synthAudioProcessor& p) : processor(p)
    {
        addAndMakeVisible(&arpSlider);
        arpSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        arpSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        arpSlider.setLookAndFeel(&sliderLookAndFeel);
        arpSpeed = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, ARP_SPEED_ID, arpSlider);
    }

    ~Arpeggiator()
    {
        arpSlider.setLookAndFeel(nullptr);
    }

    void paint (Graphics& g) override
    {
        juce::Rectangle<int> title(0, 0, getWidth(), 15);
//        g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
        g.setColour(Constants::brown);
        g.drawText("Arp. Speed", title, Justification::centred);
    }

    void resized() override
    {
        juce::Rectangle<int> sliderArea = getLocalBounds();
        sliderArea.removeFromTop(15);
        arpSlider.setBounds(sliderArea);
    }

private:
    Rorschach_synthAudioProcessor& processor;
    
    Slider arpSlider;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> arpSpeed;
    VertSliderLookAndFeel sliderLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Arpeggiator)
};
