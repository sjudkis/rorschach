/*
  ==============================================================================

    ReverbFx.h
    Created: 10 Nov 2019 10:39:31am
    Author:  Zachary Anderson

  ==============================================================================
*/

#pragma once

#include "CircularBuffer.h"

class ReverbFx
{
public:
    ReverbFx ()
    {
        combBuffer1.createCircularBuffer(88200);
        combBuffer1.flushBuffer();
        
        combBuffer2.createCircularBuffer(88200);
        combBuffer2.flushBuffer();
        
        combBuffer3.createCircularBuffer(88200);
        combBuffer3.flushBuffer();
        
        combBuffer4.createCircularBuffer(88200);
        combBuffer4.flushBuffer();
        
        allBuffer1.createCircularBuffer(88200);
        allBuffer1.flushBuffer();
        
        allBuffer2.createCircularBuffer(88200);
        allBuffer2.flushBuffer();
        
        delaySamples1 = (int) 313.0*44.1;
        delaySamples2 = (int) 233.0*44.1;
        delaySamples3 = (int) 127.0*44.1;
        delaySamples4 = (int) 43.0*44.1;
        delaySamples5 = (int) 31.0*44.1;
        delaySamples6 = (int) 89.0*44.1;
        
        g1 = 0.3;
        g2 = -0.4;
        g3 = 0.6;
        g4 = -0.7;
        
        yn1 = 0.0;
        yn2 = 0.0;
        wet = 0.0;
        
    }
    
    void effect (AudioBuffer<float> &outputBuffer, int sample, float gain)
    {
        float wn1 = combBuffer1.readBuffer(delaySamples1);
        float wn2 = combBuffer2.readBuffer(delaySamples2);
        float wn3 = combBuffer3.readBuffer(delaySamples3);
        float wn4 = combBuffer4.readBuffer(delaySamples4);
        
        // Process Low-Pass Comb Filters
        float dn1 = outputBuffer.getSample(0, sample)*0.3 + filter.lores(g1*wn1, 440, 1.0);
        float dn2 = outputBuffer.getSample(0, sample)*0.3 + filter.lores(g2*wn2, 440, 1.0);
        float dn3 = outputBuffer.getSample(0, sample)*0.3 + filter.lores(g3*wn3, 440, 1.0);
        float dn4 = outputBuffer.getSample(0, sample)*0.3 + filter.lores(g4*wn4, 440, 1.0);
        
        combBuffer1.writeBuffer(dn4);
        combBuffer2.writeBuffer(dn3);
        combBuffer3.writeBuffer(dn2);
        combBuffer4.writeBuffer(dn1);
        
        float combMix = (dn1 + dn2 + dn3 + dn4) / 8;
        
        // Process All-Pass Filters
        
        float vn1 = allBuffer1.readBuffer(delaySamples5);
        
        allBuffer1.writeBuffer(combMix);
        
        yn1 = (-0.5*combMix) + vn1 + (wet*yn1);

        
        float vn2 = allBuffer2.readBuffer(delaySamples6);
        
        allBuffer2.writeBuffer(yn1);

        yn2 = (-0.5*yn1) + vn2 + (wet*yn2);
        
        // Output
        outputBuffer.addSample(0, sample, yn2 * 0.05 * gain);
        outputBuffer.addSample(1, sample, yn2 * 0.05 * gain);
    }
    
    void setWetMix (float wet)
    {
        this->wet = wet;
    }
    
    
private:
    CircularBuffer<float> combBuffer1;
    CircularBuffer<float> combBuffer2;
    CircularBuffer<float> combBuffer3;
    CircularBuffer<float> combBuffer4;
    CircularBuffer<float> allBuffer1;
    CircularBuffer<float> allBuffer2;
    maxiFilter filter;
    int delaySamples1;
    int delaySamples2;
    int delaySamples3;
    int delaySamples4;
    int delaySamples5;
    int delaySamples6;
    float yn1;
    float yn2;
    float g1;
    float g2;
    float g3;
    float g4;
    float wet;
};

