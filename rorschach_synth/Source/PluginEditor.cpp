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
        sidebar(p),
        arpControl(p)
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
    mainDial.setRange(0.0, 2000.0);
    mainDial.setValue(0.0);
    mainDial.addListener(this);
    addAndMakeVisible(&mainDial);
    
    //reverb button
    reverbDial.setSliderStyle(Slider::Rotary);
    reverbDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    reverbDial.setLookAndFeel(&smallRotaryLookAndFeel);
    reverbDial.setRange(0.5, 0.8);
    reverbDial.setValue(0.0);
    reverbDial.addListener(this);
    addAndMakeVisible(&reverbDial);
    
    rotaryDelay = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameterState,
                                                                                       "delay_time",
                                                                                       mainDial);
    rotaryReverb = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameterState,
                                                                                    "reverb_amt",
                                                                                    reverbDial);
    
    // glitch button
    glitchButton.addListener(this);
    glitchButton.setWantsKeyboardFocus(false);
    
    glitchButton.setLookAndFeel(&buttonLookAndFeel);
    addAndMakeVisible(&glitchButton);
    
    glitchButton.setColour(TextButton::ColourIds::buttonColourId, Colours::whitesmoke);
    glitchButton.setColour(TextButton::ColourIds::buttonOnColourId, Constants::tan);
    
    // Arpeggiator button
    arpButton.addListener(this);
    arpButton.setWantsKeyboardFocus(false);
    
    arpButton.setLookAndFeel(&buttonLookAndFeel);
    addAndMakeVisible(&arpButton);
    
    arpButton.setColour(TextButton::ColourIds::buttonColourId, Colours::whitesmoke);
    arpButton.setColour(TextButton::ColourIds::buttonOnColourId, Constants::tan);
    
}
Rorschach_synthAudioProcessorEditor::~Rorschach_synthAudioProcessorEditor()
{
	mainDial.setLookAndFeel(nullptr);
    reverbDial.setLookAndFeel(nullptr);
    
    glitchButton.setLookAndFeel(nullptr);
    glitchButton.removeListener(this);
    
    arpButton.setLookAndFeel(nullptr);
    arpButton.removeListener(this);
    
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
    
    reverbDial.setBounds(600, 325, 100, 100);
    
    glitchButton.setBounds(500, 250, 60, 60);
    
    arpButton.setBounds(325, 325, 70, 70);
    
    arpControl.setBounds(10, visualizerHeight - 150, 70, 150);
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

void Rorschach_synthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &mainDial)
    {
        processor.setDelayInMilis(mainDial.getValue());
    }
    else if (slider == &reverbDial)
    {
        processor.setReverbAmt(reverbDial.getValue());
        
    }
}

// listener function for glitch button
void Rorschach_synthAudioProcessorEditor::buttonClicked(Button *button)
{
    keyboard.grabKeyboardFocus();
    if (button == &glitchButton)
    {
        auto glitchState = glitchButton.getToggleState();
        glitchButton.setToggleState(!glitchState, NotificationType::dontSendNotification);
        processor.toggleGlitch(!glitchState);
    }
    
    else if (button == &arpButton)
    {
        auto arpState = arpButton.getToggleState();
        arpButton.setToggleState(!arpState, NotificationType::dontSendNotification);
        processor.toggleArp(!arpState);
        
        // add arp controls from UI
        if (!arpState)
            addAndMakeVisible(&arpControl);
        else
            removeChildComponent(&arpControl);
    }
}
