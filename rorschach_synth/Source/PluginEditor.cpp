/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Rorschach_synthAudioProcessorEditor::Rorschach_synthAudioProcessorEditor (Rorschach_synthAudioProcessor& p)
    :   AudioProcessorEditor (&p),
        processor (p),
        keyboard(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
//        osc1(p, 1), osc2(p, 2), osc3(p, 3)
        sidebar(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    
    addAndMakeVisible(&keyboard);
    processor.keyboardState.addListener(this);
    keyboard.setWantsKeyboardFocus (false);

    // timer, callback sets focus on keyboard to allow immediate midi input
    startTimer(300);
    
    // add sidebar
    addAndMakeVisible(&sidebar);
    
}
Rorschach_synthAudioProcessorEditor::~Rorschach_synthAudioProcessorEditor()
{
    processor.keyboardState.removeListener(this);
}

//==============================================================================
void Rorschach_synthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::grey);
}

void Rorschach_synthAudioProcessorEditor::resized()
{
    
    juce::Rectangle<int> area = getLocalBounds();
    
    
    int sidebarWidth = 200;    
    sidebar.setBounds(area.removeFromRight(sidebarWidth));

    int keyboardHeight = 100;
    keyboard.setBounds(area.removeFromBottom(keyboardHeight));
}



void Rorschach_synthAudioProcessorEditor::handleNoteOn(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity)
{
    processor.keyboardNoteOn(midiChannel, midiNoteNumber, velocity);
}

void Rorschach_synthAudioProcessorEditor::handleNoteOff(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity)
{
    processor.keyboardNoteOff(midiChannel, midiNoteNumber, velocity);
}

void Rorschach_synthAudioProcessorEditor::timerCallback()
{
    keyboard.grabKeyboardFocus();
    stopTimer();
}
