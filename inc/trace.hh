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
#include "object.hh"

class Trace
{
public:
    Trace();
    
    void SetNCores(int _n_cores) { n_cores = _n_cores; }
    bool Processing();
    bool Run();
    void AddObject(Object* _obj) { objarr.push_back(_obj); }
    void SetVerbose(bool _verbose) { verbose = _verbose; }

private:
    int n_cores;
    double n_world;
    bool verbose;
    double lambda_min_init;
    int GetMinimum(const TVector3 &, const TVector3 &);
    std::thread th[100];
    TRandom2 *rand;
    Physics *physics;
    TCanvas *c1;
    TView *view;
    TGeoManager *man;
    TGeoVolume *top;
    std::vector<Object*> objarr;
};

#endif //TRACE_HH
