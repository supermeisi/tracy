#include "source.hh"

Source::Source()
{
    rand = new TRandom2();
    rand->SetSeed(1);

    n_rays = 100;
}

Source::~Source()
{}

TVector3 Source::GetPosition()
{
    double r0 = 0.5*sqrt(rand->Rndm());
    double theta0 = 2*TMath::Pi()*rand->Rndm();

    TVector3 r;

    r.SetX(r0*cos(theta0));
    r.SetY(r0*sin(theta0));
    r.SetZ(0.);

    return r;
}

TVector3 Source::GetDirection()
{
    TVector3 p;

    p.SetX(0.);
    p.SetY(0.);
    p.SetZ(1.);

    return p;
}
