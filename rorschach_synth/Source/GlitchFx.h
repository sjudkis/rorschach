/*
  ==============================================================================

    GlitchFx.h
    Created: 14 Nov 2019 6:15:08pm
    Author:  Sam Judkis

  ==============================================================================
*/

#pragma once

class GlitchFx
{
public:
    void effect(AudioBuffer<float> &outputBuffer, int numSamples)
    {
        for (int start = 0, end = numSamples - 1; start < numSamples && end >= 0; ++start, --end)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                if (start % 2 == 0)
                {
                    outputBuffer.setSample(channel, start, outputBuffer.getSample(channel, end));
                }
                else if (start % 3 == 0)
                {
                    outputBuffer.setSample(channel, start, 0);
                }
            }
        }
    }
};
