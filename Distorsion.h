// Soft Clipping
for (int channel = 0; channel < buffer.getNumChannels(); channel++)
{
    for (int i = 0; i < buffer.getNumSamples(); i ++)
    {
        float sample = buffer.getSample(channel, i);

        float out = (sample) - (powf(sample, 3.0f) / 3.0f);
        
        buffer.setSample(channel, i, out);
    }
}

// More distortions

float Distortions::hyperbolicTangent (float sample, float gain)
{
    gain = gain + 1.0f;
    float out = (tanh(gain * sample)) / (tanh(gain));
    out = out * 0.4f;

    return out;
}

float Distortions::diodeClipping (float sample, float gain)
{    
    float diodeClippingAlgorithm = expf((0.1f * sample) / (0.0253f * 1.68f)) - 1.0f;
    float out = 2 / juce::MathConstants<float>::pi * atan(diodeClippingAlgorithm * (gain * 16));    
    out = out * 0.3f;
    
    return out;
}

float Distortions::sigmoid (float sample, float gain)
{
    gain = gain + 1.0f;
    float out = (2.0f * (1.0f / (1.0f + expf(-gain * sample)))) - 1;
    out = out / log(gain);
    
    return out;
}

float Distortions::arcTanDistortion (float sample, float gain)
{
    gain = gain + 1.0f;
    float out = (2.0f / juce::MathConstants<float>::pi) * atan(gain * sample);
    out = out / log(gain);
    
    return out;
}

float Distortions::softClipper (float sample, float gain)
{
    float newInput = sample * (gain / 10);
    float out = 0.0;
    
    if (newInput >= 1.0f)
        out = 1.0f;
    else if ((newInput > -1) && (newInput < 1))
        out = (3.0f / 2.0f) * (newInput - (powf(newInput, 3.0f) / 3.0f));
    else if (newInput <= -1)
        out = -1.0f;
    
    out = out * 0.5f;
    
    return out;
}

float Distortions::fuzzExponential (float sample, float gain)
{
    float newInput = sample * gain;
    float out;
    
    // Soft clipping
    if (newInput < 0.0f)
        out = -1.0f *  (1.0f - expf(-abs(newInput)));
    else
        out = 1.0f * (1.0f - expf(-abs(newInput)));
 
    // Half Wave Rectifier
    out = 0.5f * (out + abs(out));
    out = out * 0.8f;
    
    return out;
}