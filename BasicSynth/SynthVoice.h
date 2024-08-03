#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    
    SynthVoice();
    ~SynthVoice() override;
    
    bool canPlaySound (juce::SynthesiserSound*) override;
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    
    void stopNote (float velocity, bool allowTailOff) override;
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void prepareToPlay (double inSampleRate, int inSamplesPerBlock, int inNumChannels);
    
    void updateParameters (juce::AudioProcessorValueTreeState& apvts);
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
private:
    
    bool isPrepared { false };
    int midiNote   { 0 };
    
    juce::dsp::Oscillator<float> osc;
    juce::dsp::Gain<float> gain;
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    juce::AudioBuffer<float> synthBuffer;
};