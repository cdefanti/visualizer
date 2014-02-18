#include "SequentialSoundStreamer.h"

namespace sfe
{
  void SequentialSoundStreamer::load(const sf::SoundBuffer& buffer)
  {
    // extract the audio samples from the sound buffer to our own container
    m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());

    // reset the current playing position 
    m_currentSample = 0;

    // initialize the base class
    initialize(buffer.getChannelCount(), buffer.getSampleRate());
  }

  bool SequentialSoundStreamer::onGetData(Chunk& data)
  {
    // number of samples to stream every time the function is called;
    // in a more robust implementation, it would rather be a fixed
    // amount of time rather than an arbitrary number of samples
    const int samplesToStream = 2205;

    // set the pointer to the next audio samples to be played
    data.samples = &m_samples[m_currentSample];
    double *in;
    fftw_plan p;

    in = (double*) fftw_malloc(sizeof(double) * myBufferSize);
    for(int i = 0; i < myBufferSize; i++){
      in[i] = data.samples[i];
    }

    p = fftw_plan_dft_r2c_1d(myBufferSize, in, out, FFTW_ESTIMATE);

    fftw_execute(p);

    for(int i = 0; i < myBufferSize; i++){
      outAbs[i] = sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
      outPhase[i] = atan2(out[i][1],out[i][0]);
    }

    fftw_destroy_plan(p);

    fftw_free(in); 

    // have we reached the end of the sound?
    if (m_currentSample + samplesToStream <= m_samples.size())
    {
      // end not reached: stream the samples and continue
      data.sampleCount = samplesToStream;
      m_currentSample += samplesToStream;
      return true;
    }
    else
    {
      // end of stream reached: stream the remaining samples and stop playback
      data.sampleCount = m_samples.size() - m_currentSample;
      m_currentSample = m_samples.size();
      return false;
    }
  }
  void SequentialSoundStreamer::onSeek(sf::Time timeOffset)
  {
    // compute the corresponding sample index according to the sample rate and channel count
    m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
  }

}
