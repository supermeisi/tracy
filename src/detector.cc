#include "detector.hh"

Detector::Detector()
{
    det = new TH2F("det", "Detector", 512, -1, 1, 512, -1, 1);

    n = TVector3(0., 0., 1.);
}

double Detector::GetLambda(TVector3 _r, TVector3 _p)
{
    double nx = n.X();
    double ny = n.Y();
    double nz = n.Z();

    double xm = rm.X();
    double ym = rm.Y();
    double zm = rm.Z();

    double x = _r.X();
    double y = _r.Y();
    double z = _r.Z();

    double px = _p.X();
    double py = _p.Y();
    double pz = _p.Z();

    double lambda = (nx*xm+nz*zm-nz*z+ny*ym-ny*y-nx*x)/(nz*pz+ny*py+nx*px);

    return lambda;
}

void Detector::Display()
{
    TCanvas *c = new TCanvas("c", "c", 500, 500);
    det->Draw("col");
}
