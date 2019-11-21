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
// #include "BlotBackground.h"


//==============================================================================
/**
*/
class Rorschach_synthAudioProcessorEditor  :    public AudioProcessorEditor,
                                                public Timer,
                                                private MidiKeyboardStateListener,
                                                public Slider::Listener,
                                                public Button::Listener,
                                                public OpenGLRenderer
{
public:
    Rorschach_synthAudioProcessorEditor (Rorschach_synthAudioProcessor& p);
    ~Rorschach_synthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;
    void buttonClicked(Button *button) override;
    
    //==============================================================================
    // blob background methods
    void createNextState();
    void copyNextToCurState();
    void translate(float elapsed);
    
    //==============================================================================
    void handleRetina();
    void newOpenGLContextCreated() override;
    void openGLContextClosing() override;
    void renderOpenGL() override;
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
    
    //==============================================================================
    // Blot background variables
    OpenGLContext openGLContext;
    
    bool isInitialRun = true; // Used for keyboard run
    Random r;
    int blobCount = 2000; // Has to be divisible by 2
    std::vector<std::pair<std::vector<float>, std::vector<float>>> blobState; // prev, current<x loc, y loc, size, size>
    std::vector<std::vector<float>> curState; // x loc, y loc, size x, size y
    
    // time modifiers
    int translateTimeHz = 180; // hz it takes for blobs to travel from one state to next
    int updatePerSecond = 60;
    int pauseTimeHz = .5 * 60;
    int transitionCounter = 0;
    
    // ball sizes
    float circleMaxDim = .05;
    float circleMinDim = .01;
    int circleSegments = 20;
    float padding = circleMaxDim + .01;
    float visWidth = (float)visualizerHeight / visualizerWidth;
    float visHeight = (float)visualizerWidth / visualizerHeight;
    float difference = visWidth - padding / 2;
    float xOffset =  sidebarWidth / ((float)sidebarWidth + visualizerWidth);
    float yOffset = keyboardHeight/((float)keyboardHeight+visualizerHeight) + padding/2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rorschach_synthAudioProcessorEditor)
};
