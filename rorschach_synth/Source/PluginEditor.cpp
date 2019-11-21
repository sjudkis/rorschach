/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include <OpenGL/gl.h>

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
    glitchButton.addListener(this);
    glitchButton.setWantsKeyboardFocus(false);
    
    glitchButton.setLookAndFeel(&buttonLookAndFeel);
    addAndMakeVisible(&glitchButton);
    
    glitchButton.setColour(TextButton::ColourIds::buttonColourId, Colours::whitesmoke);
    
    glitchButton.setColour(TextButton::ColourIds::buttonOnColourId, Constants::tan);
    
    // Initialize blot background values
    r = Random();
    
    // Fills arrays of blobs
    for (auto i = 0; i < blobCount; ++i)
    {
        blobState.push_back(std::make_pair(std::vector<float>{0.0, 0.0, 0.0, 0.0}, std::vector<float>{0.0, 0.0, 0.0, 0.0}));
        curState.push_back(std::vector<float>{0.0,0.0,0.0,0.0});
    }
    
    // Creates first blob state
    createNextState();
    copyNextToCurState();
    translate(0);
        
    // openGLContext.setComponentPaintingEnabled(true);
    openGLContext.setRenderer(this);
    openGLContext.setContinuousRepainting(true);
    openGLContext.attachTo(*this);
}
Rorschach_synthAudioProcessorEditor::~Rorschach_synthAudioProcessorEditor()
{
	mainDial.setLookAndFeel(nullptr);
    reverbDial.setLookAndFeel(nullptr);
    glitchButton.setLookAndFeel(nullptr);
    processor.keyboardState.removeListener(this);
}

//==============================================================================
void Rorschach_synthAudioProcessorEditor::paint (Graphics& g)
{
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
//    glitchButton.setBounds(300, 50, 60, 60);
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
    if (isInitialRun)
    {
        keyboard.grabKeyboardFocus();
        stopTimer();
        isInitialRun = false;
        startTimer(1000 / updatePerSecond); // Start background renderer
    }
    else
    {
        // Used for drawing openGL background
        if (transitionCounter++ > translateTimeHz + pauseTimeHz)
        {
            copyNextToCurState();
            createNextState();
            transitionCounter = 0;
        }
        else if (transitionCounter > translateTimeHz)
        {
            return;
        }
        translate((transitionCounter/(float)translateTimeHz));
    }
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
        auto glitchState = glitchButton.getToggleState();
        glitchButton.setToggleState(!glitchState, NotificationType::dontSendNotification);
        processor.toggleGlitch(!glitchState);
    }
}

//==============================================================================
// Background rendering code
/**
createNextState creates a next state for a blob to travel to.
*/
void Rorschach_synthAudioProcessorEditor::createNextState()
{
    float x, y;
    float prevX, prevY;
    float nextCircleMaxDistance = circleMaxDim;
    float closenessFactor = .03; // 0 < x < 1, where 1 is abosolutely random values, while 0 creates one large blob
    
    for (int i = 0; i < blobState.size(); i+=2)
    {
        // Decides wether a blot is placed in an absolute random location, or next to the old value.
        if (i > 0 && r.nextFloat() > closenessFactor)
        {
            // spawns new blot close to old one
            x = prevX;
            y = prevY;
            
            // Decide if it is a negative shift or positive
            if (r.nextFloat() >.5)
                x+= r.nextFloat() * nextCircleMaxDistance;
            else
                x-= r.nextFloat() * nextCircleMaxDistance;
            
            if (r.nextFloat() >.5)
                y+= r.nextFloat() * nextCircleMaxDistance;
            else
                y-= r.nextFloat() * nextCircleMaxDistance;
            
            // Handle edge cases where new circle goes off screen
            if (x >= visWidth)
                x-=nextCircleMaxDistance*2;
            else if (x < 0)
                x+=nextCircleMaxDistance*2;
            if (y >=visHeight-padding)
                y-=nextCircleMaxDistance*2;
            else if (y < 0)
                y+=nextCircleMaxDistance*2;
        }
        else
        {
            // spawns new blot not based on prev
            x = r.nextFloat() * visWidth;
            y = r.nextFloat() * (visHeight - padding);
        }
  
        auto dim = (r.nextFloat() * (circleMaxDim - circleMinDim)) + circleMinDim;

        auto& left = blobState[i].second;
        auto& right = blobState[(int64)i + (int64)1].second;

        // set centers of circles
        left[0] = x + dim / 2 - xOffset;
        left[1] = y  - (visHeight / 2) + yOffset;

        right[0] = -x - dim / 2 - xOffset;
        right[1] = y - (visHeight / 2) + yOffset;
    
        left[2] = dim * visWidth;
        right[2] = dim * visWidth;
        left[3] = dim;
        right[3] = dim;
        
        prevX = x;
        prevY = y;
    }
}

/**
 copyNextToCurState is called when the transition period is over, and before a new state is made, the old state is copied into the old state
 */
void Rorschach_synthAudioProcessorEditor::copyNextToCurState()
{
    for (int i = 0; i < blobState.size(); ++i)
    {
        auto& oldState = blobState[i].first;
        auto& newState = blobState[i].second;

        for (int j = 0; j < oldState.size(); j++)
        {
            oldState[j] = newState[j];
        }
    }
}

/**
 Translate updates curState with information needed for OpenGL to draw each circle,
 based on a progress value, which is 0-1, where 1 is reached nextState
 */
void Rorschach_synthAudioProcessorEditor::translate(float progress)
{
    for (int i = 0; i < blobState.size(); i++)
    {
        auto from = blobState[i].first;
        auto to = blobState[i].second;
        
        curState[i][0] = from[0] +  progress * (float)((double)to[0] - from[0]);
        
        curState[i][1] = from[1] +  progress * (float)((double)to[1] - from[1]);
        curState[i][2] = progress * (to[2] - from[2]) + from[2];
        curState[i][3] = progress * (to[3] - from[3]) + from[3];
    }
}

//==============================================================================
// We handle openGL with OpenGL 1 specs, without using JUCE
void Rorschach_synthAudioProcessorEditor::newOpenGLContextCreated() {}
void Rorschach_synthAudioProcessorEditor::openGLContextClosing() {}

void Rorschach_synthAudioProcessorEditor::renderOpenGL()
{
    // Sets background colour
    OpenGLHelpers::clear(Constants::tan);
    
    // Draw each blob
    for (int i = 0; i < curState.size(); i++)
    {
        glPushMatrix(); // Saves center point
        glTranslatef(curState[i][0], curState[i][1], 0.f);  // Translate to (xPos, yPos)
        glBegin(GL_TRIANGLE_FAN);
           glColor3f(0.01, 0.01, 0.01);
           glVertex2f(0.0f, 0.0f);       // Center of circle
           GLfloat angle;
        
        // Values need to be saved
        auto x = curState[i][2];
        auto y = curState[i][3];
        // draw circle
        for (int i = 0; i <= circleSegments; i++) {
           angle = i * 2.0f * PI / circleSegments;
           glVertex2f(cos(angle) *  x, sin(angle) *  y);
        }
        glEnd();
        glPopMatrix(); // Returns center point
    }
    glFlush();
}

/**
 handleRetina may be called in the class' constructor if the background has issues
 rendering the image.
 */
void Rorschach_synthAudioProcessorEditor::handleRetina()
{
    double scaleFactor;
    scaleFactor = juce::Desktop::getInstance().getDisplays().getMainDisplay().scale;
    if (scaleFactor > 1)
    {
        setTransform(juce::AffineTransform::scale(scaleFactor, scaleFactor));
    }
}
