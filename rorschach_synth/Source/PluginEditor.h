/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "maximilian.h"
//#include "MidiKeyboard.h"
//==============================================================================
/**
*/
class Rorschach_synthAudioProcessorEditor  : public AudioProcessorEditor,
//                                                private MidiInputCallback,
                                                private MidiKeyboardStateListener
{
public:
    Rorschach_synthAudioProcessorEditor (Rorschach_synthAudioProcessor& p);
    ~Rorschach_synthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Rorschach_synthAudioProcessor& processor;

    MidiKeyboardComponent keyboard;
        
    // virtual functions
    void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
//    void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rorschach_synthAudioProcessorEditor)
};
