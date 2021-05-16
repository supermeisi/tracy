#ifndef SOURCE_HH
#define SOURCE_HH

#include "TRandom2.h"

#include "object.hh"

class Source : public Object
{
public:
    Source();
    ~Source();

    TVector3 GetPosition();
    TVector3 GetDirection();
    int GetNRays() { return n_rays; }

    void SetNRays(int _n_rays) { n_rays = _n_rays; }

    void Hit(double _x, double _y) {}
    void Display() {}

    double GetLambda(TVector3 _r, TVector3 _p) {}
    TVector3 GetNormal(TVector3 _r) {}
    void Draw(TGeoManager &_man, TGeoVolume &_top) {}

private:
    TRandom2 *rand;
    int n_rays;
};

#endif // SOURCE_HH
