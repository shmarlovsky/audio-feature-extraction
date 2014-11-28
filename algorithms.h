#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include <essentia/pool.h>


//убрать из заголовочника
//using namespace std;
//using namespace essentia;
//using namespace essentia::standard;


class AudioProcess
{
private:
    // loaded file
    std::vector <essentia::Real> audioBuffer;
    // specidied window
    std::vector<essentia::Real> frame;
    std::vector<essentia::Real> windowedFrame;
    std::vector<essentia::Real> spectrum;
    std::vector<essentia::Real> mfcc;

public:
    std::vector<essentia::Real> getAudioBuffer() const;
    void setAudioBuffer(const std::vector<essentia::Real> &value);

    std::vector<essentia::Real> getFrame() const;
    void setFrame(const std::vector<essentia::Real> &value);


    /////
    void loadAudio(std::string fileName);
    std::vector<essentia::Real> getMFCC ();

    void makeFrame(float startPos, float windowSize);
    AudioProcess();

};

#endif // ALGORITHMS_H
