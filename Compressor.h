// Create compressor
juce::dsp::Chorus<float> compressor;

// Prepare
void MiPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Create spec
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    // Prepare compressor
    compressor.prepare (spec);
    compressor.setThreshold (1.0f);
    compressor.setRatio (100.0f);
    compressor.setAttack (0.8f);
    compressor.setRelease (0.5f);
}

// Process
auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
compressor.process (context);