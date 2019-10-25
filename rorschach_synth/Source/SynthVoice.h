/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Oct 2019 1:43:04pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "../Maximilian/maximilian.h"


#define NUM_OSCILLATORS 3

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound *sound) override
    {
        return dynamic_cast <SynthSound*>(sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber,float velocity, SynthesiserSound * sound, int currentPitchWheelPosition) override
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        allowTailOff = true;
//        level = 0;
        env1.trigger = 0;
        if (velocity == 0)
            clearCurrentNote();
    }
    
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    void getOscVolParams(float *oscVolState[])
    {
        for (int i = 0; i < NUM_OSCILLATORS; i++)
        {
            oscVols[i] = *oscVolState[i];
        }
    }
    
    
    void renderNextBlock (AudioBuffer <float> & outputBuffer, int startSample, int numSamples) override
    {
        env1.setAttack(.2);
        env1.setDecay(5000);
        env1.setSustain(0.9);
        env1.setRelease(1000);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double wave = osc1.sinewave(frequency) * oscVols[0];
            wave += osc2.square(frequency) * oscVols[1];
            wave += osc3.saw(frequency) * oscVols[2];
            
            double sound = env1.adsr(wave, env1.trigger) * level;
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, sound);
            }
            ++startSample;
        }
    }
    
private:
    double frequency;
    double level;
    
    float oscVols[3];
    
    maxiOsc osc1;
    maxiOsc osc2;
    maxiOsc osc3;
    
    maxiEnv env1;
};


