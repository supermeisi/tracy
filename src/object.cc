#include "object.hh"

Object::Object()
{
    kill = false;

    nref = 1.;

    n = TVector3(0., 0., 1.);
}

Object::~Object()
{}

void Object::SetRotation(double _xa, double _ya, double _za)
{
    xa = _xa;
    ya = _ya;
    za = _za;

    n.RotateX(_xa*TMath::Pi()/180.);
    n.RotateY(_ya*TMath::Pi()/180.);
    n.RotateZ(_za*TMath::Pi()/180.);
}
