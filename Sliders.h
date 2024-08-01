// Crear Slider y Attach
juce::Slider slider;
std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttach;

// Preparar slider
slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
addAndMakeVisible (slider);

sliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "Slider_ID", slider);

// Set size y posición
void MiPluginAudioProcessorEditor::resized()
{
    slider.setBounds (x, y, width, height);
}