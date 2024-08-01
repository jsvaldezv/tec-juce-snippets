// Create reverb
juce::dsp::Reverb reverb;

// Prepare
void MiPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Create spec
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    // Prepare reverb
    reverb.prepare (spec);

    juce::dsp::Reverb::Parameters reverbParameters;
    reverbParameters.roomSize = 0.0f;
    reverbParameters.damping = 0.0f;
    reverbParameters.wetLevel = 0.0f;
    reverbParameters.dryLevel = 0.0f;
    reverbParameters.width = 0.0f;
    reverbParameters.freezeMode = 0.0f;

    reverb.setParameters(reverbParameters);
}

// Process
auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
reverb.process(context);