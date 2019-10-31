/*
  ==============================================================================

    Oscillator.h
    Created: 23 Oct 2019 5:18:39pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator(Rorschach_synthAudioProcessor& p, int oscNum, const char* type)    :   processor(p)
    {
        oscType = type;
        setSize(50, 200);
        addAndMakeVisible(&volSlider);
        volSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        
        
        // check which oscillator number this is
        switch(oscNum)
        {
            case 1:
                volume = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
                        (processor.parameterState, OSC1_VOL_ID, volSlider);
                break;
            case 2:
                volume = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
                        (processor.parameterState, OSC2_VOL_ID, volSlider);
                break;
            case 3:
                volume = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
                        (processor.parameterState, OSC3_VOL_ID, volSlider);
                break;
        }
        
    }

    ~Oscillator()
    {
    }

    void paint (Graphics& g) override
    {
        juce::Rectangle<int> title(0, 0, getWidth(), 15);
        g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
        g.drawText(oscType, title, Justification::centred);
        
    }

    void resized() override
    {
        
        juce::Rectangle<int> sliderArea = getLocalBounds();
        sliderArea.removeFromTop(15);
        volSlider.setBounds(sliderArea);

    }

private:
    Rorschach_synthAudioProcessor& processor;
    const char* oscType;
    
    Slider volSlider;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> volume;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
