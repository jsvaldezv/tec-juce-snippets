// Process Stereo LFO Amplitude Modulation
for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
{
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        float inSample = buffer.getSample (channel, i);
        
        // y = 0.5*sin(2pi*ft) + 0.5
        float sinValue = (0.5f * sinf (juce::MathConstants<float>::twoPi * frequency * time[channel])) + 0.5f;
        
        float outSample = inSample * sinValue;
        
        buffer.setSample (channel, i, outSample);
        
        //time[channel] = time[channel] + deltaTime[channel];
        time[channel] += deltaTime[channel];
        
        if (time[channel] >= 1.0f)
            time[channel] = 0.0f;
    }
}

// Process Stereo Sin Oscillator
for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
{
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        float inSample = buffer.getSample (channel, i);
        
        float sinValue = sinf (juce::MathConstants<float>::twoPi * frequency * time[channel]);
        
        float outSample = inSample + sinValue;
        
        buffer.setSample (channel, i, outSample);
        
        //time[channel] = time[channel] + deltaTime[channel];
        time[channel] += deltaTime[channel];
        
        if (time[channel] >= 1.0f)
            time[channel] = 0.0f;
    }
}