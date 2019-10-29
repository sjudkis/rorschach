/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Constants.h"

//==============================================================================
Rorschach_synthAudioProcessorEditor::Rorschach_synthAudioProcessorEditor (Rorschach_synthAudioProcessor& p)
    :   AudioProcessorEditor (&p),
        processor (p),
        keyboard(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
        sidebar(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(sidebarWidth+visualizerWidth, keyboardHeight+visualizerHeight);
    addAndMakeVisible(&keyboard);
    processor.keyboardState.addListener(this);
    keyboard.setWantsKeyboardFocus (false);

    // timer, callback sets focus on keyboard to allow immediate midi input
    startTimer(300);
    
    // add sidebar
    addAndMakeVisible(&sidebar);

	// set main dial position
	mainDial.setSliderStyle(Slider::Rotary);
	mainDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	mainDial.setLookAndFeel(&largeRotaryLookAndFeel);
	addAndMakeVisible(&mainDial);
}
Rorschach_synthAudioProcessorEditor::~Rorschach_synthAudioProcessorEditor()
{
	mainDial.setLookAndFeel(nullptr);
    processor.keyboardState.removeListener(this);
}

//==============================================================================
void Rorschach_synthAudioProcessorEditor::paint (Graphics& g)
{
	// Set base background colour
    g.fillAll(Constants::tan);

	// visualizer static placeholder image
	Image visualizer = ImageCache::getFromMemory(BinaryData::static_blot_jpg, BinaryData::static_blot_jpgSize);
	g.drawImageAt(visualizer, 0, 0);
}

void Rorschach_synthAudioProcessorEditor::resized()
{
    
    juce::Rectangle<int> area = getLocalBounds();

    sidebar.setBounds(area.removeFromRight(sidebarWidth));

    keyboard.setBounds(area.removeFromBottom(keyboardHeight));

	// set main dial position
	mainDial.setBounds(115, 115, 200, 200);
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
