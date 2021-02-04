/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimpleSynthExAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleSynthExAudioProcessorEditor (SimpleSynthExAudioProcessor&);
    ~SimpleSynthExAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    syn::Synth synthInstance;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleSynthExAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthExAudioProcessorEditor)
};
