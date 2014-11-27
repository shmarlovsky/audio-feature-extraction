#include "algorithms.h"
#include <QDebug>


void loadAudio (string fileName)
{
    essentia::init();

     int sampleRate = 44100;
     AlgorithmFactory& factory = standard::AlgorithmFactory::instance();

     Algorithm* audio = factory.create("MonoLoader",
                                       "filename", fileName,
                                       "sampleRate", sampleRate);
   // vector<Real> audioBuffer;

    audio->output("audio").set(::audioBuffer);
    audio->compute();
    qDebug() << "AudioBuffer size: " << ::audioBuffer.size();
    delete audio;
    essentia::shutdown();
   // return audioBuffer;
}

vector<Real> getMFCC ()
{

}

vector<Real> makeWindow (vector<Real> audio, float startPos)
{
    vector<Real> window;
    int windowSize = 300;
    for (int i=0; i<windowSize; i++)
    {
        window[i]=audio[startPos*44100];
    }
    return window;
}
