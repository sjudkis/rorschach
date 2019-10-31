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
//==============================================================================
/*
*/
class SideBar    : public Component
{
public:
    SideBar(Rorschach_synthAudioProcessor& p) :
            processor(p),
            oscillators(p),
            envelope(p)
            
    {
        addAndMakeVisible(&oscillators);
        addAndMakeVisible(&envelope);
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
        
        int oscillatorGroupHeight = 250;
        oscillators.setBounds(area.removeFromTop(oscillatorGroupHeight));
        envelope.setBounds(area.removeFromTop(getWidth()));
    }

private:
    Rorschach_synthAudioProcessor& processor;
    OscillatorGroup oscillators;
    Envelope envelope;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SideBar)
};
