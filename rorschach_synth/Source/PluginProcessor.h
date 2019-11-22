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


#define OSC1_VOL_ID "osc1_vol"
#define OSC1_VOL_NAME "Osc1_vol"
#define OSC2_VOL_ID "osc2_vol"
#define OSC2_VOL_NAME "Osc2_vol"
#define OSC3_VOL_ID "osc3_vol"
#define OSC3_VOL_NAME "Osc3_vol"
#define ATTACK_ID "attack"
#define ATTACK_NAME "Attack"
#define DECAY_ID "decay"
#define DECAY_NAME "Decay"
#define SUSTAIN_ID "sustain"
#define SUSTAIN_NAME "Sustain"
#define RELEASE_ID "release"
#define RELEASE_NAME "Release"
#define DELAY_TIME "delay_time"
#define DELAY_NAME "delay_time"
#define GAIN_ID "gain"
#define GAIN_NAME "Gain"
#define LFO_ID "lfo"
#define LFO_NAME "LFO"
#define REVERB_AMT "reverb_amt"
#define REVERB_NAME "reverb_amt"
#define GLITCH_ID "glitch"
#define GLITCH_NAME "Glitch"
#define LOW_PASS_ID "lopass"
#define LOW_PASS_NAME "Lopass"
#define HIGH_PASS_ID "highpass"
#define HIGH_PASS_NAME "Highpass"
#define ARP_SPEED_ID "arp_speed"
#define ARP_SPEED_NAME "Arp_Speed"
//==============================================================================
/**
*/
class Rorschach_synthAudioProcessor  :  public AudioProcessor

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
    
    //==============================================================================
    double getDelayInMilis();
    void setDelayInMilis(double);
    
    double getReverbAmt();
    void setReverbAmt(double);
    
    // toggle button functions
    void toggleGlitch(bool);

    void toggleArpOnOff(bool);
    void toggleArpMode(bool);
    
    
    void arpeggiate(AudioBuffer<float>& buffer, MidiBuffer& origMidiMessages, MidiBuffer& arpMidiMessages);

    void toggleLfoButton(bool);

    
    // tree state holds values from UI controls
    AudioProcessorValueTreeState parameterState;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    
private:
    Synthesiser synth;
    SynthVoice *voice;
    
    double delayInMilis;
    double reverbAmt;
    
    double lastSampleRate;
    
    bool glitchState;

    bool arpState;
    bool arpMode;
    
    // arpeggiator variables
//    float speed;
    int currentNote, lastNoteValue;
    int time;
    float rate;
    SortedSet<int> notes;
    
    

    bool lfoButtonState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rorschach_synthAudioProcessor)
};
