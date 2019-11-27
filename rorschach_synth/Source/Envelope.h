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
#include "SideBarLookAndFeel.h"
#include "EnvelopeGraph.h"
#include "Constants.h"

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
		attack.onValueChange = [this] {
			envelopeGraph.onAttackChange(sliderPos(attack));
			envelopeGraph.repaint();
		};
        
		setRotaryStyle(decay);
        decay.setRange(0.001f, 2.0f);
		decay.onValueChange = [this] {
			envelopeGraph.onDecayChange(sliderPos(decay));
			envelopeGraph.repaint();
		};

        setRotaryStyle(sustain);
        sustain.setRange(0.0f, 1.0f);
		sustain.onValueChange = [this] {
			envelopeGraph.onSustainChange(sliderPos(sustain));
			envelopeGraph.repaint();
		};

        setRotaryStyle(release);
        release.setRange(0.001f, 5.0f);
		release.onValueChange = [this] {
			envelopeGraph.onReleaseChange(sliderPos(release)); 
			envelopeGraph.repaint();
		};

        addAndMakeVisible(&attack);
        addAndMakeVisible(&decay);
        addAndMakeVisible(&sustain);
        addAndMakeVisible(&release);
		addAndMakeVisible(&envelopeGraph);
        
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

	// slider position in percentage
	// assumes that all sliders start around zero
	double sliderPos(Slider &s) {

		return s.getValue() / (s.getRange().getEnd() - s.getRange().getStart());
	}

    void setRotaryStyle(Slider &s)
    {
        s.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        s.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        s.setLookAndFeel(&sideBarLookAndFeel);
        
    }
    void paint (Graphics& g) override
    {
        g.setColour(Constants::brown);
        g.setFont(18);

        int labelWidth = 20;
        int labelHeight = 20;

		juce::Rectangle<int> area = getLocalBounds().removeFromTop(2 * getHeight() / 3);

        juce::Rectangle<int> labelA(0, 0, labelWidth, labelHeight);
        g.drawText("A", labelA, Justification::centred);
        
        juce::Rectangle<int> labelD(getWidth() - labelWidth, 0, labelWidth, labelHeight);
        g.drawText("D", labelD, Justification::centred);
        
        juce::Rectangle<int> labelS(0, area.getHeight() - labelHeight, labelWidth, labelHeight);
        g.drawText("S", labelS, Justification::centred);
        
        juce::Rectangle<int> labelR(getWidth() - labelWidth, area.getHeight() - labelHeight, labelWidth, labelHeight);
        g.drawText("R", labelR, Justification::centred);

		
    }

    void resized() override
    {
        juce::Rectangle<int> area = getLocalBounds().removeFromTop(2*getHeight()/3);
        int envWidth = area.getWidth() / 2;
        int envHeight = area.getHeight() / 2;
        
        
        juce::Rectangle<int> topArea = area.removeFromTop(envHeight);
        juce::Rectangle<int> topLeft = topArea.removeFromLeft(envWidth);
        
     
        attack.setBounds(topLeft);
        
        decay.setBounds(topArea);
        
        juce::Rectangle<int> bottomLeft = area.removeFromLeft(envWidth);
        sustain.setBounds(bottomLeft);
        release.setBounds(area);

        juce::Rectangle<int> graphArea = getLocalBounds().removeFromBottom(getHeight()/3);

        envelopeGraph.setBounds(graphArea.reduced(10));
    }

private:
    Rorschach_synthAudioProcessor& processor;
    
    Slider attack;
    Slider decay;
    Slider sustain;
    Slider release;
	EnvelopeGraph envelopeGraph;

    
    // listeners
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> attackState;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> decayState;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sustainState;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> releaseState;
    
    SideBarLookAndFeel sideBarLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
