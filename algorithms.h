#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>

#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include <essentia/pool.h>


class AudioProcess
{
private:
    // loaded file
    std::vector <essentia::Real> audioBuffer;
    // specified frame
    std::vector<essentia::Real> frame;
    std::vector<essentia::Real> windowedFrame;
    std::vector<essentia::Real> spectrum;
    std::vector<essentia::Real> mfcc;

public:
    std::vector<essentia::Real> getAudioBuffer() const;
    //void setAudioBuffer(const std::vector<essentia::Real> &value);

    std::vector<essentia::Real> getFrame() const;
    //void setFrame(const std::vector<essentia::Real> &value);

    std::vector<essentia::Real> getSpectrum() const;
    std::vector<essentia::Real> getMfcc() const;

    /////
    void loadAudio(std::string fileName);
    void calculateMFCC();

    void calculateSpectrum ();

    void makeFrame(float startPos, float windowSize);
    AudioProcess();

    //void setSpectrum(const std::vector<essentia::Real> &value);

    //void setMfcc(const std::vector<essentia::Real> &value);
};

#endif // ALGORITHMS_H
