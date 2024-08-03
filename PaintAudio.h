// En processor.h    
juce::AudioBuffer<float> samples;

// En processor.cpp
samples = buffer;

// En component.h
juce::AudioVisualiserComponent audioVisualiserComponent { 2 };

// En component.cpp
audioVisualiserComponent.setBufferSize (audioProcessor.getBlockSize());
addAndMakeVisible (audioVisualiserComponent);

startTimerHz (30);

// En resized
void PaintAudio::resized()
{
    audioVisualiserComponent.setBounds (x, y, w, h);
}

// En timer
void PaintAudio::timerCallback()
{
    audioVisualiserComponent.pushBuffer (audioProcessor.samples);
}