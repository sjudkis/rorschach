/*
  ==============================================================================

    HighPassFilter.h
    Created: 14 Nov 2019 8:52:41pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SideBarLookAndFeel.h"

//==============================================================================
/*
*/
class HighPassFilter    : public Component
{
public:
    HighPassFilter(Rorschach_synthAudioProcessor& p) : processor(p)
    {
        hiPassSlider.setLookAndFeel(&sideBarLookAndFeel);
        hiPassSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        hiPassSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        hiPassSlider.setSkewFactor(0.08);
        
        addAndMakeVisible(&hiPassSlider);
        
        hiPassVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, HIGH_PASS_ID, hiPassSlider);
    }

    ~HighPassFilter()
    {
        hiPassSlider.setLookAndFeel(nullptr);
    }

    void paint (Graphics& g) override
    {
        juce::Rectangle<int> title = getLocalBounds().removeFromBottom(20);
        g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
        
        g.drawText("HiPass", title, Justification::centredTop);
    }

    void resized() override
    {
        juce::Rectangle<int> sliderArea = getLocalBounds();
        sliderArea.removeFromBottom(15);
        hiPassSlider.setBounds(sliderArea);
    }


private:
    Rorschach_synthAudioProcessor& processor;
    
    Slider hiPassSlider;
    SideBarLookAndFeel sideBarLookAndFeel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> hiPassVal;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HighPassFilter)
};