// Crear button y attach
juce::ImageButton button;
juce::Image myImageOff, myImageOn;
std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> buttonAttach;

// Preparar button
myImageOn = juce::ImageFileFormat::loadFrom (BinaryData::imageOn_png, BinaryData::imageOn_pngSize);
myImageOff = juce::ImageFileFormat::loadFrom (BinaryData::imageOff_png, BinaryData::imageOff_pngSize);

button.setClickingTogglesState (true);
button.setImages (false, true, false, myImageOff, 1.0f, {}, myImageOff, 1.0f, {}, myImageOn, 1.0f, {});
addAndMakeVisible (button);

buttonAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.apvts, "Button_ID", button);

// Set size y posición
void MiPluginAudioProcessorEditor::resized()
{
    button.setBounds (x, y, width, height);
}