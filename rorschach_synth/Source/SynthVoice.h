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
#include "GlitchFx.h"

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
    
    void setGlitch(bool val)
    {
        glitchState = val;
    }
    
    void setLfoState(bool state)
    {
        lfoState = state;
    }
    
    void renderNextBlock (AudioBuffer <float> & outputBuffer, int startSample, int numSamples) override
    {
        deArtifacting(numSamples);
        
        envelope.setParameters(envelopeParams);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            if (sample > 0) incRampParams(); // Increment ramped parameters
            
            effectedGain = gainRamp;
            
            // Alter params based on LFO
            double freqMod = frequency;
            if (lfoFreq > 0.0)
            {
                if (lfoState)
                {
                    effectedGain *= ((lfo.sinewave(lfoFreq) / 2) + 0.5);
                }
                else
                {
                    freqMod += (lfo.sinewave(lfoFreq) * 6.0);
                }
            }
            
            // Mix Oscillators
            double wave = osc1.sinewave(freqMod) * oscVols[0];
            wave += osc2.square(freqMod) * oscVols[1];
            wave += osc3.saw(freqMod) * oscVols[2];
            wave *= level;
            
            // Process main gain
            wave *= effectedGain;
            
            // Process filters
            wave = loPassFilter.lores(wave, loPassCutoffRamp, 1.0);
            wave = highPassFilter.hires(wave, hiPassCutoffRamp, 1.0);
            
            // Process Envelope
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, envelope.getNextSample() * wave);
            }
            
            // Process Reverb Effect
            if (reverbAmt > 0.5) reverbFx.effect(outputBuffer, startSample, gainRamp);
            
            // Process Delay Effect
            delayFx.effect(outputBuffer, startSample, gainRamp);
            
            ++startSample;
        }
    
        // Process Garble Effect
        if (glitchState)
            glitchFx.effect(outputBuffer, numSamples);
    }
    
    void deArtifacting(int numSamples)
    {
        gainInc = (gain - gainRamp) / numSamples;
        loPassCutoffInc = (loPassCutoff - loPassCutoffRamp) / numSamples;
        hiPassCutoffInc = (hiPassCutoff - hiPassCutoffRamp) / numSamples;
    }
    
    void incRampParams()
    {
        gainRamp += gainInc;
        loPassCutoffRamp += loPassCutoffInc;
        hiPassCutoffRamp += hiPassCutoffInc;
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
    
    void setLoPassCutoff(double loPassCutoff)
    {
        this->loPassCutoff = loPassCutoff;
    }
    
    void setHiPassCutoff(double hiPassCutoff)
    {
        this->hiPassCutoff = hiPassCutoff;
    }
    
private:
    double frequency;
    double level;
    
    float oscVols[3];
    float gain;
    float gainRamp = 0.562f;
    float gainInc = 0.0f;
    float effectedGain;
    
    maxiOsc osc1;
    maxiOsc osc2;
    maxiOsc osc3;
    maxiOsc lfo;
    
    maxiFilter loPassFilter;
    maxiFilter highPassFilter;
    
    DelayFx delayFx;
    ReverbFx reverbFx;
    
    GlitchFx glitchFx;
    bool glitchState;
    
    bool lfoState;
    
    double reverbAmt;
    double lfoFreq;
    double loPassCutoff;
    double loPassCutoffRamp = 7000.0f;
    double loPassCutoffInc = 0.0f;
    double hiPassCutoff;
    double hiPassCutoffRamp = 0.0f;
    double hiPassCutoffInc = 0.0f;
    
    ADSR envelope;
    ADSR::Parameters envelopeParams;
};


