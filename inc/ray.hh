#ifndef RAY_HH
#define RAY_HH

#include <iostream>

#include "TVector3.h"
#include "TGeoTrack.h"

#include "vertex.hh"

class Ray
{
    public:
        Ray();
        ~Ray();
        
        void AddVertex(Vertex *_vtx) { vtx.push_back(_vtx); }
        void SetWavelength(Double_t _wlen) { wlen = _wlen; }
        void Draw();
        void Print();
        
        Vertex *GetVertex(Int_t i) { return vtx[i]; }

        Double_t GetWavelength() { return wlen; }

        Int_t GetN() { return vtx.size(); }
    
    private:
        std::vector<Vertex*> vtx;
        Double_t wlen;
};

#endif //RAY_HH

