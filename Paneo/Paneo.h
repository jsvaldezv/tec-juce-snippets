// Constant Power Panning
for (int channel = 0; channel < buffer.getNumChannels(); channel++)
{
    for (int i = 0; i < buffer.getNumSamples(); i ++)
    {
        float sample = buffer.getSample(channel, i);
        
        // Process Left Channel
        if (channel == 0)
        {
            sample *= sqrtf( ( (pi/2.0f) - panningValue) * (2.0f/pi) * (cosf(panningValue)) );
        }
        else
        {
            sample *= sqrtf (panningValue * (2.0f/pi) * sinf(panningValue));
        }
        
        buffer.setSample(channel, i, sample);
    }
}