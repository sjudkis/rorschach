/*
  ==============================================================================

    LowPassFilter.h
    Created: 14 Nov 2019 8:52:25pm
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
class LowPassFilter    : public Component
{
public:
    LowPassFilter(Rorschach_synthAudioProcessor& p) : processor(p)
    {
        loPassSlider.setLookAndFeel(&sideBarLookAndFeel);
        loPassSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        loPassSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        loPassSlider.setSkewFactor(0.08);
        
        addAndMakeVisible(&loPassSlider);
        
        loPassVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, LOW_PASS_ID, loPassSlider);
    }

    ~LowPassFilter()
    {
        loPassSlider.setLookAndFeel(nullptr);
    }

    void paint (Graphics& g) override
    {
        juce::Rectangle<int> title = getLocalBounds().removeFromBottom(20);
        g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
        
        g.drawText("LoPass", title, Justification::centredTop);
    }

    void resized() override
    {
        juce::Rectangle<int> sliderArea = getLocalBounds();
        sliderArea.removeFromBottom(15);
        loPassSlider.setBounds(sliderArea);
    }


private:
    Rorschach_synthAudioProcessor& processor;
    
    Slider loPassSlider;
    SideBarLookAndFeel sideBarLookAndFeel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> loPassVal;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowPassFilter)
};