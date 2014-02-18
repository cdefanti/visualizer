#include <SFML/Audio.hpp>
#include <sndfile.h>
#include <fftw3.h>
#include <iostream>
#include <fftw3.h>
#include <math.h>

namespace sfe
{

class SequentialSoundStreamer : public sf::SoundStream
{
public :
    SequentialSoundStreamer(std::size_t BufferSize) :
    myBufferSize(BufferSize)  {}
    bool Open(const char * Filename);
	double* getFFTAbs() { return outAbs; }
	double* getFFTPhase() { return outPhase; }

private :
    virtual bool OnGetData(sf::SoundStream::Chunk& Data);
    std::size_t            myBufferSize;

    SNDFILE * SoundFile;
    SF_INFO SoundFileInfo;
    short * SamplesArray;
	fftw_complex *out;
	double* outAbs;
	double* outPhase;
};
}