#ifndef OBJECT_HH
#define OBJECT_HH

#include "TVector3.h"
#include "TGeoVolume.h"
#include "TGeoManager.h"

class Object
{
    public:
        Object();
        ~Object();
        void SetPosition(double _xm, double _ym, double _zm) { xm = _xm; ym = _ym; zm = _zm; rm = TVector3(_xm, _ym, _zm);}
        void SetKillTrack(bool _kill) { kill = _kill; }
        void SetRefIndex(double _nref) { nref = _nref; }
        void SetName(TString _name) { name = _name; }
        bool IsDetector() { return detector; }
        bool GetKillTrack() { return kill; }
        double GetRefIndex() { return nref; }
        virtual void Hit(double _x, double _y) {}
        virtual void Display() {}

        virtual double GetLambda(TVector3 _r, TVector3 _p) = 0;
        virtual TVector3 GetNormal(TVector3 _r) = 0;
        virtual void Draw(TGeoManager &_man, TGeoVolume &_top) {}

    protected:
        double xm, ym, zm;
        TVector3 rm;
        bool kill;
        double nref;
        TString name;
        bool detector;
};

#endif // OBJECT_HH
