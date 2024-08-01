// Create noise
juce::dsp::Chorus<float> noiseGate;

// Prepare
void MiPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Create spec
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    // Prepare noise gate
    noiseGate.prepare (spec);
    noiseGate.setThreshold (1.0f);
    noiseGate.setRatio (100.0f);
    noiseGate.setAttack (0.8f);
    noiseGate.setRelease (0.5f);
}

// Process
auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
noiseGate.process (context);