/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== README ==================
static const unsigned char temp_binary_data_0[] =
"                      .__        .__.__  .__               \r\n"
"  _____ _____  ___  __|__| _____ |__|  | |__|____    ____  \r\n"
" /     \\\\__  \\ \\  \\/  /  |/     \\|  |  | |  \\__  \\  /    \\ \r\n"
"|  Y Y  \\/ __ \\_>    <|  |  Y Y  \\  |  |_|  |/ __ \\|   |  \\\r\n"
"|__|_|  (____  /__/\\_ \\__|__|_|  /__|____/__(____  /___|  /\r\n"
"      \\/     \\/      \\/        \\/                \\/     \\/ \r\n"
"\r\n"
"::::::::::::::::::::::::::What's Maximilian?\r\n"
"\r\n"
"Maximilian is an audio synthesis and signal processing library written in C++. It's cross-platform compatible with MacOS, Windows, Linux and IOS systems.  The main features are:\r\n"
"\r\n"
"- sample playback, recording and looping\r\n"
"- read from WAV and OGG files.\r\n"
"- a selection of oscillators and filters\r\n"
"- enveloping\r\n"
"- multichannel mixing for 1, 2, 4 and 8 channel setups\r\n"
"- controller mapping functions\r\n"
"- effects including delay, distortion, chorus, flanging\r\n"
"- granular synthesis, including time and pitch stretching\r\n"
"- atom synthesis\r\n"
"- realtime music information retrieval functions: spectrum analysis, spectral features, octave analysis, Bark scale analysis, and MFCCs\r\n"
"- example projects for Windows and MacOS, using command line and OpenFrameworks environments\r\n"
"\r\n"
"\r\n"
":::::::::::::::::::::::::::BASIC EXAMPLES\r\n"
"\r\n"
"You can choose between using RTAudio and PortAudio drivers in player.h by uncommenting the appropriate line.  To use PortAudio, you will need to compile the portAudio library from http://http://www.portaudio.com/ and link it with your executable.\r\n"
"\r\n"
"Examples demonstrating different features can be found in the maximilian_examples folder.  To try them, replace the contents of main.cpp with the contents of a tutorial file and compile.\r\n"
"\r\n"
"\r\n"
":::MAC OSX XCODE PROJECT\r\n"
"\r\n"
"You can run the examples using the 'maximilianTest' XCode 3 project provided.\r\n"
"\r\n"
"\r\n"
"::WINDOWS VISUAL STUDIO 2010 PROJECT\r\n"
"\r\n"
"This is in the maximilianTestWindowsVS2010 folder. You will need to install the DirectX SDK, so that the program can use DirectSound.\r\n"
"\r\n"
"\r\n"
":::COMMAND LINE COMPILATION IN MACOSX\r\n"
"\r\n"
"> g++ -Wall -D__MACOSX_CORE__ -o maximilian main.cpp RtAudio.cpp player.cpp maximilian.cpp -framework CoreAudio -framework CoreFoundation -lpthread\r\n"
"\r\n"
"> ./maximilian\r\n"
"\r\n"
"\r\n"
"::COMMAND LINE COMPILATION IN LINUX\r\n"
"\r\n"
"With OSS:\r\n"
"> g++ -Wall -D__LINUX_OSS__ -o maximilian main.cpp RtAudio.cpp player.cpp maximilian.cpp -lpthread\r\n"
"\r\n"
"With ALSA:\r\n"
"> g++ -Wall -D__LINUX_ALSA__ -o maximilian main.cpp RtAudio.cpp player.cpp maximilian.cpp -lasound -lpthread\r\n"
"\r\n"
"With Jack:\r\n"
"> g++ -Wall -D__UNIX_JACK__ -o maximilian main.cpp RtAudio.cpp player.cpp maximilian.cpp `pkg-config --cflags --libs jack` -lpthread\r\n"
"\r\n"
"then:\r\n"
"> ./maximilian\r\n"
"\r\n"
"\r\n"
"\r\n"
":::::::::::::::::::::::::::OPENFRAMEWORKS\r\n"
"\r\n"
"Maximilian works well with the OpenFrameworks C++ creative coding toolkit (http://www.openframeworks.cc).\r\n"
"\r\n"
"In the ofxMaxim directory you will find examples to run in Windows, OSX and iOS, including FFT analysis and granular synthesis.  \r\n"
"\r\n"
"You can install the ofxMaxim addon by copying the ofxMaxim/ofxMaxim folder into your openframeworks addons directory.\r\n"
"\r\n"
"Important: when using Maximilian on OSX, link against the Accelerate framework.\r\n";

const char* README = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x8fd84dae:  numBytes = 3115; return README;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "README"
};

const char* originalFilenames[] =
{
    "README"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
