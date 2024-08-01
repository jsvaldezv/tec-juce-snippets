// Create noise
juce::dsp::Chorus<float> phaser;

// Prepare
void MiPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Create spec
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    // Prepare phaser
    phaser.prepare (spec);
    phaser.setRate (1.0f);
    phaser.setDepth (100.0f);
    phaser.setCentreFrequency (0.8f);
    phaser.setFeedback (0.5f);
    phaser.setMix (0.5f);
}

// Process
auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
phaser.process (context);