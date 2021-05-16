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
    void Draw(TGeoManager &_man, TGeoVolume &_top);
    void SetBins(double _nx, double _ny) { det->SetBins(_nx, xmin, xmax, _ny, ymin, ymax); }

private:
    TH2F *det;
    TVector3 n;
    double xmin, xmax;
    double ymin, ymax;
    int nbinsx, nbinsy;
};

#endif // DETECTOR_HH
