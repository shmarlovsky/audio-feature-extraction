#ifndef ALGORITHMS_H
#define ALGORITHMS_H



#include <iostream>
#include <fstream>
#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include <essentia/pool.h>

using namespace std;
using namespace essentia;
using namespace essentia::standard;

void loadAudio(string fileName);

vector<Real> getMFCC ();
vector<Real> makeWindow (vector<Real> audio, float startPos);

vector<Real> audioBuffer;

#endif // ALGORITHMS_H
