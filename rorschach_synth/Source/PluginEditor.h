/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "OscillatorGroup.h"
#include "SideBar.h"
#include "LargeRotaryLookAndFeel.h"
#include "SmallRotaryLookAndFeel.h"
#include "ButtonLookAndFeel.h"


//==============================================================================
/**
*/
class Rorschach_synthAudioProcessorEditor  :    public AudioProcessorEditor,
                                                public Timer,
                                                private MidiKeyboardStateListener,
                                                public Slider::Listener,
                                                public Button::Listener
{
public:
    Rorschach_synthAudioProcessorEditor (Rorschach_synthAudioProcessor& p);
    ~Rorschach_synthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;
    void buttonClicked(Button *button) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Rorschach_synthAudioProcessor& processor;

    // built in keyboard UI
    MidiKeyboardComponent keyboard;
	const int keyboardHeight = 100;

	// Main Rotary
	Slider mainDial;
	LargeRotaryLookAndFeel largeRotaryLookAndFeel;
    unique_ptr<AudioProcessorValueTreeState::SliderAttachment> rotaryDelay;
    
    //Reverb Rotary
    Slider reverbDial;
    SmallRotaryLookAndFeel smallRotaryLookAndFeel;
    unique_ptr<AudioProcessorValueTreeState::SliderAttachment> rotaryReverb;
    
    // Arpeggiator button
    TextButton arpButton;
    
    //Glitch button
    TextButton glitchButton;
    ButtonLookAndFeel buttonLookAndFeel;

    
	// Sidebar with synth controls
    SideBar sidebar;
	const int sidebarWidth = 200;
	// Width of visualizer. Right now, it is static.
	const int visualizerWidth = 736;
	const int visualizerHeight = 479;
	
    // virtual functions
    void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

    // timer to grab focus for keyboard
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rorschach_synthAudioProcessorEditor)
};
