#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "TCanvas.h"
#include "TVector3.h"
#include "TH2F.h"

class Detector
{
public:
    Detector();

    double GetLambda(TVector3 _r, TVector3 _p);
    void SetPosition(double _xm, double _ym, double _zm) { xm = _xm; ym = _ym; zm = _zm; rm = TVector3(_xm, _ym, _zm);}
    void Hit(double _x, double _y) { det->Fill(_x, _y); }
    void Display();

private:
    TVector3 n;
    TVector3 rm;

    double xm, ym, zm;

    TH2F *det;
};

#endif // DETECTOR_HH
