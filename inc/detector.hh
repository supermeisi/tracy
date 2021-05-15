#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "TCanvas.h"
#include "TVector3.h"
#include "TH2F.h"
#include "TStyle.h"

#include "object.hh"

class Detector : public Object
{
public:
    Detector();
    ~Detector();

    double GetLambda(TVector3 _r, TVector3 _p);
    void Hit(double _x, double _y) { det->Fill(_x, _y); }
    TVector3 GetNormal(TVector3 _r) { return n; }
    void Display();
    void Draw(TGeoManager &_man, TGeoVolume &_top) {};

private:
    TH2F *det;
    TVector3 n;
};

#endif // DETECTOR_HH
