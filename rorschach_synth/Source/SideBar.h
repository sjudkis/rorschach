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
#include "LFO.h"
#include "LowPassFilter.h"
#include "HighPassFilter.h"
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
            gain(p),
            lfo(p),
            lowPassFilter(p),
            highPassFilter(p)
            
    {
        addAndMakeVisible(&oscillators);
        addAndMakeVisible(&envelope);
        addAndMakeVisible(&gain);
        addAndMakeVisible(&lfo);
        addAndMakeVisible(&lowPassFilter);
        addAndMakeVisible(&highPassFilter);
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
        gain.setBounds(area.removeFromRight(getWidth() / 4));
        lfo.setBounds(area.removeFromRight(getWidth() / 4));
        lowPassFilter.setBounds(area.removeFromRight(getWidth() / 4));
        highPassFilter.setBounds(area.removeFromRight(getWidth() / 4));
    }

private:
    Rorschach_synthAudioProcessor& processor;
    OscillatorGroup oscillators;
    Envelope envelope;
    Gain gain;
    LFO lfo;
    LowPassFilter lowPassFilter;
    HighPassFilter highPassFilter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SideBar)
};
