#ifndef TRACE_HH
#define TRACE_HH

#include <iostream>
#include <thread>

#include "TH2F.h"
#include "TRandom2.h"
#include "TView.h"
#include "TGeoTrack.h"

#include "source.hh"
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
    void AddSource(Source* _src) { srcarr.push_back(_src); }
    void AddObject(Object* _obj) { objarr.push_back(_obj); }
    void SetVerbose(bool _verbose) { verbose = _verbose; }
    void SetNVisibleRays(int _n_draw) { n_draw = _n_draw; }

private:
    int n_cores;
    int n_draw;
    double n_world;
    bool verbose;
    double lambda_min_init;
    std::thread th[100];
    Physics *physics;
    TCanvas *c1;
    TView *view;
    TGeoManager *man;
    TGeoVolume *top;
    std::vector<Object*> objarr;
    std::vector<Source*> srcarr;

    int GetMinimum(const TVector3 &, const TVector3 &);
};

#endif //TRACE_HH
