#include "sphere.hh"

Sphere::Sphere()
{
    R = 1;

    nref = 1.47;

    detector = false;
    kill = false;
}

Sphere::~Sphere()
{}

double Sphere::GetLambda(TVector3 _r, TVector3 _p)
{
    double x = _r.X();
    double y = _r.Y();
    double z = _r.Z();
    
    double px = _p.X();
    double py = _p.Y();
    double pz = _p.Z();
    
    double lambda1 = -pow(pow(pz,2)+pow(py,2)+pow(px,2),-1)*(pow((-pow(py,2)-pow(px,2))*pow(zm,2)+((2*pow(py,2)+2*pow(px,2))*z+2*py*pz*ym-2*py*pz*y+2*px*pz*xm-2*px*pz*x)*zm+(-pow(py,2)-pow(px,2))*pow(z,2)+(-2*py*pz*ym+2*py*pz*y-2*px*pz*xm+2*px*pz*x)*z+(-pow(pz,2)-pow(px,2))*pow(ym,2)+((2*pow(pz,2)+2*pow(px,2))*y+2*px*py*xm-2*px*py*x)*ym+(-pow(pz,2)-pow(px,2))*pow(y,2)+(2*px*py*x-2*px*py*xm)*y+(-pow(pz,2)-pow(py,2))*pow(xm,2)+(2*pow(pz,2)+2*pow(py,2))*x*xm+(-pow(pz,2)-pow(py,2))*pow(x,2)+pow(R,2)*pow(pz,2)+pow(R,2)*pow(py,2)+pow(R,2)*pow(px,2),0.5)-pz*zm+pz*z-py*ym+py*y-px*xm+px*x);
    
    double lambda2 = pow(pow(pz,2)+pow(py,2)+pow(px,2),-1)*(pow((-pow(py,2)-pow(px,2))*pow(zm,2)+((2*pow(py,2)+2*pow(px,2))*z+2*py*pz*ym-2*py*pz*y+2*px*pz*xm-2*px*pz*x)*zm+(-pow(py,2)-pow(px,2))*pow(z,2)+(-2*py*pz*ym+2*py*pz*y-2*px*pz*xm+2*px*pz*x)*z+(-pow(pz,2)-pow(px,2))*pow(ym,2)+((2*pow(pz,2)+2*pow(px,2))*y+2*px*py*xm-2*px*py*x)*ym+(-pow(pz,2)-pow(px,2))*pow(y,2)+(2*px*py*x-2*px*py*xm)*y+(-pow(pz,2)-pow(py,2))*pow(xm,2)+(2*pow(pz,2)+2*pow(py,2))*x*xm+(-pow(pz,2)-pow(py,2))*pow(x,2)+pow(R,2)*pow(pz,2)+pow(R,2)*pow(py,2)+pow(R,2)*pow(px,2),0.5)+pz*zm-pz*z+py*ym-py*y+px*xm-px*x);


    if(std::abs(lambda1) < std::abs(lambda2) && lambda1 > 1e-15)
    {
        return lambda1;
    }
    else
    {
        return lambda2;
    }
}

TVector3 Sphere::GetNormal(TVector3 _r)
{
    double x = _r.X();
    double y = _r.Y();
    double z = _r.Z();
    
    TVector3 n(xm - x, ym - y, zm - z);

    n = n.Unit();
    
    return n;
}

void Sphere::Draw(TGeoManager &_man, TGeoVolume &_top)
{
    TGeoVolume *sphere = _man.MakeSphere("SPHERE",NULL,0,R);

    TGeoHMatrix *trans_rot = new TGeoHMatrix("TRANSROT");

    trans_rot->SetDx(xm);
    trans_rot->SetDy(ym);
    trans_rot->SetDz(zm);

    _top.AddNode(sphere, 0, trans_rot);
}
