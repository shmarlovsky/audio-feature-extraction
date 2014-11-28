#include "algorithms.h"
#include <QDebug>
#include "mainwindow.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace essentia;
using namespace essentia::standard;


AudioProcess::AudioProcess()
{

    //audioBuffer.push_back(0);

}

vector<Real> AudioProcess::getAudioBuffer() const
{
    return audioBuffer;
}

void AudioProcess::setAudioBuffer(const vector<Real> &value)
{
    audioBuffer = value;
}
vector<Real> AudioProcess::getFrame() const
{
    return frame;
}

void AudioProcess::setFrame(const vector<Real> &value)
{
    frame = value;
}


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
    essentia::shutdown();
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


vector<Real> AudioProcess::getMFCC ()
{

}
