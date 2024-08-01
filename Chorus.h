// Create chorus
juce::dsp::Chorus<float> chorus;

// Prepare
void MiPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Create spec
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    // Prepare chorus
    chorus.prepare (spec);
    chorus.setDepth (1.0f);
    chorus.setCentreDelay (100.0f);
    chorus.setFeedback (0.8f);
    chorus.setMix (0.5f);
}

// Process
auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
chorus.process (context);