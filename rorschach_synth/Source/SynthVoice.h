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
#include "DelayFx.h"
#include "ReverbFx.h"


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
        envelope.noteOn();
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        envelope.noteOff();
        allowTailOff = true;
//        level = 0;
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
    
    void getEnvelopeParams(float *att, float *dec, float *sus, float *rel)
    {
        envelopeParams.attack = *att;
        envelopeParams.decay = *dec;
        envelopeParams.sustain = *sus;
        envelopeParams.release = *rel;
        
        envelope.setParameters(envelopeParams);
    }
    
    void setEnvelopeSampleRate(double sampleRate)
    {
        envelope.setSampleRate(sampleRate);
    }
    
    void getGainParam(float *g)
    {
        gain = pow(10, (*g / 20.0));
    }
    
    void renderNextBlock (AudioBuffer <float> & outputBuffer, int startSample, int numSamples) override
    {
        envelope.setParameters(envelopeParams);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double freqMod = 0.0;
            if (lfoFreq > 0.0)
            {
                freqMod = (lfo.sinewave(lfoFreq) * 12);
            }
            double wave = osc1.sinewave(frequency + freqMod) * oscVols[0];
            wave += osc2.square(frequency + freqMod) * oscVols[1];
            wave += osc3.saw(frequency + freqMod) * oscVols[2];
            wave *= level;
            wave *= gain;
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, envelope.getNextSample() * wave);
            }
            
            if (reverbAmt > 0.5) reverbFx.effect(outputBuffer, startSample, gain);
            
            delayFx.effect(outputBuffer, startSample, gain);

            ++startSample;
        }
    
        
    }
    
    void setDelaySamples(int delaySamples)
    {
        delayFx.setDelaySamples(delaySamples);
    }
    
    void setReverbAmt(double reverbAmt)
    {
        this->reverbAmt = reverbAmt;
        reverbFx.setWetMix(reverbAmt);
    }
    
    void setLfoFreq(double lfoFreq)
    {
        this->lfoFreq = lfoFreq;
    }
    
private:
    double frequency;
    double level;
    
    float oscVols[3];
    float gain;
    
    maxiOsc osc1;
    maxiOsc osc2;
    maxiOsc osc3;
    maxiOsc lfo;
    
    DelayFx delayFx;
    ReverbFx reverbFx;
    
    double reverbAmt;
    double lfoFreq;
    
    ADSR envelope;
    ADSR::Parameters envelopeParams;
};


