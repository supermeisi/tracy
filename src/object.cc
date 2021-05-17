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
    n.RotateX(_xa);
    n.RotateY(_ya);
    n.RotateZ(_za);
}
