/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Rorschach_synthAudioProcessor::Rorschach_synthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     :  AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        parameterState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    synth.clearVoices();
    
    for (int i = 0; i < 10; i++)
    {
        synth.addVoice(new SynthVoice());
    }
    
    synth.clearSounds();
    synth.addSound(new SynthSound());
    
    glitchState = false;
}

Rorschach_synthAudioProcessor::~Rorschach_synthAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout Rorschach_synthAudioProcessor::createParameterLayout()
{
    // create vector to hold parameters
    std::vector<std::unique_ptr<AudioParameterFloat>> parameters;
    
    // osc1 parameters
    auto osc1Vol = std::make_unique<AudioParameterFloat>(OSC1_VOL_ID, OSC1_VOL_NAME, 0.0f, 1.0, .5f);
    parameters.push_back(std::move(osc1Vol));
    
    // osc2 parameters
    auto osc2Vol = std::make_unique<AudioParameterFloat>(OSC2_VOL_ID, OSC2_VOL_NAME, 0.0f, 1.0, .5f);
    parameters.push_back(std::move(osc2Vol));
    
    // osc3 parameters
    auto osc3Vol = std::make_unique<AudioParameterFloat>(OSC3_VOL_ID, OSC3_VOL_NAME, 0.0f, 1.0, .5f);
    parameters.push_back(std::move(osc3Vol));
    
    // envelope parameters
    auto attack = std::make_unique<AudioParameterFloat>(ATTACK_ID, ATTACK_NAME, 0.001f, 5.0f, 0.001f);
    parameters.push_back(std::move(attack));
    auto decay = std::make_unique<AudioParameterFloat>(DECAY_ID, DECAY_NAME, 0.001f, 2.0f, 0.001f);
    parameters.push_back(std::move(decay));
    auto sustain = std::make_unique<AudioParameterFloat>(SUSTAIN_ID, SUSTAIN_NAME, 0.0f, 1.0f, 0.9f);
    parameters.push_back(std::move(sustain));
    auto release = std::make_unique<AudioParameterFloat>(RELEASE_ID, RELEASE_NAME, 0.001f, 5.0f, 0.1f);
    parameters.push_back(std::move(release));
    
    // delay parameter
    auto delayTime = std::make_unique<AudioParameterFloat>(DELAY_TIME, DELAY_NAME, NormalisableRange<float>(0.0, 2000.0), 0.0);
    parameters.push_back(std::move(delayTime));
    
    // gain parameter
    auto gain = std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, -48.0f, 0.0f, -5.0f);
    parameters.push_back(std::move(gain));
    
    // lfo parameter
    auto lfo = std::make_unique<AudioParameterFloat>(LFO_ID, LFO_NAME, 0.0f, 20.0f, 0.0f);
    parameters.push_back(std::move(lfo));
    
    // lopass parameter
    auto loPassCutoff = std::make_unique<AudioParameterFloat>(LOW_PASS_ID, LOW_PASS_NAME, 0.0f, 7000.0f, 7000.0f);
    parameters.push_back(std::move(loPassCutoff));
    
    // hipass parameter
    auto hiPassCutoff = std::make_unique<AudioParameterFloat>(HIGH_PASS_ID, HIGH_PASS_NAME, 0.0f, 7000.0f, 0.0f);
    parameters.push_back(std::move(hiPassCutoff));
    
    // reverb parameter
    auto reverbAmt = std::make_unique<AudioParameterFloat>(REVERB_AMT, REVERB_NAME, NormalisableRange<float>(0.5, 0.8), 0.0);
    parameters.push_back(std::move(reverbAmt));
    
    return { parameters.begin(), parameters.end() };
}


//==============================================================================
const String Rorschach_synthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Rorschach_synthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Rorschach_synthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Rorschach_synthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Rorschach_synthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Rorschach_synthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Rorschach_synthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Rorschach_synthAudioProcessor::setCurrentProgram (int index)
{
}

const String Rorschach_synthAudioProcessor::getProgramName (int index)
{
    return {};
}

void Rorschach_synthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Rorschach_synthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    synth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void Rorschach_synthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Rorschach_synthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Rorschach_synthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    
    buffer.clear();
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if ((voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))))
        {
            // set envelope sample rate for each voice
            voice->setEnvelopeSampleRate(lastSampleRate); //
            
            float *volParams[3];
            // create float* array containing vol state for each osc
            volParams[0] = parameterState.getRawParameterValue(OSC1_VOL_ID);
            volParams[1] = parameterState.getRawParameterValue(OSC2_VOL_ID);
            volParams[2] = parameterState.getRawParameterValue(OSC3_VOL_ID);
            
            voice->getOscVolParams(volParams);
            
            voice->getEnvelopeParams(parameterState.getRawParameterValue(ATTACK_ID),
                                     parameterState.getRawParameterValue(DECAY_ID),
                                     parameterState.getRawParameterValue(SUSTAIN_ID),
                                     parameterState.getRawParameterValue(RELEASE_ID));
            
            voice->getGainParam(parameterState.getRawParameterValue(GAIN_ID));
            
            int samplesToDelay = *parameterState.getRawParameterValue(DELAY_TIME) * lastSampleRate * 0.001;
            voice->setDelaySamples(samplesToDelay);
            voice->setReverbAmt(*parameterState.getRawParameterValue(REVERB_AMT));
            
            voice->setGlitch(glitchState);
            voice->setLfoState(lfoButtonState);
            
            voice->setLfoFreq(*parameterState.getRawParameterValue(LFO_ID));
            voice->setLoPassCutoff(*parameterState.getRawParameterValue(LOW_PASS_ID));
            voice->setHiPassCutoff(*parameterState.getRawParameterValue(HIGH_PASS_ID));
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    
}

//==============================================================================
bool Rorschach_synthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Rorschach_synthAudioProcessor::createEditor()
{
    return new Rorschach_synthAudioProcessorEditor (*this);
}

//==============================================================================
void Rorschach_synthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Rorschach_synthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Rorschach_synthAudioProcessor();
}


//void Rorschach_synthAudioProcessor::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
//{
//    
//}

void Rorschach_synthAudioProcessor::keyboardNoteOn(int midiChannel, int midiNoteNumber, float velocity)
{
    synth.noteOn(midiChannel, midiNoteNumber, velocity);
}

void Rorschach_synthAudioProcessor::keyboardNoteOff(int midiChannel, int midiNoteNumber, float velocity)
{
    synth.noteOff(midiChannel, midiNoteNumber, velocity, true);
}

//==============================================================================
double Rorschach_synthAudioProcessor::getDelayInMilis ()
{
    return this->delayInMilis;
}

void Rorschach_synthAudioProcessor::setDelayInMilis (double delayInMilis)
{
    this->delayInMilis = delayInMilis;
}

double Rorschach_synthAudioProcessor::getReverbAmt ()
{
    return this->reverbAmt;
}

void Rorschach_synthAudioProcessor::setReverbAmt (double reverbAmt)
{
    this->reverbAmt = reverbAmt;
}

//==============================================================================
void Rorschach_synthAudioProcessor::toggleGlitch(bool state)
{
    glitchState = state;
}

void Rorschach_synthAudioProcessor::toggleLfoButton(bool state)
{
    lfoButtonState = state;
}
