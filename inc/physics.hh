#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "math.h"

#include "TVector3.h"

class Physics
{
public:
    Physics();

    TVector3 Refraction(TVector3 e, TVector3 n, double n1, double n2);
};

#endif // PHYSICS_HH
