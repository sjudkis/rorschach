/*
  ==============================================================================

    Envelope.h
    Created: 30 Oct 2019 1:46:33pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "RotaryLookAndFeel.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(Rorschach_synthAudioProcessor& p) : processor(p)
    {
        setRotaryStyle(attack);
        attack.setRange(0.001f, 5.0f);
        
        setRotaryStyle(decay);
        decay.setRange(0.001f, 2.0f);
        
        setRotaryStyle(sustain);
        sustain.setRange(0.0f, 1.0f);
        
        setRotaryStyle(release);
        release.setRange(0.001f, 5.0f);
        
        addAndMakeVisible(&attack);
        addAndMakeVisible(&decay);
        addAndMakeVisible(&sustain);
        addAndMakeVisible(&release);

        
        attackState = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, ATTACK_ID, attack);
        decayState = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, DECAY_ID, decay);
        sustainState = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, SUSTAIN_ID, sustain);
        releaseState = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.parameterState, RELEASE_ID, release);
        
    
    }

    ~Envelope()
    {
        attack.setLookAndFeel(nullptr);
        decay.setLookAndFeel(nullptr);
        sustain.setLookAndFeel(nullptr);
        release.setLookAndFeel(nullptr);
    }

    void setRotaryStyle(Slider &s)
    {
        s.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        s.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        s.setLookAndFeel(&rotaryLookAndFeel);
        
    }
    void paint (Graphics& g) override
    {
        g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
        g.setFont(18);
        
        int labelWidth = 20;
        int labelHeight = 20;
        
        juce::Rectangle<int> labelA(0, 0, labelWidth, labelHeight);
        g.drawText("A", labelA, Justification::centred);
        
        juce::Rectangle<int> labelD(getWidth() - labelWidth, 0, labelWidth, labelHeight);
        g.drawText("D", labelD, Justification::centred);
        
        juce::Rectangle<int> labelS(0, getHeight() - labelHeight, labelWidth, labelHeight);
        g.drawText("S", labelS, Justification::centred);
        
        juce::Rectangle<int> labelR(getWidth() - labelWidth, getHeight() - labelHeight, labelWidth, labelHeight);
        g.drawText("R", labelR, Justification::centred);
    }

    void resized() override
    {
        juce::Rectangle<int> area = getLocalBounds();
        int envWidth = getWidth() / 2;
        int envHeight = getHeight() / 2;
        
        
        juce::Rectangle<int> topArea = area.removeFromTop(envHeight);
        juce::Rectangle<int> topLeft = topArea.removeFromLeft(envWidth);
        
        
        
        attack.setBounds(topLeft);
        
        decay.setBounds(topArea);
        
        juce::Rectangle<int> bottomLeft = area.removeFromLeft(envWidth);
        sustain.setBounds(bottomLeft);
        release.setBounds(area);
                          
    }

private:
    Rorschach_synthAudioProcessor& processor;
    
    Slider attack;
    Slider decay;
    Slider sustain;
    Slider release;
    
//    juce::Rectangle<int> topLeft;
//    juce::Rectangle<int> topRight;
//    juce::Rectangle<int> bottomLeft;
//    juce::Rectangle<int> bottomRight;
    
    // listeners
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> attackState;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> decayState;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sustainState;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> releaseState;
    
    RotaryLookAndFeel rotaryLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
