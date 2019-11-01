/*
  ==============================================================================

    DelayFx.h
    Created: 20 Oct 2019 2:04:49pm
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once

#include "CircularBuffer.h"


class DelayFx
{
public:
    DelayFx ()
    {
        delayBufferL.createCircularBuffer(88200);
        delayBufferL.flushBuffer();
        
        delayBufferR.createCircularBuffer(88200);
        delayBufferR.flushBuffer();
        
        delaySamples = 22050;
    }
    
    void effect (AudioBuffer<float> &outputBuffer, int sample)
    {
        if (delaySamples == 0) return;
        
        float ynL = delayBufferL.readBuffer(delaySamples);
        float y1L = delayBufferL.readBuffer(8000)*0.5;
        float y2L = delayBufferL.readBuffer(2000)*0.5;
        
        float ynR = delayBufferR.readBuffer(delaySamples);
        float y1R = delayBufferR.readBuffer(4000)*0.5;
        float y2R = delayBufferR.readBuffer(1000)*0.5;
        
        float dnL = outputBuffer.getSample(0, sample)*0.3 + (0.7*ynL);
        float dnR = outputBuffer.getSample(1, sample)*0.3  + (0.7*ynR);
        
        delayBufferL.writeBuffer(dnR);
        delayBufferR.writeBuffer(dnL);
        
        outputBuffer.addSample(0,
                               sample,
                               (outputBuffer.getSample(0, sample)*0.5
                                + (ynL + y1L + y2L)*0.5) * 0.125);
        outputBuffer.addSample(1,
                               sample,
                               (outputBuffer.getSample(1, sample)*0.5
                                + (ynR + y1R + y2R)*0.5) * 0.125);
    }
    
    void setDelaySamples (int delaySamples)
    {
        if (delaySamples != this->delaySamples)
        {
            delayBufferL.flushBuffer();
            delayBufferR.flushBuffer();
        }
        this->delaySamples = delaySamples;
    }
    
private:
    CircularBuffer<float> delayBufferL;
    CircularBuffer<float> delayBufferR;
    int delaySamples;
};
