// Reducir 6dB a señal
for (int channel = 0; channel < buffer.getNumChannels(); channel++)
{
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        // Obtener el sample de entrada
        float sample = buffer.getSample(channel, i);

        // Reducir 6dB a sample
        float processedSample = sample * 0.5f;

        // Regresar sample para escucharlo
        buffer.setSample(channel, i, processedSample);
    }
}

// Convertir de dB a lineal
float linearValue = juce::Decibels::decibelsToGain (decibelsValue, -100.0f)