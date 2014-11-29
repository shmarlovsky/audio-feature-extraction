#include <iostream>
#include <fstream>
#include <QDebug>

#include "algorithms.h"
#include "mainwindow.h"


using namespace std;
using namespace essentia;
using namespace essentia::standard;


AudioProcess::AudioProcess()
{

}


std::vector<essentia::Real> AudioProcess::getSpectrum() const
{
    return spectrum;
}

//void AudioProcess::setSpectrum(const std::vector<essentia::Real> &value)
//{
//    spectrum = value;
//}


std::vector<essentia::Real> AudioProcess::getMfcc() const
{
    return mfcc;
}

//void AudioProcess::setMfcc(const std::vector<essentia::Real> &value)
//{
//    mfcc = value;
//}

vector<Real> AudioProcess::getAudioBuffer() const
{
    return audioBuffer;
}

//void AudioProcess::setAudioBuffer(const vector<Real> &value)
//{
//    audioBuffer = value;
//}

vector<Real> AudioProcess::getFrame() const
{
    return frame;
}

//void AudioProcess::setFrame(const vector<Real> &value)
//{
//    frame = value;
//}


void AudioProcess::loadAudio (string fileName)
{
    essentia::init();

     int sampleRate = 44100;
     AlgorithmFactory& factory = standard::AlgorithmFactory::instance();

     Algorithm* audio = factory.create("MonoLoader",
                                       "filename", fileName,
                                       "sampleRate", sampleRate);
   // vector<Real> audioBuffer;

    audioBuffer.clear();
    audio->output("audio").set(audioBuffer);
    audio->compute();
    qDebug() << "AudioBuffer size: " << audioBuffer.size();
    delete audio;
    //essentia::shutdown();
    //return audioBuffer;
}

void AudioProcess::makeFrame (float startPos, float windowSize)
{
    frame.clear();

    float a = startPos*44100.0;
    for (int i=0; i<windowSize; i++)
    {
        frame.push_back(audioBuffer[a+i]);
    }

}

void AudioProcess::calculateSpectrum()
{
    AlgorithmFactory& factory = standard::AlgorithmFactory::instance();

    Algorithm* windowAlg     = factory.create("Windowing",
                                      "type", "blackmanharris62");

    Algorithm* spectrumAlg  = factory.create("Spectrum");

    vector<Real> windowedFrame;
    windowAlg->input("frame").set(frame);
    windowAlg->output("frame").set(windowedFrame);

    spectrumAlg->input("frame").set(windowedFrame);
    spectrumAlg->output("spectrum").set(spectrum);
    windowAlg->compute();
    spectrumAlg->compute();

    delete windowAlg;
    delete spectrumAlg;

}


void AudioProcess::calculateMFCC ()
{
    AlgorithmFactory& factory = standard::AlgorithmFactory::instance();
    Algorithm* mfccAlg  = factory.create("MFCC");

    vector<Real> mfccBands;
    mfccAlg->input("spectrum").set(spectrum);
    mfccAlg->output("bands").set(mfccBands);
    mfccAlg->output("mfcc").set(mfcc);

    mfccAlg->compute();
    qDebug() <<"mfccSize: " << mfcc.size();

}


