/*
  ==============================================================================

    SynthSound.h
    Created: 20 Oct 2019 1:43:20pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    
    bool appliesToNote (int midiNoteNumber) override {
        return true;
    }
    
    bool appliesToChannel (int channelNumber) override {
        return true;
    }
};
