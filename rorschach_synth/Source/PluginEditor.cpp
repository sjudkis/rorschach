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
    addAndMakeVisible(&glitchButton);
    glitchButton.addListener(this);
    glitchButton.setButtonText("Glitch Off");
    
    glitchButton.setColour(TextButton::ColourIds::buttonColourId, Constants::brown);
    glitchButton.setColour(TextButton::ColourIds::textColourOffId, Constants::tan);
    
    glitchButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred); //Constants::tan);
    glitchButton.setColour(TextButton::ColourIds::textColourOnId, Colours::white); //Constants::brown);
    
}
Rorschach_synthAudioProcessorEditor::~Rorschach_synthAudioProcessorEditor()
{
	mainDial.setLookAndFeel(nullptr);
    reverbDial.setLookAndFeel(nullptr);
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
    
    glitchButton.setBounds(10, visualizerHeight - 70, 60, 60);
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

void Rorschach_synthAudioProcessorEditor::buttonClicked(Button *button)
{
    keyboard.grabKeyboardFocus();
    if (button == &glitchButton)
    {
        bool glitchOn = glitchButton.getToggleState();
        processor.toggleGlitch(!glitchOn);
        glitchButton.setToggleState(!glitchOn, NotificationType::dontSendNotification);
        // check if button is on
        if (glitchOn)
        {
            glitchButton.setButtonText("Glitch Off");
        }
        else
        {
            glitchButton.setButtonText("Glitch On");
        }
        
    
    }
}
