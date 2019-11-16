/*
  ==============================================================================

    GlitchButton.h
    Created: 14 Nov 2019 6:45:23pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class GlitchButton    : public Component//,
//                        public Button::Listener
{
public:
    GlitchButton(Rorschach_synthAudioProcessor& p) : processor(p)
    {
        button.setButtonText("Glitch");
        addAndMakeVisible(&button);
//        button.addListener(this);
        
    }

    ~GlitchButton()
    {
    }

    void paint (Graphics& g) override
    {
        
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        button.setBounds(getLocalBounds());
    }

//    void buttonClicked(Button *b) override
//    {
//        if (b == &button)
//        {
//            processor.toggleGlitch();
//        }
//    }
private:
    Rorschach_synthAudioProcessor& processor;
    
    TextButton button;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlitchButton)
};
