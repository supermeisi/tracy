#ifndef TRACE_HH
#define TRACE_HH

#include <iostream>
#include <thread>

#include "TH2F.h"
#include "TRandom2.h"
#include "TView.h"
#include "TGeoTrack.h"

#include "sphere.hh"
#include "physics.hh"
#include "detector.hh"
#include "ray.hh"

class Trace
{
public:
    Trace();
    
    void SetNCores(int _n_cores) { n_cores = _n_cores; }
    bool Processing();
    bool Run();

private:
    int n_cores;
    std::thread th[100];

    TRandom2 *rand;

    Physics *physics;

    double n_world;

    Sphere *sp;
    Detector *det;

    bool verbose;

    TCanvas *c1;
    TView *view;
    TGeoManager *man;
    TGeoVolume *top;
};

#endif //TRACE_HH
