#ifndef SPHERE_HH
#define SPHERE_HH

#include "TVector3.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoManager.h"

class Sphere
{
public:
    Sphere();
    ~Sphere();

    void SetRadius(double _R) { R = _R; }
    double GetLambda(TVector3 _r, TVector3 _p);
    TVector3 GetNormal(TVector3 _r);
    void Draw();
    void SetPosition(double _xm, double _ym, double _zm) { xm = _xm; ym = _ym; zm = _zm; rm = TVector3(_xm, _ym, _zm);}
    double GetRefIndex() { return n; }
    void Draw(TGeoManager &_man, TGeoVolume &_top);

private:
    double R;
    double xm, ym, zm;
    TVector3 rm;
    double n;
};

#endif //SPHERE_HH
