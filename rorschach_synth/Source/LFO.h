/*
  ==============================================================================

    LFO.h
    Created: 13 Nov 2019 9:07:30pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "VertSliderLookAndFeel.h"

//==============================================================================
/*
*/
class LFO    : public Component
{
public:
    LFO(Rorschach_synthAudioProcessor& p) : processor(p)
    {
        lfoSlider.setLookAndFeel(&vertSliderLookAndFeel);
        lfoSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        lfoSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        
        addAndMakeVisible(&lfoSlider);
        
        lfoVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, LFO_ID, lfoSlider);
    }

    ~LFO()
    {
        lfoSlider.setLookAndFeel(nullptr);
    }

    void paint (Graphics& g) override
    {
        juce::Rectangle<int> title = getLocalBounds().removeFromBottom(20);
        g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
        
        g.drawText("LFO", title, Justification::centredTop);
    }

    void resized() override
    {
        juce::Rectangle<int> sliderArea = getLocalBounds();
        sliderArea.removeFromBottom(15);
        lfoSlider.setBounds(sliderArea);
    }


private:
    Rorschach_synthAudioProcessor& processor;
    
    Slider lfoSlider;
    VertSliderLookAndFeel vertSliderLookAndFeel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> lfoVal;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};
