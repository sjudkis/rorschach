# Rorschach Synthesizer

OSU Online CS capstone project. The goal was to build a visually reactive synthesizer application, using the JUCE C++ framework. The synthesizer will consist of multiple oscillators and effects. There will also be a visual display showing images or animations that change in response to audio effects being placed on the synthesized sound. We intend to use the Maximilian C++ library to provide some digital signal processing (DSP) abstractions.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

[JUCE](https://juce.com/) must be used to create the necessary environment files.

The synth has been tested on Windows 10, Visual Studios 2019 and macOS Catalina, XCode, however it might run on any OS/IDE JUCE supports.

### Installing

Installation on both Windows/MacOS is basically the same.

1. Clone this repository.
2. With juce installed, open `rorschach_synth/rorschach_synth.jucer`.
3. Choose the correct platform, and click VS2019/Xcode icon to create platform-specific code.
4. Build project in your IDE, and the synth should open.

## Features

Press info key at the top left of the synth to see labels of buttons and sliders in the blot region.

This section gives a brief, high level description of each effect.

### Arpeggiator

When clicked, spawns a slider and a button that plays an arpeggio from one note to another. Try swiping through all the keys or holding multiple keys together.

### Drop-shot Delay

Adds a delay that successively plays note at lower and lower volume. The greater the slider has traveled, the longer the delay.

### Envelope

Modulates sound. Controlled by the A/S/D/R rotary dials, and the modulation is represented in the graph below.

### Gain

Changes sound level by input.

### Garble

Adds a TV-static-like effect to the sound.

### High/Low Pass Filters



### LFO


### Oscillators


### Reverb

## Built With

* [JUCE](https://juce.com/) - C++ framework used to build multiplatform audio applications
* [Maxmillian](https://github.com/micknoise/Maximilian) - Audio synthesis and signal processing library

## Authors

* **Zachary Anderson** - [zanderson3j](https://https://github.com/zanderson3j)
* **Andrew Lee** - [andrewl33](https://https://github.com/andrewl33)
* **Samuel Judkis** - [sjudkis](https://https://github.com/sjudkis)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Blot background based off of [transofrming rorschach's mask](https://codepen.io/anthesema/pen/GzzGpQ) by [anthesema](https://codepen.io/anthesema).
* [OpenGL example](https://gist.github.com/wtsnz/a5ee2c0216b834df5aaace5e67716f0b) for integrating OpenGL with JUCE.
