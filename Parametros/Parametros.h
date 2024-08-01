// Declaraciones en .h
juce::AudioProcessorValueTreeState apvts;
juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

// Crear parametros
juce::AudioProcessorValueTreeState::ParameterLayout MiPluginAudioProcessor::createParameters()
{
    /*
    SliderFloat -> parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "SliderFloat", 1 }, "SliderFloat", 0.0f, 100.0f, 80.0f));
    SliderInt -> parameters.add (std::make_unique<juce::AudioParameterInt>(juce::ParameterID { "SliderInt", 1 }, "SliderInt", 0, 100, 50));
    Button -> parameters.add (std::make_unique<juce::AudioParameterBool>(juce::ParameterID { "Button", 1 } , "Button", true));
    Options -> parameters.add (std::make_unique<juce::AudioParameterChoice>(juce::ParameterID { "Options", 1 }, "Options", juce::StringArray {"1/2", "1/4", "1/8", "1/16"}, 2));
    */

    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    
    parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "Parametro", 1 }, "Volume", 0.0f, 1.0f, 1.0f));

    return parameters;
}

// Obtener valor de slider
float parameterValue = *apvts.getRawParameterValue("Parametro");

// Activar GUI por Default
juce::AudioProcessorEditor* MiPluginAudioProcessor::createEditor()
{
    //return new MiPluginAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}
