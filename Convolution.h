// Create Convolution
juce::dsp::Convolution convolution;

// Prepare
void MiPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Create spec
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    // Prepare convolution
    convolution.reset();
    convolution.prepare(spec);
    
    // Load IR from binary data
    convolution.loadImpulseResponse(BinaryData::Sample_wav,
                                    BinaryData::Sample_wavSize,
                                    juce::dsp::Convolution::Stereo::yes,
                                    juce::dsp::Convolution::Trim::yes,
                                    0,
                                    juce::dsp::Convolution::Normalise::yes);
}

// Process
auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
convolution.process (context);