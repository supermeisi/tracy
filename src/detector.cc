#include "detector.hh"

Detector::Detector()
{
    xmin = -1;
    xmax = 1;

    ymin = -1;
    ymax = 1;

    nbinsx = 100;
    nbinsy = 100;

    det = new TH2F("det", "Detector", nbinsx, xmin, xmax, nbinsy, ymin, ymax);

    detector = true;
    kill = true;

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
    gStyle->SetPalette(kRainBow);
    TCanvas *c = new TCanvas("c", "c", 500, 500);
    det->Draw("col");
}

void Detector::Draw(TGeoManager &_man, TGeoVolume &_top)
{
    TGeoVolume *box = _man.MakeBox("BOX",NULL,1,1,0);

    box->SetLineColor(kGreen);

    TGeoHMatrix *trans_rot = new TGeoHMatrix("TRANSROT");

    trans_rot->RotateX(xa);
    trans_rot->RotateY(ya);
    trans_rot->RotateZ(za);

    trans_rot->SetDx(xm);
    trans_rot->SetDy(ym);
    trans_rot->SetDz(zm);

    _top.AddNode(box,0, trans_rot);
}
