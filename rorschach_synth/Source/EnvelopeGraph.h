/*
  ==============================================================================

    EnvelopeGraph.h
    Created: 1 Nov 2019 2:06:14pm
    Author:  Andrew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"

class EnvelopeGraph : public Component
{
public:
	EnvelopeGraph()
	{
	}

	void paint(Graphics& g) override
	{
		auto widthStart = 0;
		auto widthEnd = getWidth();
		auto heightStart = 0;
		auto heightEnd = getHeight();

		// brown background
		juce::Rectangle<float> envelopeArea(Point<float>(widthStart, heightStart), Point<float>(widthEnd, heightEnd));
		g.setColour(Constants::brown);
		g.fillRoundedRectangle(envelopeArea, 5.5f);

		// calculates final points
		auto bottom = (double)heightEnd - 10;
		auto attackDecayWidth = widthStart + 40;
		auto sustainReleaseWidth = widthStart + 140;
		auto attackLength = attackDecayWidth - 30 * attack;
		auto decayLength = 20 * decay + attackDecayWidth;
		auto sustainHeight = (double)bottom - (((double)bottom - heightStart - 10.0f) * sustain);
		auto releaseLength = (double)20 * release + sustainReleaseWidth;

		auto attackHeight = attack < .01 && decay < .01 ? sustainHeight : (double)heightStart + 10;

		// path is overdraw to remove rounded edges
		Path adsrPath;
		adsrPath.startNewSubPath(Point<float>(widthStart - 5, bottom));
		adsrPath.lineTo(Point<float>(attackLength, heightEnd - 10)); // To start of attack
		adsrPath.lineTo(Point<float>(attackDecayWidth, attackHeight));	// To end of attack/start of decay
		adsrPath.lineTo(Point<float>(decayLength, sustainHeight));	// To end of decay/start of sustain
		adsrPath.lineTo(Point<float>(sustainReleaseWidth, sustainHeight));	// To end of sustain/start of release
		adsrPath.lineTo(Point<float>(releaseLength, bottom));	// To end of graph
		adsrPath.lineTo(Point<float>(widthEnd+5, bottom)); // Line after release
		g.setColour(Constants::tan);
		g.strokePath(adsrPath, PathStrokeType(5.0f, PathStrokeType::JointStyle::curved));
	}

	void onAttackChange(double attackVal)
	{
		attack = attackVal;
	}

	void onDecayChange(double decayVal)
	{
		decay = decayVal;
	}

	void onSustainChange(double sustainVal)
	{
		sustain = sustainVal;
	}

	void onReleaseChange(double releaseVal)
	{
		release = releaseVal;
	}


private:
	double attack = 0;
	double decay = 0;
	double sustain = 0;
	double release = 0;
};
