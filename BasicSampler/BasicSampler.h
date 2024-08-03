// Declare in .h
void loadFile();

juce::Synthesiser mySampler;
juce::AudioFormatManager formatManager;
juce::AudioFormatReader* formatReader {nullptr};

juce::ADSR::Parameters myADSRParameters;

std::atomic<bool> isNotePlayed {false};
std::atomic<int> sampleCount {0};

// Init sampler
formatManager.registerBasicFormats();

for(int i = 0; i < 3; i++)
    mySampler.addVoice (new juce::SamplerVoice());

// In destructor
formatReader = nullptr;

// Prepare sampler
mySampler.setCurrentPlaybackSampleRate(sampleRate);

for(int i = 0; i < getTotalNumOutputChannels(); i++)
{
    ptrLFO[i]->prepareLFO(sampleRate);
}

// Process sampler
juce::MidiMessage m;
juce::MidiBuffer::Iterator it {midiMessages};
int sample;

while(it.getNextEvent(m, sample))
{
    if(m.isNoteOn())
        isNotePlayed = true;
    else if(m.isNoteOff())
        isNotePlayed = false;
}

sampleCount = isNotePlayed ? sampleCount += buffer.getNumSamples() : 0;
mySampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

// Load File
void MySamplerAudioProcessor::loadFile()
{
    juce::FileChooser chooser {"Carga tu sonido"};
    
    if(chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        formatReader = formatManager.createReaderFor(file);
    }
    
    juce::BigInteger range;
    range.setRange(0, 128, true);
    
    mySampler.addSound(new juce::SamplerSound("Sample", *formatReader, range, 60, 0.1, 0.1, 10));
}