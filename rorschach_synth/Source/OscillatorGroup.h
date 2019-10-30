/*
  ==============================================================================

    OscillatorGroup.h
    Created: 24 Oct 2019 12:01:35pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "VertSliderLookAndFeel.h"
//==============================================================================
/*
*/
class OscillatorGroup    : public Component
{
public:
    OscillatorGroup(Rorschach_synthAudioProcessor& p)   :
                osc1(p, 1, "Sine"), osc2(p, 2, "Square"), osc3(p, 3, "Saw"),
                processor(p)
    {
		osc1.setLookAndFeel(&vertSliderLookAndFeel);
		osc2.setLookAndFeel(&vertSliderLookAndFeel);
		osc3.setLookAndFeel(&vertSliderLookAndFeel);

        addAndMakeVisible(&osc1);
        addAndMakeVisible(&osc2);
        addAndMakeVisible(&osc3);
    }

    ~OscillatorGroup()
    {
		osc1.setLookAndFeel(nullptr);
		osc2.setLookAndFeel(nullptr);
		osc3.setLookAndFeel(nullptr);
    }

    void paint (Graphics& g) override
    {
        juce::Rectangle<int> title(0, 0, getWidth(), 30);
        g.setColour(Colours::black);
        g.setFont(20);
        g.drawText("Oscillators", title, Justification::centred);
    }

    void resized() override
    {
		juce::Rectangle<int> area = getLocalBounds();
        area.removeFromTop(30); // remove title area
        
        int oscWidth = getWidth() / 3;
        osc1.setBounds(area.removeFromLeft(oscWidth));
        osc2.setBounds(area.removeFromLeft(oscWidth));
        osc3.setBounds(area);

    }

private:
    Oscillator osc1; // sine
    Oscillator osc2; // square
    Oscillator osc3; // saw

    Rorschach_synthAudioProcessor& processor;
    
	VertSliderLookAndFeel vertSliderLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorGroup)
};
