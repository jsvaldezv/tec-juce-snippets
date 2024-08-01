// Create variables
juce::Image backgroundImage;
juce::ImageComponent backgroundComponent;

// Prepare background
backgroundImage = juce::ImageCache::getFromMemory (BinaryData::background_png, BinaryData::background_pngSize);
backgroundComponent.setImage (backgroundImage);
addAndMakeVisible (backgroundComponent);

// Set size
backgroundComponent.setBounds (getLocalBounds());