/*
  ==============================================================================

    SideBar.h
    Created: 24 Oct 2019 5:45:49pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OscillatorGroup.h"
#include "Envelope.h"
#include "Gain.h"
//==============================================================================
/*
*/
class SideBar    : public Component
{
public:
    SideBar(Rorschach_synthAudioProcessor& p) :
            processor(p),
            oscillators(p),
            envelope(p),
            gain(p)
            
    {
        addAndMakeVisible(&oscillators);
        addAndMakeVisible(&envelope);
        addAndMakeVisible(&gain);
    }

    ~SideBar()
    {
    }

    void paint (Graphics& g) override
	{
    }

    void resized() override
    {
        juce::Rectangle<int> area = getLocalBounds();
        
        int oscillatorGroupHeight = 200;
        oscillators.setBounds(area.removeFromTop(oscillatorGroupHeight));
		envelope.setBounds(area.removeFromTop(250)); //300
        gain.setBounds(area.removeFromRight(getWidth() / 3));
    }

private:
    Rorschach_synthAudioProcessor& processor;
    OscillatorGroup oscillators;
    Envelope envelope;
    Gain gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SideBar)
};
