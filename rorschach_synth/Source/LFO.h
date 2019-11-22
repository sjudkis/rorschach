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
#include "Constants.h"

//==============================================================================
/*
*/
class LFO    : public Component,
               public Button::Listener
{
public:
    LFO(Rorschach_synthAudioProcessor& p) : processor(p)
    {
        lfoSlider.setLookAndFeel(&vertSliderLookAndFeel);
        lfoSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        lfoSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        
        lfoButton.addListener(this);
        lfoButton.setWantsKeyboardFocus(false);
        lfoButton.setColour(TextButton::buttonColourId, Constants::brown);
        lfoButton.setColour(TextButton::textColourOffId, Constants::tan);
        lfoButton.setColour(TextButton::buttonOnColourId, Constants::brown);
        lfoButton.setColour(TextButton::textColourOnId, Constants::tan);
        
        
        addAndMakeVisible(&lfoSlider);
        addAndMakeVisible(&lfoButton);
        
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
        
        if (lfoButton.getToggleState())
        {
            lfoButton.setButtonText("AM");
        }
        else
        {
            lfoButton.setButtonText("FM");
        }
    }

    void resized() override
    {
        juce::Rectangle<int> sliderArea = getLocalBounds();
        sliderArea.removeFromBottom(15);
        lfoSlider.setBounds(sliderArea.removeFromBottom(getHeight() * 0.75));
        sliderArea.reduce(4, 0);
        lfoButton.setBounds(sliderArea);
    }
    
    void buttonClicked(Button *button) override
    {
        if (button == &lfoButton)
        {
            auto lfoButtonState = lfoButton.getToggleState();
            lfoButton.setToggleState(!lfoButtonState, NotificationType::dontSendNotification);
            processor.toggleLfoButton(!lfoButtonState);
        }
    }
    
    
private:
    Rorschach_synthAudioProcessor& processor;
    
    Slider lfoSlider;
    TextButton lfoButton;
    VertSliderLookAndFeel vertSliderLookAndFeel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> lfoVal;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};
