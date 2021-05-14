#ifndef VERTEX_HH
#define VERTEX_HH

#include "TVector3.h"

class Vertex
{
public:
    Vertex();
    ~Vertex();

    void SetPosition(TVector3 _r) { r = _r; }
    void SetDirection(TVector3 _p) { p = _p; }

    TVector3 GetPosition() { return r; }
    TVector3 GetDirection() { return p; }

protected:
    TVector3 r, p;
};

#endif // VERTEX_HH
