#include "SynthVoice.h"

SynthVoice::SynthVoice() {}

SynthVoice::~SynthVoice() {}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    auto frequency = static_cast<float> (juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber));
    
    midiNote = midiNoteNumber;
    osc.setFrequency (frequency);
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue) {}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue) {}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels)
{
    adsr.setSampleRate (sampleRate);
    
    adsrParams.attack   = 0.01f;
    adsrParams.decay    = 0.5f;
    adsrParams.sustain  = 0.5f;
    adsrParams.release  = 1.0f;
    adsr.setParameters (adsrParams);
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate         = sampleRate;
    spec.numChannels        = static_cast<juce::uint32> (numChannels);
    spec.maximumBlockSize   = static_cast<juce::uint32> (samplesPerBlock);
    
    osc.prepare     (spec);
    osc.initialise  ([](float x) { return x / juce::MathConstants<float>::pi * x; });
    
    gain.prepare (spec);

    isPrepared = true;
}

void SynthVoice::updateParameters(juce::AudioProcessorValueTreeState& apvts)
{
    auto gainValue = apvts.getRawParameterValue("Gain")->load();
    gain.setGainDecibels (gainValue);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);
    
    if (!isVoiceActive())
        return;
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    
    juce::dsp::ProcessContextReplacing<float> block (audioBlock);
    
    osc.process (block);
    gain.process (block);
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (!adsr.isActive())
            clearCurrentNote();
    }
}