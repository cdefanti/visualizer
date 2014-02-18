#include "SequentialSoundStreamer.h"

namespace sfe
{
    bool SequentialSoundStreamer::Open(const char * Filename)
    {
        SoundFileInfo.format=0;
        if (!(SoundFile = sf_open (Filename, SFM_READ, &SoundFileInfo)))
            std::cout<<"\nCan't open the file.\n";

        initialize(SoundFileInfo.channels,SoundFileInfo.samplerate);

        SamplesArray = (short*) fftw_malloc(sizeof(short) * myBufferSize);

		out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * myBufferSize);
		outAbs = (double*) malloc(sizeof(double) * myBufferSize);
		outPhase = (double*) malloc(sizeof(double) * myBufferSize);

        return false;
    }

    bool SequentialSoundStreamer::OnGetData(sf::SoundStream::Chunk& Data)
    {
        if (! (Data.sampleCount = sf_readf_short (SoundFile, SamplesArray, myBufferSize / SoundFileInfo.channels) * SoundFileInfo.channels))
           {std::cout<<"\nCan't read the file (can be the end of it).\n"; return false;}

        Data.samples   = SamplesArray;


		double *in;
		fftw_plan p;

		in = (double*) fftw_malloc(sizeof(double) * myBufferSize);
		
		p = fftw_plan_dft_r2c_1d(myBufferSize, in, out, FFTW_FORWARD | FFTW_ESTIMATE);

		fftw_execute(p);

		for(int i = 0; i < myBufferSize; i++){
			outAbs[i] = sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
			outPhase[i] = atan2(out[i][1],out[i][0]);
		}

		fftw_destroy_plan(p);

		fftw_free(in); 

        return true;
    }

}