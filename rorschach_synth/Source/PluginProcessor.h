/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"
//#include "MidiKeyboard.h"


//==============================================================================
/**
*/
class Rorschach_synthAudioProcessor  :  public AudioProcessor,
                                        private MidiInputCallback
{
public:
    //==============================================================================
    Rorschach_synthAudioProcessor();
    ~Rorschach_synthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // keeps current state of UI keyboard component
    MidiKeyboardState keyboardState;

    // functions called by keyboard state listener
    void keyboardNoteOn(int midiChannel, int midiNoteNumber, float velocity);
    void keyboardNoteOff(int midiChannel, int midiNoteNumber, float velocity);
    
private:
    Synthesiser synth;
    SynthVoice voice;
    
    double lastSampleRate;
    
    // virtual function for UI keyboard state
    void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rorschach_synthAudioProcessor)
};
