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

//==============================================================================
/*
*/
class SideBar    : public Component
{
public:
    SideBar(Rorschach_synthAudioProcessor& p) :
            processor(p),
            oscillators(p)
            
    {
        addAndMakeVisible(&oscillators);

    }

    ~SideBar()
    {
    }

    void paint (Graphics& g) override
    {
        g.setColour(Colours::darkgrey);
        g.drawRect(getLocalBounds(), 1);
        
    }

    void resized() override
    {
        juce::Rectangle<int> area = getLocalBounds();
        
        int oscillatorGroupHeight = 250;
        oscillators.setBounds(area.removeFromTop(oscillatorGroupHeight));
    }

private:
    Rorschach_synthAudioProcessor& processor;
    OscillatorGroup oscillators;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SideBar)
};
