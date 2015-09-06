#ifndef ALGORITHMS_H
#define ALGORITHMS_H

//#include <vector>

#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include <essentia/pool.h>


class AudioProcess
{
private:
    // loaded file
    std::vector <essentia::Real> audioBuffer;
    std::string fileName;
    // specified frame
    std::vector<essentia::Real> frame;
    //std::vector<std::vector<essentia::Real> > allFrames;
    std::vector<essentia::Real> windowedFrame;
    std::vector<essentia::Real> spectrum;
    std::vector<essentia::Real> mfccCoeffs;
    std::vector<std::vector<essentia::Real> > allMFCC;
    std::vector<essentia::Real> gfccCoeffs;
    std::vector<std::vector<essentia::Real> > allGFCC;
    std::vector<std::vector<double> > waveletResult;

public:
    std::vector<essentia::Real> getAudioBuffer() const;
    //void setAudioBuffer(const std::vector<essentia::Real> &value);

    std::vector<essentia::Real> getFrame() const;
    //std::vector<essentia::Real> frameCutter() const;
    //void setFrame(const std::vector<essentia::Real> &value);

    std::vector<essentia::Real> getSpectrum() const;
    std::vector<essentia::Real> getMfcc() const;
    std::vector<essentia::Real> getGfcc() const;

    /////
    void loadAudio(std::string fileName);
    void calculateMFCC();
    void calculateGFCC();

    void calculateSpectrum ();

    void makeFrame(float startPos, int windowSize);
    void frameCutter(int frameSize=1024);
    void calculateWholeAudio(int frameSize=1024);
    void calculateWavelet();
    void exportToFile();
    AudioProcess();

    //void setSpectrum(const std::vector<essentia::Real> &value);

    //void setMfcc(const std::vector<essentia::Real> &value);

    //void setGfcc(const std::vector<essentia::Real> &value);
    std::string getFileName() const;
    void setFileName(const std::string &value);
    std::vector<double> getWaveletResult() const;
    void setWaveletResult(const std::vector<std::vector<double> > &value);
};

#endif // ALGORITHMS_H
