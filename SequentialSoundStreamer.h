#ifndef SEQUENTIAL_SOUND_STREAMER_H_
#define SEQUENTIAL_SOUND_STREAMER_H_

#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
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
        myBufferSize(BufferSize)  {
          out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * myBufferSize);
          outAbs = (double*) malloc(sizeof(double) * myBufferSize);
          outPhase = (double*) malloc(sizeof(double) * myBufferSize);
        }
      virtual ~SequentialSoundStreamer() {}
      void load(const sf::SoundBuffer &buffer);
      double* getFFTAbs() { return outAbs; }
      double* getFFTPhase() { return outPhase; }

    private :
      virtual bool onGetData(sf::SoundStream::Chunk& Data);
      virtual void onSeek(sf::Time timeOffset);
      std::size_t            myBufferSize;

      fftw_complex *out;
      double* outAbs;
      double* outPhase;
      std::vector<sf::Int16> m_samples;
      std::size_t m_currentSample;
  };
}

#endif
