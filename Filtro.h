// Create filter
juce::dsp::StateVariableTPTFilter<float> lowpassFilter;

// Prepare
void MiPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Create spec
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    // Prepare filter
    lowpassFilter.prepare (spec);
    lowpassFilter.setType (juce::dsp::StateVariableTPTFilterType::lowpass);
    lowpassFilter.setCutoffFrequency (500.0f);
}

// Process
auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
lowpassFilter.process (context);

// Otros filtros
filter.setType (juce::dsp::StateVariableTPTFilterType::highpass);
filter.setType (juce::dsp::StateVariableTPTFilterType::bandass);