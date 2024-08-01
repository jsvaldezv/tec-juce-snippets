// Create filter
juce::dsp::StateVariableTPTFilter<float> lowpassFilter;

// Prepare filter
lowpassFilter.prepare (spec);
lowpassFilter.setType (juce::dsp::StateVariableTPTFilterType::lowpass);
lowpassFilter.setCutoffFrequency (500.0f);

// Process filter
auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);

lowpassFilter.process (context);

// Otros filtros
filter.setType (juce::dsp::StateVariableTPTFilterType::highpass);
filter.setType (juce::dsp::StateVariableTPTFilterType::bandass);