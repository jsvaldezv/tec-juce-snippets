// Declarar en .h
void initSynth();
juce::Synthesiser synth;

// Init synth
void BasicSynthAudioProcessor::initSynth()
{
    synth.addSound (new SynthSound());
    
    for (auto i = 0; i < 5; i++)
        synth.addVoice (new SynthVoice());
}

// Prepare synth
void BasicSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(i)))
            voice->prepareToPlay (sampleRate, samplesPerBlock, getTotalNumInputChannels());
    }
}

// Proces synth
for (int i = 0; i < synth.getNumVoices(); i++)
{
    if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        voice->updateParameters (apvts);
}

synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());