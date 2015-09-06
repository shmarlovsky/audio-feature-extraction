#include <iostream>
#include <fstream>
#include <QDebug>

#include "algorithms.h"
#include "mainwindow.h"
#include "dsp/cwt.h"


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

std::vector<essentia::Real> AudioProcess::getMfcc() const
{
    return mfccCoeffs;
}


std::vector<essentia::Real> AudioProcess::getGfcc() const
{
    return gfccCoeffs;
}

std::string AudioProcess::getFileName() const
{
    return fileName;
}

void AudioProcess::setFileName(const std::string &value)
{
    fileName = value;
}

std::vector<double> AudioProcess::getWaveletResult() const
{
    return waveletResult[0];
}

void AudioProcess::setWaveletResult(const std::vector<std::vector<double> > &value)
{
    waveletResult = value;
}
vector<Real> AudioProcess::getAudioBuffer() const
{
    return audioBuffer;
}

vector<Real> AudioProcess::getFrame() const
{
    return frame;
}


void AudioProcess::loadAudio (string fileName)
{
    essentia::init();

    int sampleRate = 44100;
    AlgorithmFactory& factory = standard::AlgorithmFactory::instance();

    Algorithm* audio = factory.create("MonoLoader",
                                      "filename", fileName,
                                      "sampleRate", sampleRate);

    audioBuffer.clear();
    frame.clear();
    windowedFrame.clear();
    spectrum.clear();
    mfccCoeffs.clear();
    gfccCoeffs.clear();
    allMFCC.clear();
    allGFCC.clear();

    audio->output("audio").set(audioBuffer);
    audio->compute();
    qDebug() << "AudioBuffer size: " << audioBuffer.size();
    delete audio;
    essentia::shutdown();
}

void AudioProcess::makeFrame (float startPos, int windowSize)
{
    frame.clear();

    float a = startPos*44100.0;
    for (int i=0; i<windowSize; i++)
    {
        frame.push_back(audioBuffer[a+i]);
    }

}

void AudioProcess::frameCutter(int frameSize)
{
    essentia::init();
    AlgorithmFactory& factory = standard::AlgorithmFactory::instance();
    //int frameSize = 2048;
    int hopSize = 1024;
    Algorithm* fc    = factory.create("FrameCutter",
                                      "frameSize", frameSize,
                                      "hopSize", hopSize,"startFromZero",true,"lastFrameToEndOfFile",true);
    fc->input("signal").set(audioBuffer);
    fc->output("frame").set(frame);
    fc->compute();

    qDebug() <<"(from framecutter) frameSize: " << frame.size();
    //cout << "frame after alg: " << frame << endl;
    essentia::shutdown();
}



void AudioProcess::calculateSpectrum()
{
    essentia::init();
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
    qDebug() << "frameSize: " << frame.size();
    qDebug() << "windowedFrameSize: " << windowedFrame.size();
    qDebug() << "spectrumSize: " << spectrum.size();
    delete windowAlg;
    delete spectrumAlg;
    essentia::shutdown();

}


void AudioProcess::calculateMFCC ()
{
    essentia::init();
    AlgorithmFactory& factory = standard::AlgorithmFactory::instance();
    Algorithm* mfccAlg  = factory.create("MFCC", "highFrequencyBound", 22050);

    vector<Real> mfccBands;
    mfccAlg->input("spectrum").set(spectrum);
    mfccAlg->output("bands").set(mfccBands);
    mfccAlg->output("mfcc").set(mfccCoeffs);

    mfccAlg->compute();

    // normalization
    //    for (int i=0; i< mfcc.size(); i++)
    //    {
    //        if( (mfcc[i] > 20  && mfcc[i] < 100) || (mfcc[i] < -20 && mfcc[i] > -100) )
    //            mfcc[i]*=0.1;
    //        if( mfcc[i] > 100 || mfcc[i] < -100 )
    //            mfcc[i]*=0.01;
    //    }

    qDebug() <<"mfccSize: " << mfccCoeffs.size();
    cout << "MFCC coefs" << mfccCoeffs << endl;

    essentia::shutdown();

}


void AudioProcess::calculateGFCC()
{
    essentia::init();
    AlgorithmFactory& factory = standard::AlgorithmFactory::instance();
    Algorithm* gfccAlg  = factory.create("GFCC");

    vector<Real> gfccBands;
    gfccAlg->input("spectrum").set(spectrum);
    gfccAlg->output("bands").set(gfccBands);
    gfccAlg->output("gfcc").set(gfccCoeffs);

    gfccAlg->compute();
    qDebug() <<"gfccSize: " << gfccCoeffs.size();
    essentia::shutdown();

}


void AudioProcess::calculateWholeAudio(int frameSize)
{

    // creating algorithms
    essentia::init();

    AlgorithmFactory& factory = standard::AlgorithmFactory::instance();

    //int hopSize = 1024;
    int hopSize = frameSize/2;
    // frame size??
    Algorithm* framecutterAlg    = factory.create("FrameCutter",
                                                  "frameSize", frameSize,
                                                  "hopSize", hopSize,"startFromZero",true,"lastFrameToEndOfFile",false);

    Algorithm* windowAlg     = factory.create("Windowing",
                                              "type", "blackmanharris62");

    Algorithm* spectrumAlg  = factory.create("Spectrum");

    // size of input spectrum??
    Algorithm* mfccAlg  = factory.create("MFCC", "highFrequencyBound", 22050);

    Algorithm* gfccAlg  = factory.create("GFCC");


    //connecting algorithms
    framecutterAlg->input("signal").set(audioBuffer);
    framecutterAlg->output("frame").set(frame);

    windowAlg->input("frame").set(frame);
    windowAlg->output("frame").set(windowedFrame);

    spectrumAlg->input("frame").set(windowedFrame);
    spectrumAlg->output("spectrum").set(spectrum);

    vector<Real> mfccBands;
    mfccAlg->input("spectrum").set(spectrum);
    mfccAlg->output("bands").set(mfccBands);
    mfccAlg->output("mfcc").set(mfccCoeffs);

    vector<Real> gfccBands;
    gfccAlg->input("spectrum").set(spectrum);
    gfccAlg->output("bands").set(gfccBands);
    gfccAlg->output("gfcc").set(gfccCoeffs);


    //calculating
    int iter=0;
    while(true)
    {
        framecutterAlg->compute();
        if (!frame.size())
        {
            break;
        }

        if (isSilent(frame)) continue;
        //cout << "frame:" << frame << endl;

        windowAlg->compute();
        spectrumAlg->compute();
        mfccAlg->compute();
        gfccAlg->compute();

        allMFCC.push_back(mfccCoeffs);
        allGFCC.push_back(gfccCoeffs);

        qDebug() << "iter: " << iter;
        iter++;
    } //while


    // mfcc normalization
    //    for (int i=0; i< mfcc.size(); i++)
    //    {
    //        if( (mfcc[i] > 20  && mfcc[i] < 100) || (mfcc[i] < -20 && mfcc[i] > -100) )
    //            mfcc[i]*=0.1;
    //        if( mfcc[i] > 100 || mfcc[i] < -100 )
    //            mfcc[i]*=0.01;
    //    }


    //    int allGFCCSize = allGFCC.size();

    //    for (int i=0; i<allGFCCSize; i++)
    //    {
    //        for (int j=0; j<13; j++)
    //        {
    //            std::cout << "AllGFCC: " << allGFCC[i][j] << std::endl;
    //        }
    //        std::cout << std::endl;
    //    }

    delete framecutterAlg;
    delete windowAlg;
    delete spectrumAlg;
    delete mfccAlg;
    delete gfccAlg;

    essentia::shutdown();

}

void AudioProcess::calculateWavelet()
{

    int minLenth = 16;
    int maxLenth = 4096;
    int step = maxLenth/2;
    int size = audioBuffer.size();
    int waveletCount = 13;
    std::vector<double> audio(size);
    for(int i=0; i<size; i++)
    {
        audio[i]=(double)audioBuffer[i];
    }

    //k52::dsp::MhatWaveletFunction::shared_ptr mhatFunc(new k52::dsp::MhatWaveletFunction());
    k52::dsp::MorletWaveletFunction::shared_ptr morletFunc(new k52::dsp::MorletWaveletFunction());

    //k52::dsp::Wavelet::shared_ptr waveletPtr= k52::dsp::Wavelet::BuildWavelet(mhatFunc, 16, 4096, 13);
    k52::dsp::Wavelet::shared_ptr waveletPtr= k52::dsp::Wavelet::BuildWavelet(morletFunc, minLenth, maxLenth, waveletCount);

    waveletResult = k52::dsp::ContiniousWaveletTransformation(audio, waveletPtr, step);

    int waveCount= waveletResult.size();
    int middleWavelet = waveCount/2;
    qDebug() << middleWavelet << endl;

    std::cout << "WaveCount: " << waveCount << std::endl;
    for (int i=0; i<waveCount; i++)
    {
        for (int j=0; j<13; j++)
        {
            std::cout << "Wave: " << waveletResult[i][j] << std::endl;
        }
        std::cout << std::endl;
    }

}

void AudioProcess::exportToFile()
{

    calculateWholeAudio();
    calculateWavelet();

    int waveletWindowsCount=waveletResult.size();
    int middleWavelet = waveletWindowsCount/2;
    int allMFCCSize=allMFCC.size();
    int allGFCCSize=allGFCC.size();
    int middleCoeff = allMFCCSize/2;

    cout << "Sizes: " << waveletWindowsCount << "  " << allMFCCSize << "  " << allGFCCSize << endl;

    std::vector<std::vector<double> > waveletsForFile;
    std::vector<std::vector<essentia::Real> > MFCCForFile;
    std::vector<std::vector<essentia::Real> > GFCCForFile;

    waveletsForFile.reserve(3);
    MFCCForFile.reserve(3);
    GFCCForFile.reserve(3);


    //usrednenie
    if(waveletWindowsCount>1)
    {

        for(int i=0; i<waveletWindowsCount; i++)
        {

            if(i==0)
            {
                for(int j=0; j<13; j++)
                {
                    waveletResult[i][j]=(waveletResult[i][j]+ waveletResult[i+1][j])/2;
                }

            }
            if(i==middleWavelet && waveletWindowsCount>2)
            {
                for (int j=0; j<13; j++)
                {
                    waveletResult[i][j]=(waveletResult[i][j]+ waveletResult[i+1][j]+ waveletResult[i-1][j])/3;
                }
            }
            if(i==waveletWindowsCount-1)
            {
                for (int j=0; j<13; j++)
                {
                    waveletResult[i][j]=(waveletResult[i][j]+ waveletResult[i-1][j])/2;
                }
            }

        }
    }

    // usrednenie
    if(allMFCCSize>1 && allGFCCSize>1)
    {
        for(int i=0; i<allMFCCSize; i++)
        {

            if(i==0)
            {
                for(int j=0; j<13; j++)
                {
                    allMFCC[i][j]=(allMFCC[i][j]+ allMFCC[i+1][j])/2;
                    allGFCC[i][j]=(allGFCC[i][j]+ allGFCC[i+1][j])/2;
                }
            }
            if(i==middleCoeff && allMFCCSize>2 && allGFCCSize>2)
            {
                for (int j=0; j<13; j++)
                {
                    allMFCC[i][j]=(allMFCC[i][j]+ allMFCC[i+1][j] + allMFCC[i-1][j])/3;
                    allGFCC[i][j]=(allGFCC[i][j]+ allGFCC[i+1][j] + allGFCC[i-1][j])/3;
                }
            }
            if(i==allMFCCSize-1)
            {
                for (int j=0; j<13; j++)
                {
                    allMFCC[i][j]=(allMFCC[i][j]+ allMFCC[i-1][j])/2;
                    allGFCC[i][j]=(allGFCC[i][j]+ allGFCC[i-1][j])/2;
                }
            }

        }
    }

    waveletsForFile.push_back(waveletResult[0]);
    waveletsForFile.push_back(waveletResult[middleWavelet]);
    waveletsForFile.push_back(waveletResult[waveletWindowsCount-1]);
    MFCCForFile.push_back(allMFCC[0]);
    MFCCForFile.push_back(allMFCC[middleCoeff]);
    MFCCForFile.push_back(allMFCC[allMFCCSize-1]);
    GFCCForFile.push_back(allGFCC[0]);
    GFCCForFile.push_back(allGFCC[middleCoeff]);
    GFCCForFile.push_back(allGFCC[allMFCCSize-1]);


    //export to file
    QFile file1(QString::fromStdString(fileName)+"_features.txt");
    file1.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream outStream1(&file1);

    for(int i=0; i<3; i++)
    {
        for (int j=0; j<13; j++)
        {
            outStream1 << MFCCForFile[i][j] << endl;
        }
        //outStream1 << endl;

        for (int j=0; j<13; j++)
        {
            outStream1 << GFCCForFile[i][j] << endl;
        }
        //outStream1 << endl;

        for (int j=0; j<13; j++)
        {
            outStream1 << waveletsForFile[i][j] << endl;
        }
        outStream1 << endl;
    }
    //outStream1 << endl;
    file1.close();

}
